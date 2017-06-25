#ifndef PLAN_KALENDAR_EVENT_H
#define PLAN_KALENDAR_EVENT_H

#include <string>
using namespace std;

/**
 * Class which represents the entity class. It is the class mapped from database - table event.
 * @author Stefan Prokop <prokoste>
 */
class Event
{
public:
    Event(const int id, const int parent_id, const int calendar_id, const int status, const int repeat_count,
          const int public_event, const string & name, const string & description, const string & datetime_start,
          const string & datetime_end, bool repeatable, const double repeat_const);
    int getId() const;
    int getParentId() const;
    int getCalendarId() const;
    int getStatus() const;
    int getRepeatCount() const;
    int getPublicEvent() const;
    string getName() const;
    string getDescription() const;
    string getDatetimeStart() const;
    string getDatetimeEnd() const;
    bool isRepeatable() const;
    double getRepeatConst() const;
    void setDatetimeStart(const string & start);
    void setDatetimeEnd(const string & end);
    Event & operator = (const Event & event);
private:
    int id, parent_id, calendar_id, status, repeat_count, public_event;
    string name, description, datetime_start, datetime_end;
    bool repeatable;
    double repeat_const;
};

#endif //PLAN_KALENDAR_EVENT_H