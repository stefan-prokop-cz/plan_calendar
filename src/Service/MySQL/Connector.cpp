#include "Connector.h"

/**
 * Method which represents the Connector constructor. This method connect to the database and stores connection to the
 * variable connection.
 */
Connector::Connector()
{
    connection = mysql_init(0);
    bool result = (mysql_real_connect(connection, SERVER, USER, PASSWORD, SCHEMA, PORT, NULL, 0));

    if(!result) {
        cerr << mysql_error(connection) << endl;
        mysql_close(connection);

        exit(500);
    }
}
/**
 * Method which represents the Connection destructor. This method close the connection with database.
 */
Connector::~Connector() { mysql_close(connection); }
/**
 * Method which represents the getter. It returns the MYSQL* "object"
 * @return MYSQL*
 */
MYSQL* Connector::getConnection() const { return connection; }