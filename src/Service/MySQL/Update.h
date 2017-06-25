#ifndef PLAN_KALENDAR_UPDATE_H
#define PLAN_KALENDAR_UPDATE_H

#include "Connector.h"
#include "../../globals.h"
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <mysql/mysql.h>

/**
 * Class which propose the method which creates an update query and updates rows in database table
 * @author Stefan Prokop <prokoste>
 */
class Update
{
public:
    bool update(const map<string, string> & parameters, const string & table, const string & where) const;
};

#endif //PLAN_KALENDAR_UPDATE_H