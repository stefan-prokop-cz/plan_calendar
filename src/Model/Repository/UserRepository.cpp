#include "UserRepository.h"

/**
 * Method which represents the select query in database table user.
 * @param params            (map<string, string> - key, value - parameters for select)
 * @param one_result        (bool - if you want only one result)
 * @param custom_query      (string - custom SQL query)
 * @param join              (string - custom SQL JOIN query)
 * @param or_select         (bool - params used as OR in query)
 * @throws UserNotFoundException
 * @return vector<User*>    (found users)
 */
vector<User*> UserRepository::findBy(const map<string, string> &params, bool one_result, const string &custom_query,
                                    const string &join, bool or_select) const
{
    MYSQL_RES * result;
    MYSQL_ROW row;
    vector<User*> users;
    result = select.findBy(params, "user", one_result, custom_query, join, or_select);

    while((row = mysql_fetch_row(result)) != NULL) {
        if((int) mysql_num_fields(result) == 6) {
            users.push_back(new User(atoi(row[0]), row[1], row[2], row[3], row[4], row[5]));
        }
    }

    mysql_free_result(result);

    if(users.size() <= 0) {
        throw UserNotFoundException();
    }

    return users;
}
/**
 * Method which represents the creating a new row in database table user.
 * @param parameters    (map<string, string> - key, value parameters which will be inserted)
 * @throws DuplicateEntryException
 * @return int          (status code, 1: succesfully created)
 */
int UserRepository::create(const map<string, string> &parameters) const
{
    Insert insert;

    if(insert.insertOneRow(parameters, "user") == 0) {
        throw DuplicateEntryException();
    }

    return 1;
}