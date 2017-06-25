#ifndef PLAN_KALENDAR_EVENTHELPER_H
#define PLAN_KALENDAR_EVENTHELPER_H

#include <ctime>
#include <iostream>
#include <sstream>
#include "../../globals.h"
#include "../../Model/Entity/Event.h"
#include "../../Model/Entity/Calendar.h"
#include "../../Model/Repository/EventRepository.h"
#include "../../Model/Repository/CalendarRepository.h"
#include "Validation.h"
#include "../Exception/MaxDateTimeException.h"
#include "../Exception/LifeStyleException.h"
#include "../Exception/CalendarNotFoundException.h"
using namespace std;

/**
 * Trida poskytujici metody, ktere budou napomahat pri zpracovavani udalosti
 * @author Stefan Prokop <prokoste@fit.cvut.cz>
 */
class EventHelper
{
public:
    EventHelper();
    Event & makeRepeatedEvent(Event & event);
    bool hasException() const;
    void setException(bool exc);
    vector<string> findClosestDate(const string & calendar_name, bool relevant, const double hours) const;
    string countEndDate(const string & datetime_start, const double hours) const;
    tm & countNewDate(tm & datetime, const double hours_start);
    string createTextFromDate(const tm & time) const;
    tm & createDateFromText(tm & datetime, const string & text) const;
    double getHoursFromDate(const tm & datetime) const;

private:
    bool life_style_exception;
    vector<string> countClosestDate(const vector<Event*> & events, bool relevant, const double hours) const;
};

#endif //PLAN_KALENDAR_EVENTHELPER_H