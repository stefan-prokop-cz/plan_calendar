#include "EventController.h"

/**
 * Method which creates a new event. It takes parameters for creating the Event entity. Method validates input and
 * returns the status code:
 *      0: some error detected
 *      1: successfully created
 *      2: datetime_start or datetime_end is not a valid datetime (old date or time or datetime_start >= datetime_end)
 *      4: datetime_start or datetime_end is between interval where is defined life style constants
 *      5: calendar with calendar_name does not exists or actual user is not an owner
 *      6: datetime_start or datetime_end is between event which was created before
 * - 1 means that event was successfully created, another status codes means that event was not created
 * @param name              (string - event name)
 * @param description       (string - event description)
 * @param repeat            (bool - is repeatable)
 * @param repeat_count      (int - how many repetitions will be created)
 * @param repeat_const      (double - time between child repeated event)
 * @param datetime_start    (string - start datetime)
 * @param datetime_end      (string - end datetime)
 * @param status            (int - event status - 1: compulsory, 2: optional, 3: movable)
 * @param public_event      (int - event status #2 - 1: private, 2: public, 3: shared)
 * @param calendar_name     (string - name of the calendar where event will be created)
 * @return int              (status code)
 */
int EventController::addNewEvent(const string &name, const string &description, bool repeat, const int repeat_count,
                                 const double repeat_const, const tm &datetime_start, const tm &datetime_end,
                                 const int status, const int public_event, const string & calendar_name) const
{
    EventRepository repository;
    EventHelper helper;
    Validation validation;
    ostringstream stream;

    if(!validation.validateDateTime(datetime_start) || !validation.validateDateTime(datetime_end) ||
            validation.compareDates(datetime_start, datetime_end) != 1) {

        return 2;
    }

    if(validation.isPause(datetime_start, 0) || validation.isPause(datetime_end, 0)) {
        return 4;
    }

    CalendarRepository calendar_repository;
    map<string, string> params;
    params["name"] = calendar_name;
    stream << session->getId();
    params["user_id"] = stream.str();
    Calendar * find_calendar;

    try {
        find_calendar = calendar_repository.findBy(params, true, "", "", false)[0];
    } catch (...) {
        return 5;
    }

    string date_start = helper.createTextFromDate(datetime_start), date_end = helper.createTextFromDate(datetime_end);
    Event event(0, 0, find_calendar->getId(), status, repeat_count, public_event, name, description, date_start,
                   date_end, repeat, repeat_const);
    int result = repository.create(event);
    delete find_calendar;

    if(result == 2) { return 4; }
    else if(result == 4) { return 6; }

    return result;
}
/**
 * Method which prepares rendering form for sharing calendars with another users
 */
void EventController::renderShareForm() const
{
    ostringstream stream;
    EventView view;
    CalendarRepository repository;
    vector<Calendar*> calendars;
    map<string, string> params;
    stream << session->getId(), params["user_id"] = stream.str();
    calendars = repository.findBy(params, false, "", "", false);
    view.createShareForm(calendars);
}
/**
 * Method which creates a new calendar. It takes string parameter name which is used as a calendar name.
 * @param name      (string)
 * @return bool     (success or fail status)
 */
bool EventController::addNewCalendar(const string &name) const
{
	if(name.size() <= 0) {
		return 0;
	}

    ostringstream stream;
    stream << session->getId();
    map<string, string> params;
    params["user_id"] = stream.str(), params["name"] = name;
    CalendarRepository repository;

    return repository.create(params);
}
/**
 * Metoda obstaravajici sdileni kalendare s ostatnimi uzivateli
 * Method which is used for a sharing calendars with another users. It takes vector string parameter usernames where
 * are usernames of users - with them will be calendar shared and string parameter with calendar name.
 * - Status codes:
 *      0: Successfully shared with all users
 *      1: Sharing failed (two situations - user does not exists or some database error)
 *      3: Calendar with calendar_name does not exists
 * @param usernames         (vector<string>)
 * @param calendar_name     (string)
 * @return int              (status code)
 */
int EventController::shareCalendar(const vector<string> &usernames, const string &calendar_name) const
{
    CalendarRepository repository;
    map<string, string> params;
    params["name"] = calendar_name;
    Calendar * calendar;
    bool error = false;

    try {
        calendar = repository.findBy(params, true, "", "", false)[0];
    } catch (...) { return 3; }

    for(const auto & it : usernames) {
        if(!repository.share(it, calendar->getId())) {
            error = true;
        }
    }

    delete calendar;
    return (int) error;
}
/**
 * Method which find the closest date for a potential creating or updating the event from calendar with calendar_name
 * parameter. Second parameter is hours - it means how many hours user need for his potential new event. If hours is
 * equal to 0 then method returns the closest date and if hours is bigger than zero - it returns more relevant dates.
 * @param calendar_name     (string)
 * @param hours             (double)
 * @throws CalendarNotFoundException
 * @return vector<string>   (relevant datetimes)
 */
vector<string> EventController::getClosestDate(const string & calendar_name, const double hours, bool relevant) const
{
    EventHelper helper;
    vector<string> events;

    try {
        events = helper.findClosestDate(calendar_name, relevant, hours);
    } catch (...) { throw CalendarNotFoundException(); }

    return events;
}
/**
 * Method which prepares rendering user's calendars or calendars which are shared with him.
 */
void EventController::renderCalendars() const
{
    ostringstream stream;
    EventView view;
    CalendarRepository repository;
    vector<Calendar*> calendars;
    map<string, string> params;
    stream << session->getId();
    params["user_id"] = stream.str();
    params["shared_id"] = stream.str();
    stream.str("");
    stream << " LEFT JOIN `shared_events` ON `calendar_id`=`calendar`.`id`";

    try {
        calendars = repository.findBy(params, false, "", stream.str(), true);
    } catch (...) {}

    view.showCalendars(calendars);
}
/**
 * Method which returns events from calendar (calendar_name parameter) on the page (page parameter). This method
 * represents searching through all events in calendar with paginator. From shared calendar shows only public and shared
 * events.
 * @param calendar_name     (string)
 * @param page              (int)
 * @throws CalendarNotFoundException
 * @return vector<Event*>   (events on page)
 */
vector<Event*> EventController::getEvents(const string &calendar_name, const int page) const
{
    bool is_owner = true;
    ostringstream stream;
    EventRepository event_repository;
    CalendarRepository calendar_repository;
    vector<Event*> events;
    vector<Calendar*> calendars;
    map<string, string> params;
    stream << session->getId();
    params["name"] = calendar_name;
    Calendar * calendar;
    stream.str("");
    string join = " JOIN `shared_events` ON `calendar_id`=`calendar`.`id`";
    stream << " and (`user_id`=\"" << session->getId() << "\" or `shared_id`=\"" << session->getId() << "\")";

    try {
        calendar = calendar_repository.findBy(params, true, stream.str(), join, true)[0];
    } catch (...) { throw CalendarNotFoundException(); }

    try {
        stream.str(""), stream << session->getId();
        params["user_id"] = stream.str();

        if((calendars = calendar_repository.findBy(params, true, "", "", false)).size() == 0) {
            is_owner = false;
        }

		delete calendars[0];
    } catch (...) { is_owner = false; }

    stream.str(""), stream << calendar->getId();
    params.erase("name");
    params.erase("user_id");
    params["calendar_id"] = stream.str(), stream.str("");

    if(!is_owner) {
        stream << " and (`public`=\"2\" or `public`=\"3\")";
    }

    stream << "ORDER BY `datetime_start`" << " LIMIT " << events_per_page << " OFFSET " << ((page - 1) *
            events_per_page);
    events = event_repository.findBy(params, false, stream.str(), "", false);

    delete calendar;
    return events;
}
/**
 * Method which moves event with specific ID on the new datetime position. Method checks if time which user defines is
 * equal to difference of datetime_end and datetime_start. It checks if datetimes are not in the space where is
 * defined life style constants. Then makes update of this event.
 * @param event_id              (int)
 * @param datetime_start        (string)
 * @param datetime_end          (string)
 * @param calendar_name         (string)
 * @param time                  (double)
 * @param last                  (bool)
 * @return bool                 (status code - success or fail)
 */
bool EventController::updateEvent(const int event_id, const string &datetime_start, string &datetime_end,
                                  const string & calendar_name, const double time, bool last) const
{
    ostringstream stream;
    EventRepository event_repository;
    Validation validation;
    EventHelper helper;
    CalendarRepository calendar_repository;
    map<string, string> params;
    params["name"] = calendar_name;
    Calendar * calendar;
    vector<Event*> events;
    calendar = calendar_repository.findBy(params, true, "", "", false)[0];
    params.erase("name");
    stream << event_id;
    bool result;
    params["id"] = stream.str(), stream.str(""), stream << calendar->getId();
    params["calendar_id"] = stream.str();
    delete calendar;

    try {
        events = event_repository.findBy(params, false, "", "", false);

        if(events.size() <= 0) {
            return false;
        }
    } catch (...) { return false; }

    tm start = helper.createDateFromText(start, datetime_start);

	if(!validation.validateDateTime(start)) {
		for(auto it : events) { delete it; }

		return false;
	}

    tm end_date = helper.countNewDate(start, time);

	if(!validation.validateDateTime(end_date) || !validation.isEqualWithTime(datetime_start, datetime_end, time)
	   || validation.isPause(start, time)) {
		for(auto it : events) { delete it; }

		return false;
	}

    if(!last) {
        result = event_repository.updateDatetime(*events[0], datetime_start, helper.createTextFromDate(end_date));
    } else {
        result = event_repository.updateDatetime(*events[0], datetime_start, datetime_end);
    }

    for(auto it : events) { delete it; }

    return result;
}
