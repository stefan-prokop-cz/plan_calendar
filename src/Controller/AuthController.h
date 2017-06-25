#ifndef PLAN_KALENDAR_AUTHCONTROLLER_H
#define PLAN_KALENDAR_AUTHCONTROLLER_H

#include <map>
#include "../View/AuthView.h"
#include "../Model/Repository/UserRepository.h"
#include "../Model/Repository/BaseRepository.h"
#include "../globals.h"
#include "../Service/Exception/DuplicateEntryException.h"
#include "../Service/Exception/UserNotFoundException.h"
using namespace std;

/**
 * Class which operates with user's authentication and registration. It provides methods which rigister / create a new
 * user and method for login
 *
 * @author Stefan Prokop <prokoste>
 */
class AuthController
{
public:
    bool login(const string & username, const string & password);
    int registerUser(const string & name, const string & surname, const string & username, const string & password,
            const string & password_verify);

private:
    User * user;
};

#endif //PLAN_KALENDAR_AUTHCONTROLLER_H