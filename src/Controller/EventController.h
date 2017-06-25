#ifndef PLAN_KALENDAR_EVENTCONTROLLER_H
#define PLAN_KALENDAR_EVENTCONTROLLER_H

#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>
#include "../View/EventView.h"
#include "../Model/Repository/CalendarRepository.h"
#include "../Service/Exception/LifeStyleException.h"
#include "../Model/Repository/EventRepository.h"
#include "../Model/Entity/Event.h"
#include "../Model/Entity/Calendar.h"
#include "../globals.h"
#include "../Service/DI/Validation.h"
using namespace std;

/**
 * Class which operates with user's events and calendars. It propose methods for creating, selecting and updating
 * events or calendars.
 * @author Stefan Prokop <prokoste>
 */
class EventController
{
public:
    void renderShareForm() const;
    void renderCalendars() const;
    int addNewEvent(const string & name, const string & description, bool repeat, const int repeat_count,
                    const double repeat_const, const tm & datetime_start, const tm & datetime_end,
                    const int status, const int public_event, const string & calendar_name) const;
    bool addNewCalendar(const string & name) const;
    int shareCalendar(const vector<string> & usernames, const string & calendar_name) const;
    vector<string> getClosestDate(const string & calendar_name, const double hours, bool relevant) const;
    vector<Event*> getEvents(const string & calendar_name, const int page) const;
    bool updateEvent(const int event_id, const string & datetime_start, string & datetime_end,
                     const string & calendar_name, const double time, bool last) const;
};

#endif //PLAN_KALENDAR_EVENTCONTROLLER_H