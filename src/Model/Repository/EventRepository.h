#ifndef PLAN_KALENDAR_EVENTREPOSITORY_H
#define PLAN_KALENDAR_EVENTREPOSITORY_H

#include <ctime>
#include "BaseRepository.h"
#include "../Entity/Event.h"
#include "../../Service/DI/EventHelper.h"

/**
 * Class which works with the database table event and with the entity Event. The parent class is BaseRepository.
 * @author Stefan Prokop <prokoste>
 */
class EventRepository : public BaseRepository<Event>
{
public:
    virtual int create(const map<string, string> & parameters) const;
    virtual int create(const Event & event) const;
    virtual vector<Event*> findBy(const map<string, string> & params, bool one_result, const string & custom_query,
                              const string & join, bool or_select) const;
    bool updateDatetime(Event & event, const string & datetime_start, const string & datetime_end);

private:
    map<string, string> createEventData(const Event & calendar, const unsigned int & parent) const;
};

#endif //PLAN_KALENDAR_EVENTREPOSITORY_H