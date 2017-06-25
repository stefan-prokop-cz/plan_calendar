#include "EventRepository.h"

/**
 * Method which represents the creating a new row in database table event. METHOD UNUSED.
 * @param parameters    (map<string, string> - parameters for creating a new row)
 * @return int          (status code - 0: failed)
 */
int EventRepository::create(const map<string, string> &parameters) const { return 0; }
/**
 * Method which represents the creating a new row in database table event. Status codes:
 *      0: failed
 *      1: successfully created
 *      2: some events is created and some not - life style constants or is between another events
 *      3: max datetime - from constant
 *      4: event is between existing events
 * @param event     (Event - this object will be insert into database)
 * @return int      (status code)
 */
int EventRepository::create(const Event &event) const
{
    Insert insert;
    ostringstream stream;
    EventHelper helper;
    int insert_result;
    bool exc = false;
    map<string, string> params;
    stream << " ((`datetime_start` <= '" << event.getDatetimeStart() << "' and `datetime_end` >= '"
           << event.getDatetimeStart() << "') or (`datetime_start` <= '" << event.getDatetimeEnd()
           << "' and `datetime_end` >= '" << event.getDatetimeEnd() << "')) and `calendar_id`='"
           << event.getCalendarId() << "'";

    if(findBy(params, false, stream.str(), "", false).size() > 0) {
        return 4;
    }

    if(event.isRepeatable()) {
        Event repeated_calendar(0, 0, 0, 0, 0, 0, "", "", "", "", false, 0);
        repeated_calendar = event;

        if(event.getRepeatCount() == 0) {
            insert_result = insert.insertOneRow(createEventData(event, 0), "event");

            if(insert_result > 0) {
                while (true) {
                    try {
                        repeated_calendar = helper.makeRepeatedEvent(repeated_calendar);
                    } catch (...) {
                        break;
                    }

                    if(!helper.hasException()) {
                        insert.insertOneRow(createEventData(repeated_calendar, insert_result), "event");
                    } else {
                        exc = true;
                    }

                    helper.setException(false);
                }

                if(exc) {
                    return 2;
                }

                return 1;
            } else {
                return 0;
            }
        }

        for(int i = 0; i <= event.getRepeatCount(); i++) {
            if(i == 0) {
                insert_result = insert.insertOneRow(createEventData(event, 0), "event");

                if(insert_result <= 0) {
                    return 0;
                }
            } else {
                try {
                    repeated_calendar = helper.makeRepeatedEvent(repeated_calendar);

                    if(!helper.hasException()) {
                        insert.insertOneRow(createEventData(repeated_calendar, insert_result), "event");
                    } else {
                        exc = true;
                    }
                } catch(...) {
                    return 3;
                }
            }

            helper.setException(false);
        }
    } else {
        insert_result = insert.insertOneRow(createEventData(event, 0), "event");
    }

    if(exc) {
        return 2;
    }

    if(insert_result > 0) {
        return 1;
    }

    return 0;
}
/**
 * Method which prepares entity Event for inserting into database. It makes map<string, string> the key value storage
 * from entity.
 * @param event     (Event)
 * @param parent    (event parent ID)
 * @return map<string, string>
 */
map<string, string> EventRepository::createEventData(const Event &event, const unsigned int & parent) const
{
    ostringstream stream;
    map<string, string> map_event;

    if(parent != 0) {
        stream << parent;
        map_event["parent_id"] = stream.str(), stream.str("");
    }

    stream << event.getCalendarId();
    map_event["calendar_id"] = stream.str();
    stream.str(""), stream << event.getStatus();
    map_event["status"] = stream.str();
    stream.str(""), stream << event.getRepeatCount();
    map_event["repeat_count"] = stream.str();
    stream.str(""), stream << event.getPublicEvent();
    map_event["public"] = stream.str();
    map_event["name"] = event.getName();
    map_event["description"] = event.getDescription();
    map_event["datetime_start"] = event.getDatetimeStart();
    map_event["datetime_end"] = event.getDatetimeEnd();
    map_event["repeatable"] = (event.isRepeatable()) ? "1" : "0";
    stream.str(""), stream << event.getRepeatConst();
    map_event["repeat_const"] = stream.str();

    return map_event;
}
/**
 * Method which represents the select query in database table event.
 * @param params                (map<string, string> - key, value - parameters for select)
 * @param one_result            (bool - if you want only one result)
 * @param custom_query          (string - custom SQL query)
 * @param join                  (string - custom SQL JOIN query)
 * @param or_select             (bool - params used as OR in query)
 * @return vector<Event*>       (found events)
 */
 vector<Event*> EventRepository::findBy(const map<string, string> &params, bool one_result, const string &custom_query,
                                        const string &join, bool or_select) const
{
    Select select;
    vector<Event*> events;
    MYSQL_RES * result;
    MYSQL_ROW row;
    result = select.findBy(params, "event", false, custom_query, "", false);

    while((row = mysql_fetch_row(result)) != NULL) {
        if(mysql_num_fields(result) == 12) {
            events.push_back(new Event(atoi(row[0]), (row[1]) ? atoi(row[1]) : 0, atoi(row[9]), atoi(row[2]),
                                       atoi(row[8]), atoi(row[3]), row[4], row[5], row[10], row[11],
                                       (bool) atoi(row[6]), atof(row[7])));
        }
    }

    mysql_free_result(result);

    return events;
}
/**
 * Method which updates event's start and end datetime
 * @param event             (Event)
 * @param datetime_start    (string - new start datetime)
 * @param datetime_end      (string - new end datetime)
 * @return bool             (true: updated, false: failed)
 */
bool EventRepository::updateDatetime(Event &event, const string &datetime_start, const string &datetime_end)
{
    if(event.getStatus() != 3) {
        return false;
    }

    Update update;
    ostringstream stream;
    event.setDatetimeStart(datetime_start);
    event.setDatetimeEnd(datetime_end);
    stream << " `id`=\"" << event.getId() << "\"";

    return update.update(createEventData(event, 0), "event", stream.str());
}
