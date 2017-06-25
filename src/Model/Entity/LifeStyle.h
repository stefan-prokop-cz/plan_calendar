#ifndef PLAN_KALENDAR_LIFESTYLE_H
#define PLAN_KALENDAR_LIFESTYLE_H

#include <iostream>
#include <string>
#include <map>
#include <ctime>
#include <vector>
using namespace std;

/**
 * Class which represents the database table called lifestyle.
 * @author Stefan Prokop <prokoste>
 */
class LifeStyle
{
public:
    LifeStyle(const map<string, vector<tm>> & style);
    map<string, vector<tm>> getStyle() const;

private:
    map<string, vector<tm>> style;
};

#endif //PLAN_KALENDAR_LIFESTYLE_H