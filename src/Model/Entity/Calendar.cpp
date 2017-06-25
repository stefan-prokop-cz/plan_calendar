#include "Calendar.h"

/**
 * Method which represents the constructor. It creates the object with string parameter name, int ID and user_id (who
 * is owner)
 * @param name      (string)
 * @param id        (int)
 * @param user_id   (int)
 */
Calendar::Calendar(const string &name, const int id, const int user_id) : name(name), id(id), user_id(user_id) {}
/**
 * Method which represents the getter. It returns the name of the calendar.
 * @return string (calendar name)
 */
string Calendar::getName() const { return name; }
/**
 * Method which represents the getter. It returns the calendar ID (from database).
 * @return int (calendar ID)
 */
int Calendar::getId() const { return id; }
/**
 * Method which represents the getter. It returns user_id from database (owner of calendar)
 * @return int (user id)
 */
int Calendar::getUserId() const { return user_id; }