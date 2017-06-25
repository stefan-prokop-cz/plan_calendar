#include "AuthController.h"

/**
 * Method which takes string parameters username and password. These parameters are used for authentication. Method
 * calls model class and send auth parameters. Then returns false if user is not found or true if is found and stores
 * found user to the session.
 * @param username (string)
 * @param password (string)
 * @return bool
 */
bool AuthController::login(const string &username, const string &password)
{
    map<string, string> credentials;
    credentials["username"] = username;
    credentials["password"] = password;
    UserRepository repository;

    try {
        user = repository.findBy(credentials, true, "", "", false)[0];

        if(user->getUsername() == username) {
            if(session_exists) {
                delete session;
            }

            session = user;
            session_exists = true;
            terminal_text = username + "> ";

            return true;
        }
    } catch (UserNotFoundException ex) {
        return false;
    }

    return false;
}
/**
 * Method which takes string parameters name, surname, username, password and password_verify. Method validate these
 * parameters (password is equal to password_verify) and then returns status code:
 *      0: user with this username is already exists
 *      1: password is not equal to password_verify
 *      2: successful registration
 *      3: some parameter is empty
 * - 0, 1 and 3 means that new user was not created
 * - 2 means that new user was successfully created
 * @param name              (string)
 * @param surname           (string)
 * @param username          (string)
 * @param password          (string)
 * @param password_verify   (string)
 * @return int              (status code)
 */
int AuthController::registerUser(const string &name, const string &surname, const string &username,
                                  const string &password, const string &password_verify)
{
    if(password != password_verify) {
        return 1;
    }

    if(name == "" || surname == "" || username == "" || password == "") {
        return 3;
    }

    map<string, string> data;
    data["name"] = name;
    data["surname"] = surname;
    data["username"] = username;
    data["password"] = password;

    UserRepository repository;

    try {
        repository.create(data);

        return 2;
    } catch (DuplicateEntryException ex) {
        return 0;
    }
}