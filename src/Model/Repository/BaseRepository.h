#ifndef PLAN_KALENDAR_BASEREPOSITORY_H
#define PLAN_KALENDAR_BASEREPOSITORY_H

#include <mysql/mysql.h>
#include <iostream>
#include <map>
#include <sstream>
#include "../../Service/MySQL/Connector.h"
#include "../../Service/MySQL/Select.h"
#include "../../Service/MySQL/Insert.h"
#include "../../Service/MySQL/Update.h"
#include "../../Service/Exception/CalendarNotFoundException.h"
#include "../../Service/Exception/DuplicateEntryException.h"
#include "../../Service/Exception/LifeStyleException.h"
#include "../../Service/Exception/MaxDateTimeException.h"
#include "../../Service/Exception/UserNotFoundException.h"
using namespace std;

/**
 * Abstract class which represents the parent class for all repositories. This class works with entity classes. It
 * proposes the abstract methods.
 * @tparam T (means entity class)
 * @author Stefan Prokop <prokoste>
 */
template <class T>
class BaseRepository
{
public:
    virtual ~BaseRepository() {};
    virtual int create(const map<string, string> & parameters) const = 0;
    virtual vector<T*> findBy(const map<string, string> & params, bool one_result, const string & custom_query,
                     const string & join, bool or_select) const = 0;
};

#endif //PLAN_KALENDAR_BASEREPOSITORY_H