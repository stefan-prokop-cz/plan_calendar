#ifndef PLAN_KALENDAR_LIFESTYLEREPOSITORY_H
#define PLAN_KALENDAR_LIFESTYLEREPOSITORY_H

#include <vector>
#include "BaseRepository.h"
#include "../Entity/LifeStyle.h"

/**
 * Class which represents the LifeStyle repository. It operates with LifeStyle entity and works with database table
 * lifestyle. It is extended by BaseRepository class.
 * @author Stefan Prokop <prokoste>
 */
class LifeStyleRepository : public BaseRepository<LifeStyle>
{
public:
    virtual int create(const map<string, string> & parameters) const;
    virtual vector<LifeStyle*> findBy(const map<string, string> & params, bool one_result, const string & custom_query,
                              const string & join, bool or_select) const;
};

#endif //PLAN_KALENDAR_LIFESTYLEREPOSITORY_H