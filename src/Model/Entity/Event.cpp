#include "Event.h"

/**
 * Method which represents the object constructor. It takes parameters same as are in the database table and it sets the
 * variables.
 * @param id                (int - event ID)
 * @param parent_id         (int - parent event ID - if is repeated or NULL if is not repeated)
 * @param calendar_id       (int - ID of the calendar)
 * @param status            (int - status code - 1: compulsory, 2: optional, 3: movable)
 * @param repeat_count      (int - indicates, how many repetitions will be created, -1 means infinity)
 * @param public_event      (int - the column public - 1: private, 2: public, 3: shared - status code #2)
 * @param name              (string - event name)
 * @param description       (string - event description)
 * @param datetime_start    (string - start at)
 * @param datetime_end      (string - end at)
 * @param repeatable        (bool - is repeatable)
 * @param repeat_const      (double - after how many hours will be created the repetition)
 */
Event::Event(const int id, const int parent_id, const int calendar_id, const int status, const int repeat_count,
             const int public_event, const string &name, const string &description, const string &datetime_start,
             const string &datetime_end, bool repeatable, const double repeat_const)
        : id(id), parent_id(parent_id), calendar_id(calendar_id), status(status), repeat_count(repeat_count),
          public_event(public_event), name(name), description(description), datetime_start(datetime_start),
          datetime_end(datetime_end), repeatable(repeatable), repeat_const(repeat_const) {}
/**
 * Method which represents the getter. It returns the repeat_const variable.
 * @return double (repeat_const)
 */
double Event::getRepeatConst() const { return repeat_const; }
/**
 * Method which represents the getter. It returns the public status of the event.
 * @return int (public_event)
 */
int Event::getPublicEvent() const { return public_event; }
/**
 * Method which represents the getter. It returns the state - true if is event repeatable of false if is not.
 * @return bool (repeatable)
 */
bool Event::isRepeatable() const { return repeatable; }
/**
 * Method which represents the getter. It returns the datetime_end variable.
 * @return string (datetime_end)
 */
string Event::getDatetimeEnd() const { return datetime_end; }
/**
 * Method which represents the getter. It returns the datetime_start variable.
 * @return string (datetime_start)
 */
string Event::getDatetimeStart() const { return datetime_start; }
/**
 * Method which represents the getter. It returns the event description.
 * @return string (description)
 */
string Event::getDescription() const { return description; }
/**
 * Method which represents the getter. It returns the event name.
 * @return string (name)
 */
string Event::getName() const { return name; }
/**
 * Method which represents the getter. It returns the repeat_count variable.
 * @return int (repeat_count)
 */
int Event::getRepeatCount() const { return repeat_count; }
/**
 * Method which represents the getter. It returns the status code of the event. 1: compulsory, 2: optional, 3: movable.
 * @return int (status)
 */
int Event::getStatus() const { return status; }
/**
 * Method which represents the getter. It returns the calendar ID where is event created.
 * @return int (calendar ID)
 */
int Event::getCalendarId() const { return calendar_id; }
/**
 * Method which represents the getter. It returns the event ID from database.
 * @return int (id)
 */
int Event::getId() const { return id; }
/**
 * Method which represents the getter. It returns the parent ID of the event.
 * @return int (parent_id)
 */
int Event::getParentId() const { return parent_id; }
/**
 * Method which represents the operator =. It copies the event.
 * @param event         (Event)
 * @return Event
 */
Event& Event::operator=(const Event &event)
{
    if(this == &event) {
        return *this;
    }

    id = event.id, parent_id = event.parent_id, calendar_id = event.calendar_id, status = event.status,
            repeat_count = event.repeat_count, name = event.name, description = event.description,
            datetime_start = event.datetime_start, datetime_end = event.datetime_end,
            repeatable = event.repeatable, repeat_const = event.repeat_const, public_event = event.public_event;

    return *this;
}
/**
 * Method which represents the setter. It sets the variable datetime_start. It takes string parameter with new start
 * datetime.
 * @param start (string)
 */
void Event::setDatetimeStart(const string &start) { datetime_start = start; }
/**
 * Method which represents the setter. It sets the variable datetime_end. It takes parameter with new end datetime.
 * @param end (string)
 */
void Event::setDatetimeEnd(const string &end) { datetime_end = end; }