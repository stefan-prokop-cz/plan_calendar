#ifndef PLAN_KALENDAR_CALENDAR_H
#define PLAN_KALENDAR_CALENDAR_H

#include <string>
using namespace std;

/**
 * Class which represents database table calendar. It means the entity.
 * @author Stefan Prokop <prokoste>
 */
class Calendar
{
public:
    Calendar(const string & name, const int id, const int user_id);
    string getName() const;
    int getId() const;
    int getUserId() const;

private:
    string name;
    int id, user_id;
};

#endif //PLAN_KALENDAR_CALENDAR_H