#ifndef PLAN_KALENDAR_USERREPOSITORY_H
#define PLAN_KALENDAR_USERREPOSITORY_H

#include <vector>
#include "BaseRepository.h"
#include "../Entity/User.h"

/**
 * Class represents the User repository. This class works with the entity User and called database queries to user
 * table. Parent class is BaseRepository which defines methods.
 *
 * @author Stefan Prokop <prokoste>
 */
class UserRepository : public BaseRepository<User>
{
public:
    virtual int create(const map<string, string> & parameters) const override;
    virtual vector<User*> findBy(const map<string, string> & params, bool one_result, const string & custom_query,
                     const string & join, bool or_select) const override;
private:
    Select select;
};

#endif //PLAN_KALENDAR_USERREPOSITORY_H