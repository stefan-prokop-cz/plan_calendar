#include "Validation.h"

/**
 * Method which represents the Validation constructor. It initialize the variable days_in_month. It is an int array
 * where are stored how many days are in each month
 */
Validation::Validation()
{
    days_in_month[0] = 31, days_in_month[1] = 29, days_in_month[2] = 31, days_in_month[3] = 30, days_in_month[4] = 31,
    days_in_month[5] = 30, days_in_month[6] = 31, days_in_month[7] = 31, days_in_month[8] = 30, days_in_month[9] = 31,
    days_in_month[10] = 30, days_in_month[11] = 31;
}
/**
 * Method which validates the user defined datetime. It tests if this datetime is bigger or equal to the actual
 * datetime - if not: then returns false else returns true.
 * @param datetime (struct tm)
 * @return bool
 */
bool Validation::validateDateTime(const tm &datetime) const
{
    if(datetime.tm_year <= 2000) { return false; }

    tm time_now;
    time_t now = time(0);
    time_now = *localtime(&now);
    time_now.tm_year = time_now.tm_year + 1900, time_now.tm_mon = time_now.tm_mon + 1;

    if(datetime.tm_year < time_now.tm_year || datetime.tm_year > (time_now.tm_year + max_years) ||
            (datetime.tm_year == time_now.tm_year && datetime.tm_mon < time_now.tm_mon) ||
            (datetime.tm_year == time_now.tm_year && datetime.tm_mon == time_now.tm_mon &&
            datetime.tm_mday < time_now.tm_mday) || (datetime.tm_year == time_now.tm_year
            && datetime.tm_mon == time_now.tm_mon && datetime.tm_mday == time_now.tm_mday &&
            datetime.tm_hour < time_now.tm_hour) || (datetime.tm_year == time_now.tm_year &&
            datetime.tm_mon == time_now.tm_mon && datetime.tm_mday == time_now.tm_mday &&
            datetime.tm_hour == time_now.tm_hour && datetime.tm_min < time_now.tm_min) || datetime.tm_mon <= 0 ||
            datetime.tm_mon > 12 || datetime.tm_mday <= 0 || datetime.tm_mday > days_in_month[datetime.tm_mon - 1] ||
            datetime.tm_hour < 0 || datetime.tm_hour > 23 || datetime.tm_min < 0 || datetime.tm_min > 59 ||
            datetime.tm_sec < 0 || datetime.tm_sec > 59) {

        return false;
    }

    return true;
}
/**
 * Method which compares two datetimes - struct tm. It tests if a is smaller then b.
 * @param a     (struct tm)
 * @param b     (struct tm)
 * @return int  (-1, 0, 1)
 */
int Validation::compareDates(const tm &a, const tm &b) const
{
    if(a.tm_year == b.tm_year) {
        if(a.tm_mon == b.tm_mon) {
            if(a.tm_mday == b.tm_mday) {
                if(a.tm_hour == b.tm_hour) {
                    if(a.tm_min == b.tm_min) {
                        if(a.tm_sec == b.tm_sec) {
                            return 0;
                        }

                        return a.tm_sec < b.tm_sec;
                    }

                    return a.tm_min < b.tm_min;
                }

                return a.tm_hour < b.tm_hour;
            }

            return a.tm_mday < b.tm_mday;
        }

        return a.tm_mon < b.tm_mon;
    }

    return a.tm_year < b.tm_year;
}
/**
 * Method which reepresents the getter. It returns the days in month for sent parameter month.
 * @param month     (int)
 * @return int      (days in month)
 */
int Validation::getDaysInMonth(const int &month) const { return days_in_month[month - 1]; }
/**
 * Metoda kontrolujici, zda se zadany datum nenachazi v dobe vyhrazene pro pauzu
 *
 * @param datetime
 * @return bool
 */
bool Validation::isPause(const tm &datetime, const double plus_hours) const
{
    double hours = (datetime.tm_hour + 0.0) + (datetime.tm_min + 0.0) / 60 + (datetime.tm_sec + 0.0) / 60 / 60;

    for(const auto & it : life_style->getStyle()) {
        double start_h = (it.second[0].tm_hour + 0.0) + (it.second[0].tm_min + 0.0) / 60 + (it.second[0].tm_sec + 0.0) / 60 / 60;
        double end_h = (it.second[1].tm_hour + 0.0) + (it.second[1].tm_min + 0.0) / 60 + (it.second[1].tm_sec + 0.0) / 60 / 60;

        if(plus_hours > 0) {
            if(hours < start_h && (hours + plus_hours) > start_h) {
                return true;
            }
        } else {
            if(hours >= start_h && hours <= end_h) {
                return true;
            }
        }
    }

    return false;
}
/**
 * Method which tests if datetime end minus start (to hours) is equal to hours. These hours defined user.
 * @param start     (string - datetime start)
 * @param end       (string - datetime end)
 * @param hours     (double)
 * @return bool     (true: is equal, false: is not equal)
 */
bool Validation::isEqualWithTime(const string &start, const string &end, const double hours) const
{
    ostringstream stream;
    tm start_time, end_time;
    double start_h, end_h;

    sscanf(start.c_str(), " %d-%d-%d %d:%d:%d", &start_time.tm_year, &start_time.tm_mon, &start_time.tm_mday, &start_time.tm_hour,
                &start_time.tm_min, &start_time.tm_sec);
    sscanf(end.c_str(), " %d-%d-%d %d:%d:%d", &end_time.tm_year, &end_time.tm_mon, &end_time.tm_mday, &end_time.tm_hour,
           &end_time.tm_min, &end_time.tm_sec);

    start_h = (start_time.tm_year + 0.0) * 365 * 24 + (start_time.tm_mon + 0.0) * days_in_month[start_time.tm_mon] * 24 +
            (start_time.tm_mday + 0.0) * 24;
    end_h = (end_time.tm_year + 0.0) * 365 * 24 + (end_time.tm_mon + 0.0) * days_in_month[end_time.tm_mon] * 24 +
              (end_time.tm_mday + 0.0) * 24;

    if(end_h < start_h) {
        return false;
    }

    start_h = start_time.tm_hour + 0.0 + (start_time.tm_min + 0.0) / 60.0 + (start_time.tm_sec + 0.0) / 60.0 / 60.0;
    start_h = end_time.tm_hour + 0.0 + (end_time.tm_min + 0.0) / 60.0 + (end_time.tm_sec + 0.0) / 60.0 / 60.0;

    if((end_h - start_h) < hours) {
        return false;
    }

    return true;
}