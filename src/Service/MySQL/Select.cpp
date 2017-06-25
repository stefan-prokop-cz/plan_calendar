#include "Select.h"

/**
 * Method which represents the Select constructor.
 */
Select::Select() {}
/**
 * Method which represents the Select destructor
 */
Select::~Select() {}
/**
 * Method which find all rows from defined database table.
 * @param table     (string)
 * @return MYSQL_RES*
 */
MYSQL_RES* Select::findAll(const string &table) const
{
    string query = "SELECT * FROM `" + table + "`";
    mysql_query(connector->getConnection(), query.c_str());
    string error = mysql_error(connector->getConnection());

    if(error.size() > 0) {
        return NULL;
    }

    return mysql_store_result(connector->getConnection());
}
/**
 * Method which find all rows from database table which meet the conditions
 * @param params                (map<string, string> - key, value - parameters for select)
 * @param one_result            (bool - if you want only one result)
 * @param custom_query          (string - custom SQL query)
 * @param join                  (string - custom SQL JOIN query)
 * @param or_select             (bool - params used as OR in query)
 * @return MYSQL_RES*
 */
MYSQL_RES* Select::findBy(const map<string, string> &parameters, const string &table, bool one_result,
                            const string & custom_query, const string & join, bool or_select = false) const
{
    int count = 0;
    string to_select = "";

    for (auto iterator : parameters) {
        if (count != 0) {
            to_select += (or_select) ? " or " : " and ";
        }

        to_select += ("`" + iterator.first + "`=\"" + iterator.second + "\"");
        count++;
    }

    string query = "SELECT * FROM `" + table + "` " + join + " WHERE " + to_select + custom_query;

    if(one_result) {
        query += " LIMIT 1";
    }

    mysql_query(connector->getConnection(), query.c_str());
    string error = mysql_error(connector->getConnection());

    if(error.size() > 0) {
        return NULL;
    }

    return mysql_store_result(connector->getConnection());
}
