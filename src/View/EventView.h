#ifndef PLAN_KALENDAR_EVENTVIEW_H
#define PLAN_KALENDAR_EVENTVIEW_H

#include <vector>
#include "BaseView.h"
#include "../Controller/EventController.h"
#include "../Model/Entity/Event.h"
#include "../Model/Entity/Calendar.h"
#include "../globals.h"

/**
 * Class which represents the event view. It proposes methods which renders views associated with calendar or event
 * classes (entities).
 * @author Stefan Prokop <prokoste>
 */
class EventView : public BaseView
{
public:
    virtual void show() {}
    void createEventForm();
    void createShareForm(const vector<Calendar*> & calendars);
    void createCalendarForm();
    void createShowView();
    void showCalendars(const vector<Calendar*> & calendars);
    void createShowEventForm();
    void createMoveForm();

private:
    void printEvents(const vector<Event*> & events, bool share_event, int & page);
    void printEventsTable(const vector<Event*> & events);
};

#endif //PLAN_KALENDAR_EVENTVIEW_H
