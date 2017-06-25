#include "EventHelper.h"

/**
 * Method which represents the EventHelper constructor. It sets the variable life_style_exception to false. This
 * variable is used for indicating the error when user creates new events. Default value is false.
 */
EventHelper::EventHelper() : life_style_exception(false) {}
/**
 * Method which creates next datetime for repeated event. It count the time between old and repeated event and store it
 * into event.
 * @param event (Event)
 * @throws MaxDateTimeException
 * @return Event
 */
Event& EventHelper::makeRepeatedEvent(Event &event)
{
    Validation validation;
    ostringstream stream;
    tm datetime, start_date;
    datetime = createDateFromText(datetime, event.getDatetimeEnd());
    start_date = createDateFromText(start_date, event.getDatetimeStart());
    double start_hours = getHoursFromDate(start_date), end_hours = getHoursFromDate(datetime);
    double result_hours = end_hours - start_hours + 0.0;

    try {
        start_date = countNewDate(datetime, event.getRepeatConst());
        datetime = countNewDate(datetime, result_hours);
    } catch(...) {
        throw MaxDateTimeException();
    }

    string date_s = createTextFromDate(start_date), date_e = createTextFromDate(datetime);
    event.setDatetimeStart(date_s);
    event.setDatetimeEnd(date_e);

    return event;
}
/**
 * Method which count the next datetime for event. It add hours. After these hours will be event repeated. These hours
 * defined user.
 * @param datetime      (tm - datetime)
 * @param hours_start   (double - hours)
 * @throws MaxDateTimeException
 * @return tm           (new datetime)
 */
tm& EventHelper::countNewDate(tm &datetime, const double hours_start)
{
    Validation validation;
    int seconds = hours_start * 60 * 60;
    datetime.tm_sec = datetime.tm_sec + seconds;
    tm testing;
    time_t now = time(0);
    testing = *localtime(&now);
    int days_in_month = validation.getDaysInMonth(datetime.tm_mon);

    if(datetime.tm_sec > 59) {
        int minutes = datetime.tm_sec / 60;
        datetime.tm_sec = datetime.tm_sec % 60;
        datetime.tm_min = datetime.tm_min + minutes;

        if(datetime.tm_min > 59) {
            int hours = datetime.tm_min / 60;
            datetime.tm_min = datetime.tm_min % 60;
            datetime.tm_hour = datetime.tm_hour + hours;

            if (datetime.tm_hour >= 24) {
                int days = datetime.tm_hour / 24;
                datetime.tm_hour = datetime.tm_hour % 24;
                datetime.tm_mday = datetime.tm_mday + days;

                if (datetime.tm_mday > days_in_month) {
                    int month = datetime.tm_mday / days_in_month;
                    datetime.tm_mday = datetime.tm_mday % days_in_month;
                    datetime.tm_mon = datetime.tm_mon + month;

                    if (datetime.tm_mon > 12) {
                        int years = datetime.tm_mon / 12;
                        datetime.tm_mon = datetime.tm_mon % 12;
                        datetime.tm_year = datetime.tm_year + years;

                        if (datetime.tm_year > (testing.tm_year + 1900 + max_years)) {
                            throw MaxDateTimeException();
                        }
                    }
                }
            }
        }
    }

    if(validation.isPause(datetime, 0)) {
        life_style_exception = true;
    }

    return datetime;
}
/**
 * Method which represents the getter. It returns status of variable life_style_exception
 * @return bool
 */
bool EventHelper::hasException() const { return life_style_exception; }
/**
 * Method which represents the setter. It sets the variable life_style_exception
 * @param exc
 */
void EventHelper::setException(bool exc) { life_style_exception = exc; }
/**
 * Method which find the closest or relevant date for a potential new event.
 * @param calendar_name     (string - name of the calendar)
 * @param relevant          (bool - true: relevant dates between defined hours, false: closest dates - only one result)
 * @param hours             (double - how many hours will user need for event)
 * @throws CalendarNotFoundException
 * @return vector<string>   (relevant dates in string format)
 */
vector<string> EventHelper::findClosestDate(const string & calendar_name, bool relevant, const double hours) const
{
    ostringstream stream;
    EventRepository event_repository;
    CalendarRepository calendar_repository;
    Calendar * calendar;
    vector<string> events;
    tm today;
    time_t now = time(0);
    today = *localtime(&now);
    today.tm_year = today.tm_year + 1900;
    today.tm_mon = today.tm_mon + 1;

    map<string, string> params;
    stream << session->getId();
    params["name"] = calendar_name, params["user_id"] = stream.str();

    try {
        calendar = calendar_repository.findBy(params, true, "", "", false)[0];
    } catch (...) {
        throw CalendarNotFoundException();
    }

    stream.str(""), stream << calendar->getId();
    params.erase("name"), params.erase("user_id");
    params["calendar_id"] = stream.str();

    string d = createTextFromDate(today);
    string custom_query = " and `datetime_start` > \"" + d + "\" ORDER BY `datetime_start`";

    delete calendar;
    return countClosestDate(event_repository.findBy(params, false, custom_query, "", false), relevant, hours);
}
/**
 * Method which count the closest or relevant date. It takes found events and tests if these events are relevant. Then
 * stores these events into vector<string> and returns.
 * @param events        (vector<Event*>)
 * @param relevant      (bool)
 * @param hours         (double)
 * @return vector<string>
 */
vector<string> EventHelper::countClosestDate(const vector<Event*> &events, bool relevant, const double hours) const
{
    Validation validation;
    ostringstream stream;
    vector<string> date;
    tm today, start, end, last_date;
    double start_hours, end_hours;
    time_t now = time(0);
    today = *localtime(&now);
    today.tm_year = today.tm_year + 1900;
    today.tm_mon = today.tm_mon + 1;
    last_date = today;
    last_date.tm_year += max_years, last_date.tm_mon = 12, last_date.tm_mday = validation.getDaysInMonth(12),
            last_date.tm_hour = 23, last_date.tm_min = 59, last_date.tm_sec = 59;

    for(size_t i = 0; i < events.size(); i++) {
        if(i == 0) {
            end = today;
        } else {
            end = createDateFromText(end, events[i - 1]->getDatetimeEnd());
        }

        start = createDateFromText(start, events[i]->getDatetimeStart());
        start_hours = getHoursFromDate(start);
        end_hours = getHoursFromDate(end);

        if((start_hours - end_hours) >= hours) {
            if((start_hours - end_hours - hours) > 4.0 ||
                    (!validation.isPause(start, (relevant) ? (start_hours - end_hours) : 0) &&
                            !validation.isPause(end, (relevant) ? (start_hours - end_hours) : 0))) {

                if (i == 0) {
                    string result = createTextFromDate(end);
                    date.push_back(result);
                } else {
                    date.push_back(events[i - 1]->getDatetimeEnd());
                }

                date.push_back(events[i]->getDatetimeStart());

                if (!relevant) {
                    break;
                }
            }
        }

        if((i + 1) >= events.size()) {
            end_hours = getHoursFromDate(last_date);
            start_hours = getHoursFromDate(start);

            if((end_hours - start_hours) >= hours) {
                date.push_back(events[i]->getDatetimeEnd());
                date.push_back("Konec");
            }

            if(!relevant) {
                break;
            }
        }
    }

    for(auto it : events) {
        delete it;
    }

    return date;
}
/**
 * Method which creates string text from a struct tm datetime.
 * @param time (struct tm)
 * @return string
 */
string EventHelper::createTextFromDate(const tm &time) const
{
    ostringstream stream;
    stream << time.tm_year << "-" << time.tm_mon << "-" << time.tm_mday << " " << time.tm_hour << ":" << time.tm_min
           << ":" << time.tm_sec;

    return stream.str();
}
/**
 * Method which takes struct tm parameter - it means the output format and string parameter text. It converts text into
 * struct tm format
 * @param datetime      (tm - struct)
 * @param text          (string)
 * @return tm           (tm - struct)
 */
tm& EventHelper::createDateFromText(tm &datetime, const string &text) const
{
    int result = sscanf(text.c_str(), "%d-%d-%d %d:%d:%d", &datetime.tm_year, &datetime.tm_mon, &datetime.tm_mday,
                        &datetime.tm_hour, &datetime.tm_min, &datetime.tm_sec);

    if(result != 6) {
        datetime.tm_year = 1500;
    }

    return datetime;
}
/**
 * Method which takes struct tm parameter datetime. Method count the hours from datetime. Then returns the result.
 * @param datetime  (tm - struct)
 * @return double   (hours)
 */
double EventHelper::getHoursFromDate(const tm &datetime) const
{
    Validation validation;
    double result;

    result = ((datetime.tm_year + 0.0) * 365 * 24) +
            ((datetime.tm_mon + 0.0) * validation.getDaysInMonth(datetime.tm_mon) * 24) +
            ((datetime.tm_mday + 0.0) * 24) + (datetime.tm_hour + 0.0) + ((datetime.tm_min + 0.0) / 60) +
            ((datetime.tm_sec + 0.0) / 60 / 60);

    return result;
}