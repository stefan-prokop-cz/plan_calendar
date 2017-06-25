#include "TerminalListener.h"

/**
 * Method which processing the user input before user's sign in
 * - Input variants:
 *      1: login form
 *      2: registration form
 */
void TerminalListener::preAuthenticate() const
{
    string input;
    BaseView * view = new AuthView();
    BaseView * view2 = new RegistrationView();

    while(getline(cin, input)) {
        if (trim(input) == "1") {
            view->show();

            if(session_exists) {
                break;
            }
        } else if (trim(input) == "2") {
            view2->show();
        } else {
            cout << "> ";
        }
    }

    delete view;
    delete view2;
}
/**
 * Method which processing the user input after user's sign in
 * - Input variants:
 *      logout:     same as ^D - logout user and correctly stops the program
 *      add:        shows form for creating a new event
 *      share:      shows form where user can share his calendar with another users
 *      create:     shows form for creating a new calendar
 *      search:     shows form for searching for free space for a potential new events
 *      calendars:  shows user's calendars (theirs or shared)
 *      show:       shows form for a searching through events
 *      move:       shows form for updating / moving events to the new free space (time interval)
 *      export:     shows form for exporting the calendar into iCalendar format
 */
void TerminalListener::postAuthenticate() const
{
    EventController event_controller;
    EventView view;
    string input;
    input = trim(input);

    while(getline(cin, input)) {
        if(input == "logout") {
            break;
        } else if(input == "add") {
            view.createEventForm();
        } else if(input == "share") {
            event_controller.renderShareForm();
        } else if(input == "create") {
            view.createCalendarForm();
        } else if(input == "search") {
            view.createShowView();
        } else if(input == "calendars") {
            event_controller.renderCalendars();
        } else if (input == "show") {
            view.createShowEventForm();
        } else if(input == "move") {
            view.createMoveForm();
        } else if(input == "export") {
            Export e;

            if(e.exportEvents()) {
                cout << "\033[1;32mUdalosti byly exportovany do souboru calendar.ical\033[0m" << endl;
            } else {
                cout << "\033[1;31mUdalosti se bohuzel nepodarilo exportovat.\033[0m" << endl;
            }
        } else {
            cout << terminal_text;
        }
    }
}
/**
 * Method which takes a string parameter and cut the white characters out of this string from the begin and end of
 * this parameter
 * @param text (string)
 * @return string (parameter text without white characters on the begin and on the end)
 */
string& TerminalListener::trim(string &text) const
{
    auto it2 =  find_if( text.begin() , text.end() , [](char ch){ return !std::isspace<char>(ch , std::locale::classic() ) ; } );
    text.erase( text.begin() , it2);

    auto it1 =  find_if( text.rbegin() , text.rend() , [](char ch){ return !std::isspace<char>(ch , std::locale::classic() ) ; } );
    text.erase( it1.base() , text.end() );

    return text;
}
