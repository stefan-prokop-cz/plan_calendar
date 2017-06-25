#include "User.h"

/**
 * Method which represents the object constructor.
 * @param id            (int - user ID from database)
 * @param username      (string - username - UNIQUE identifier)
 * @param password      (string - user's password)
 * @param name          (string - user's name)
 * @param surname       (string - user's surname)
 * @param time          (string - timestamp - created at)
 */
User::User(const int &id, const string &username, const string &password, const string &name, const string &surname,
           const string &time)
        : id(id), username(username), password(password), name(name), surname(surname), created_at(time) {}
/**
 * Method which represents the getter. It returns the user ID.
 * @return int (id)
 */
int User::getId() const { return id; }
/**
 * Method which represents the getter. It returns the user's username.
 * @return string (username)
 */
string User::getUsername() const { return username; }