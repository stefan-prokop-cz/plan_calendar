#include "Export.h"

/**
 * Method which find all events from calendar which user defined. It stores these events into file called calendar.ical
 * in root folder (place where program started). This file is in iCalendar format.
 * Validated using this web page: http://severinghaus.org/projects/icv/
 * @return bool (true: successfully exported, false: failed)
 */
bool Export::exportEvents() const
{
    ostringstream stream;
    EventRepository event_repository;
    CalendarRepository calendar_repository;
    Calendar * calendar;
    string calendar_name;
    map<string, string> params;
    vector<Event*> events;
    stream << session->getId();
    params["user_id"] = stream.str();

    cout << "Zadejte jmeno kalendare, ze ktereho se budou data exportovat: ";
    getline(cin, calendar_name);
    params["name"] = calendar_name;

    try {
        calendar = calendar_repository.findBy(params, true, "", "", false)[0];
    } catch(...) {
        return false;
    }

    stream.str(""), params.erase("name"), params.erase("user_id");
    stream << calendar->getId();
    params["calendar_id"] = stream.str();
    events = event_repository.findBy(params, false, "", "", false);

    if(events.size() <= 0) {
        delete calendar;
        return false;
    }

    ofstream calendar_stream;
    calendar_stream.open("calendar.ical");
    tm start, end;
    calendar_stream << "BEGIN:VCALENDAR\n";
    calendar_stream << "VERSION:2.0\n";
    calendar_stream << "PRODID:-//hacksw/handcal//NONSGML v1.0//EN\n";

    for(const auto & it : events) {
        sscanf(it->getDatetimeStart().c_str(), " %d-%d-%d %d:%d:%d", &start.tm_year, &start.tm_mon, &start.tm_mday,
               &start.tm_hour, &start.tm_min, &start.tm_sec);
        sscanf(it->getDatetimeEnd().c_str(), " %d-%d-%d %d:%d:%d", &end.tm_year, &end.tm_mon, &end.tm_mday,
               &end.tm_hour, &end.tm_min, &end.tm_sec);

        calendar_stream << "BEGIN:VEVENT\nUID:" << it->getId() << "\n";

        for(int i = 0; i < 2; i++) {
            ((i == 0) ? calendar_stream << "DTSTAMP:" : calendar_stream << "DTSTART:");
            calendar_stream << start.tm_year;
            ((start.tm_mon < 10) ? calendar_stream << 0 : calendar_stream << "");
            calendar_stream << start.tm_mon;
            ((start.tm_mday < 10) ? calendar_stream << 0 : calendar_stream << "");
            calendar_stream << start.tm_mday << "T";
            ((start.tm_hour < 10) ? calendar_stream << 0 : calendar_stream << "");
            calendar_stream << start.tm_hour;
            ((start.tm_min < 10) ? calendar_stream << 0 : calendar_stream << "");
            calendar_stream << start.tm_min;
            ((start.tm_sec < 10) ? calendar_stream << 0 : calendar_stream << "");
            calendar_stream << start.tm_sec << "Z\n";
        }

        calendar_stream << "DTEND:" << end.tm_year;
        ((end.tm_mon < 10) ? calendar_stream << 0 : calendar_stream << "");
        calendar_stream << end.tm_mon;
        ((end.tm_mday < 10) ? calendar_stream << 0 : calendar_stream << "");
        calendar_stream << end.tm_mday << "T";
        ((end.tm_hour < 10) ? calendar_stream << 0 : calendar_stream << "");
        calendar_stream << end.tm_hour;
        ((end.tm_min < 10) ? calendar_stream << 0 : calendar_stream << "");
        calendar_stream << end.tm_min;
        ((end.tm_sec < 10) ? calendar_stream << 0 : calendar_stream << "");
        calendar_stream << end.tm_sec << "Z\n";
        calendar_stream << "SUMMARY:" << it->getName() << " - " << it->getDescription() << "\n";

        if(it->getPublicEvent() == 1) {
            calendar_stream << "CLASS:PRIVATE\n";
        } else if(it->getPublicEvent() == 2) {
            calendar_stream << "CLASS:PUBLIC\n";
        }

        calendar_stream << "END:VEVENT\n";
    }

    calendar_stream << "END:VCALENDAR\n";
    calendar_stream.close();
    delete calendar;
    for(auto it : events) {
        delete it;
    }
    return true;
}