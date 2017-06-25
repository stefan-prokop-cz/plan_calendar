#include "Insert.h"

/**
 * Method which represents the Insert constructor.
 */
Insert::Insert() {}
/**
 * Method which represents the Insert destructor.
 */
Insert::~Insert() {}
 /**
  * Method which creates new row in database table.
  * @param data         (map<string, string> - key, value storage with data - this data will be inserted)
  * @param table_name   (string - name of the table)
  * @return int         (status - 0: failed, mysql_insert_id)
  */
int Insert::insertOneRow(const map<string, string> & data, const string & table_name)
{
    int count = 0;
    string columns = "", values = "", query;

    for(const auto iterator : data) {
        if(count > 0) {
            columns += ", ", values += ", ";
        }

        columns += iterator.first;
        values += "'";
        values += iterator.second;
        values += "'";
        count++;
    }

    query = "INSERT INTO `" + table_name + "` (" + columns + ") VALUES (" + values + ")";
    mysql_query(connector->getConnection(), query.c_str());
    string error = mysql_error(connector->getConnection());

    if(error.size() > 0) {
        return 0;
    }

    return mysql_insert_id(connector->getConnection());
}