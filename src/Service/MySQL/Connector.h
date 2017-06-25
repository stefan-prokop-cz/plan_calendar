#ifndef PLAN_KALENDAR_CONNECTOR2_H
#define PLAN_KALENDAR_CONNECTOR2_H

#include <mysql/mysql.h>
#include <iostream>
using namespace std;

/**
 * Constant SERVER - MySQL server address
 */
#define SERVER "127.0.0.1"
/**
 * Constant PORT - MySQL server address port
 */
#define PORT 3306
/**
 * Constant USER - MySQL server user
 */
#define USER "root"
/**
 * Constant PASSWORD - MySQL password for server user
 */
#define PASSWORD ""
/**
 * Constant SCHEMA - MySQL table or schema name
 */
#define SCHEMA "plan_calendar"

/**
 * Class which helps with creating the database connection.
 * @author Stefan Prokop <prokoste>
 */
class Connector
{
public:
    Connector();
    ~Connector();
    MYSQL * getConnection() const;
private:
    MYSQL * connection;
};

#endif //PLAN_KALENDAR_CONNECTOR2_H
