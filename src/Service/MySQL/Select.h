#ifndef PLAN_KALENDAR_SELECT_H
#define PLAN_KALENDAR_SELECT_H

#include "Connector.h"
#include "../../globals.h"
#include <iostream>
#include <map>
#include <string>
#include <mysql/mysql.h>
using namespace std;

/**
 * Class which propose method which finding rows in database tables.
 * @author Stefan Prokop <prokoste>
 */
class Select
{
public:
    Select();
    ~Select();
    MYSQL_RES * findAll(const string & table) const;
    MYSQL_RES * findBy(const map<string, string> & parameters, const string & table, bool one_result,
                        const string & custom_query, const string & join, bool or_select) const;
};

#endif //PLAN_KALENDAR_SELECT_H