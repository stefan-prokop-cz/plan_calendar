#include "Update.h"

/**
 * Method which creates an update query and update defined rows in defined table.
 * @param parameters    (map<string, string> key, value storage with new data)
 * @param table         (string - database table name)
 * @param where         (string - where condition)
 * @return bool         (status code - 0: failed, 1: successfully updated)
 */
bool Update::update(const map<string, string> &parameters, const string &table, const string & where) const
{
    ostringstream stream;
    int count = 0;
    string values = "", query;

    for(const auto & iterator : parameters) {
        if(count > 0) {
            values += ", ";
        }

        values += ("`" + iterator.first + "`='" + iterator.second + "'");
        count++;
    }

    stream << "UPDATE `" << table << "` SET " << values << " WHERE " << where;
    query = stream.str();
    mysql_query(connector->getConnection(), query.c_str());
    string error = mysql_error(connector->getConnection());

    if(error.size() > 0) {
        return false;
    }

    return true;
}