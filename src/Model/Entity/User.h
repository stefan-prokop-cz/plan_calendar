#ifndef PLAN_KALENDAR_USER_H
#define PLAN_KALENDAR_USER_H

#include <string>
using namespace std;

/**
 * Class which represents the user entity. It represents the user database table.
 * @author Stefan Prokop <prokoste>
 */
class User
{
public:
    User(const int &id, const string &username, const string &password, const string &name, const string &surname,
         const string &time);
    int getId() const;
    string getUsername() const;
private:
    int id;
    string username, password, name, surname, created_at;
};

#endif //PLAN_KALENDAR_USER_H