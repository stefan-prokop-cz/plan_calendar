#include "LifeStyleRepository.h"

/**
 * Method which represents the creating a new row in database table calendar. METHOD IS UNUSED.
 * @param parameters    (map<string, string> - parameters for creating a new row)
 * @return int          (status code - 0: failed)
 */
int LifeStyleRepository::create(const map<string, string> &parameters) const { return 0; }
/**
 * Method which represents the select query in database table lifestyle.
 * @param params                (map<string, string> - key, value - parameters for select)
 * @param one_result            (bool - if you want only one result)
 * @param custom_query          (string - custom SQL query)
 * @param join                  (string - custom SQL JOIN query)
 * @param or_select             (bool - params used as OR in query)
 * @return vector<LifeStyle*>   (found lifestyle rows)
 */
vector<LifeStyle*> LifeStyleRepository::findBy(const map<string, string> &params, bool one_result,
                                               const string &custom_query, const string &join, bool or_select) const
{
    MYSQL_RES * result;
    MYSQL_FIELD * field;
    MYSQL_ROW row;
    tm time1, time2;
    vector<string> field_names;
    vector<LifeStyle*> life_style;
    map<string, vector<tm>> style;
    Select select;
    result = select.findAll("lifestyle");

    while((field = mysql_fetch_field(result)) != NULL) {
        field_names.push_back(field->name);
    }

    while((row = mysql_fetch_row(result)) != NULL) {
        if(mysql_num_fields(result) >= 4 && row[1] && row[2] && row[3]) {
            vector<tm> time;
            strptime(row[2], "%H:%M:%S", &time1);
            strptime(row[3], "%H:%M:%S", &time2);
            time.push_back(time1);
            time.push_back(time2);
            style.insert(pair<string, vector<tm>>(row[1], time));
        }
    }

    mysql_free_result(result);
    delete field;
    life_style.push_back(new LifeStyle(style));

    return life_style;
}