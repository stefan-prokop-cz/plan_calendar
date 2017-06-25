#include "CalendarRepository.h"

/**
 * Method which represents the creating a new row in database table calendar.
 * @param parameters    (map<string, string> - parameters for creating a new row)
 * @return int          (status code - 1: successfully created, 0: failed)
 */
int CalendarRepository::create(const map<string, string> &parameters) const
{
    Insert insert;

    return insert.insertOneRow(parameters, "calendar");
}
/**
 * Method which represents the select query in database table calendar.
 * @param params                (map<string, string> - key, value - parameters for select)
 * @param one_result            (bool - if you want only one result)
 * @param custom_query          (string - custom SQL query)
 * @param join                  (string - custom SQL JOIN query)
 * @param or_select             (bool - params used as OR in query)
 * @throws CalendarNotFoundException
 * @return vector<Calendar*>    (found calendars)
 */
vector<Calendar*> CalendarRepository::findBy(const map<string, string> &params, bool one_result,
                                             const string &custom_query, const string &join, bool or_select) const
{
    Select select;
    MYSQL_ROW row;
    MYSQL_RES * result;
    vector<Calendar*> calendars;

    if(one_result) {
        result = select.findBy(params, "calendar", true, custom_query, join, or_select);
    } else {
        result = select.findBy(params, "calendar", false, custom_query, join, or_select);
    }

    while((row = mysql_fetch_row(result)) != NULL) {
        if(row[0] && row[1] && row[2]) {
            calendars.push_back(new Calendar(row[2], atoi(row[0]), atoi(row[1])));
        }
    }

    mysql_free_result(result);

    if(calendars.size() <= 0) {
        throw CalendarNotFoundException();
    }

    return calendars;
}
/**
 * Method which shares calendar with another users. It works with database table shared_events.
 * @param username      (string - username of the users for sharing)
 * @param calendar_id   (calendar ID for sharing)
 * @return bool         (status - true: successfully shared, false: failed)
 */
bool CalendarRepository::share(const string &username, const int calendar_id) const
{
    Insert insert;
    Select select;
    UserRepository repository;
    ostringstream stream;
    map<string, string> params;
    params["username"] = username;
    stream << calendar_id;
    User * user;

    try {
        user = repository.findBy(params, true, "", "", false)[0];
    } catch (...) {
        return false;
    }

    params.erase("username"), params["calendar_id"] = stream.str(), stream.str(""), stream << session->getId();
    params["owner_id"] = stream.str(), stream.str(""), stream << user->getId(), params["shared_id"] = stream.str();

    delete user;
    return (bool) insert.insertOneRow(params, "shared_events");
}