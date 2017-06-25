#ifndef PLAN_KALENDAR_VALIDATION_H
#define PLAN_KALENDAR_VALIDATION_H

#include <ctime>
#include <sstream>
#include <map>
#include <vector>
#include "../../globals.h"

/**
 * Class which represents the validation unit. It validates components before storing into database or before another
 * work.
 * @author Stefan Prokop <prokoste>
 */
class Validation
{
public:
    Validation();
    bool validateDateTime(const tm & datetime) const;
    int compareDates(const tm & a, const tm & b) const;
    int getDaysInMonth(const int & month) const;
    bool isPause(const tm & datetime, const double plus_hours) const;
    bool isEqualWithTime(const string & start, const string & end, const double hours) const;

private:
    int days_in_month[12];
};

#endif //PLAN_KALENDAR_VALIDATION_H