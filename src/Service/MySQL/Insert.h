#ifndef PLAN_KALENDAR_INSERT_H
#define PLAN_KALENDAR_INSERT_H

#include "Connector.h"
#include "../../globals.h"
#include "../Exception/DuplicateEntryException.h"
#include <iostream>
#include <map>
#include <string>
#include <mysql/mysql.h>
using namespace std;

/**
 * Class which propose method which insert data into database.
 * @author Stefan Prokop <prokoste>
 */
class Insert {
public:
    Insert();
    ~Insert();
    int insertOneRow(const map<string, string> & data, const string & table_name);
};

#endif //PLAN_KALENDAR_INSERT_H