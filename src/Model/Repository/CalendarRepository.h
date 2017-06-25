#ifndef PLAN_KALENDAR_CALENDARREPOSITORY_H
#define PLAN_KALENDAR_CALENDARREPOSITORY_H

#include "BaseRepository.h"
#include "../Entity/Calendar.h"
#include "UserRepository.h"

/**
 * Class which operates with database table calendar. This class works with entity Calendar. Parent class is
 * BaseRepository.
 * @author Stefan Prokop <prokoste>
 */
class CalendarRepository : public BaseRepository<Calendar>
{
public:
    virtual int create(const map<string, string> & parameters) const;
    virtual vector<Calendar*> findBy(const map<string, string> & params, bool one_result, const string & custom_query,
                                     const string & join, bool or_select) const;
    bool share(const string & username, const int calendar_id) const;
};

#endif //PLAN_KALENDAR_CALENDARREPOSITORY_H