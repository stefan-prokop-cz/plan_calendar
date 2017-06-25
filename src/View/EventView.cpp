#include "EventView.h"

/**
 * Method which renders form for creating new event
 */
void EventView::createEventForm()
{
    tm datetime_start, datetime_end;
    EventController controller;
    string name, description, repeatable, calendar_name;
    int repeat_count = -1, status, public_event;
    double repeat_const = 0;
    bool repeat = false;
    this->getWelcomePage();

    cout << "Pomoci formulare vytvorte svou udalost (Maximalne " << max_years << " let dopredu)" << endl;
    cout << "Nazev kalendare, do ktereho bude udalost vlozena: ";
    getline(cin, calendar_name);
    cout << "Nazev: ";
    getline(cin, name);
    cout << "Popis: ";
    getline(cin, description);
    cout << "Bude se udalost opakovat? (A / N): ";
    getline(cin, repeatable);
    
    if(repeatable == "A" || repeatable == "a") {
        repeat = true;
    } else if(repeatable != "N" && repeatable != "n") {
        cout << "\033[1;31mSpatny format vstupu!\033[0m" << endl;
        return;
    }

    if(repeat) {
        cout << "Pocet opakovani: ";
        if(!(cin >> repeat_count) || repeat_count < 0) {
            cout << "\033[1;31mSpatny format vstupu!\033[0m" << endl;
	    return;
        }

        cout << "Po jako dobe opakovat? (Zadejte v hodinach): ";

        if(!(cin >> repeat_const) || repeat_const < 0) {
            cout << "\033[1;31mSpatny format vstupu!\033[0m" << endl;
	    return;
        }
    } else {
        repeat_const = 0;
        repeat_const = 0;
    }

    cout << "Status udalosti (1 = povinna udalost, 2 = volitelna udalost, 3 = presouvatelna udalost): ";
    if(!(cin >> status) || (status != 1 && status != 2 && status != 3)) {
        cout << "\033[1;31mSpatny format vstupu!\033[0m" << endl;
	return;
    }

    cout << "Viditelnost udalosti (1 = soukroma udalost, 2 = verejna udalost, 3 = sdilena udalost): ";
    if(!(cin >> public_event) || (public_event != 1 && public_event != 2 && public_event != 3)) {
        cout << "\033[1;31mSpatny format vstupu!\033[0m" << endl;
	return;
    }

    cin.ignore(INT32_MAX, '\n');
    cout << "Datum a cas zacatku udalosti (Zadejte ve formatu: YYYY-MM-DD HH:MM:SS): ";
    int result = scanf("%d-%d-%d %d:%d:%d", &datetime_start.tm_year, &datetime_start.tm_mon, &datetime_start.tm_mday,
                           &datetime_start.tm_hour, &datetime_start.tm_min, &datetime_start.tm_sec);

    if(result != 6) {
        cout << "\033[1;31mSpatny format datumu a casu!\033[0m" << endl;
        return;
    }

    cin.ignore(INT32_MAX, '\n');
    cout << "Datum a cas konce udalosti (Zadejte ve formatu: YYYY-MM-DD HH:MM:SS): ";
    result = scanf("%d-%d-%d %d:%d:%d", &datetime_end.tm_year, &datetime_end.tm_mon, &datetime_end.tm_mday,
                           &datetime_end.tm_hour, &datetime_end.tm_min, &datetime_end.tm_sec);

    if(result != 6) {
        cout << "\033[1;31mSpatny format datumu a casu!\033[0m" << endl;
        return;
    }

    int add_result = controller.addNewEvent(name, description, repeat, repeat_count, repeat_const, datetime_start,
                                            datetime_end, status, public_event, calendar_name);

    switch (add_result) {
        case 1:
            cout << "\033[1;32mNova udalost (" << name << ") byla uspesne vytvorena!\033[0m" << endl;
            break;
        case 2:
            cout << "\033[1;31mSpatny format datumu a casu!\033[0m" << endl;
            break;
        case 3:
            cout << "\033[1;31mNektera z nove vytvarenych udalosti prekrocila nejvyssi mozny casovy limit - "
                    "Nektere udalosti se nepodarilo vytvorit.\033[0m" << endl;
            break;
        case 4:
            cout << "\033[1;31mNektera z nove vytvarenych udalosti nebyla vytvorena z duvodu kontroly "
                    "zdraveho zivotniho stylu.\033[0m" << endl;
            break;
        case 5:
            cout << "\033[1;31mKalendar s timto jmenem nemate vytvoreny!\033[0m" << endl;
            break;
        case 6:
            cout << "\033[1;31mNektera z udalosti se casove prekryva - udalost se nepodarilo vytvorit.\033[0m" << endl;
            break;
        default:
            cout << "\033[1;31mNovou udalost se bohuzel nepodarilo vytvorit.\033[0m" << endl;
            break;
    }
}
/**
 * Method which renders form for sharing calendars with another users. It takes parameter calendars with all calendars
 * of actual user.
 * @param calendars (vector<Calendar*>)
 */
void EventView::createShareForm(const vector<Calendar*> & calendars)
{
    EventController controller;
    string console, calendar_name;
    vector<string> usernames;
    this->getWelcomePage();
    cout << "Do nasledujiciho formulare zadejte nazev kalendare, ktery chcete sdilet:" << endl;
    cout << "\033[1;33m----------- VASE KALENDARE -----------\033[0m" << endl;
    cout << "\033[1;33m#ID         Nazev                     \033[0m" << endl;
    for(const auto & it : calendars) {
        cout << "#" << it->getId() << "         " << it->getName() << endl;
    }
    for(auto it : calendars) { delete it; }
    cout << "\033[1;33m--------------------------------------\033[0m" << endl;
    cout << "\033[1;34mZadejte nazev kalendare, tery chcete sdilet: \033[0m";
    getline(cin, calendar_name);
    cout << "\033[1;34mZadejte uzivatele, kterym chcete kalendar sdilet (zadavani ukoncite zadanim sveho uzivatelskeho jmena = "
         << session->getUsername() << "):\033[0m" << endl;

    while(true) {
        getline(cin, console);

        if(console == session->getUsername()) {
            break;
        } else {
            usernames.push_back(console);
        }
    }

    if(usernames.size() > 0) {
        int result = controller.shareCalendar(usernames, calendar_name);

        if(result == 3) {
            cout << "\033[1;31mKalendar s timto jmenem nemate vytvoreny.\033[0m" << endl;
        } else if(result == 0) {
            cout << "\033[1;32mKalendar byl uspesne sdilen se vsemi zadanymi uzivateli!\033[0m" << endl;
        } else {
            cout << "\033[1;31mNekde nastala nastala chyba! V nejakem z pripadu se nepodarilo kalendar sdilet.\033[0m" << endl;
        }
    }

    cout << terminal_text;
}
/**
 * Method which shows user's events. This method takes parameter shared_event and page - for paginator.
 * @param events        (vector<Event*> - events on page number "page")
 * @param share_event   (bool - state for printing)
 * @param page          (int - page)
 */
void EventView::printEvents(const vector<Event*> &events, bool share_event, int & page)
{
    (share_event) ? cout << "Podivejte se na sve udalosti (nachazite se na " << page
                         << ". strance s udalostmi): " << endl : "";
    cout << "\033[1;33m---------------------------------------------- "
            "VASE UDALOSTI ----------------------------------------------\033[0m" << endl;
    printEventsTable(events);
    (share_event) ? cout << "\033[1;34mPrechazeni na dalsi stranku ukoncite zadanim 0\033[0m" << endl : "";
}
/**
 * Method which shows table with user's events
 * @param events    (vector<Event*>)
 */
void EventView::printEventsTable(const vector<Event*> &events)
{
    cout << "\033[1;33m#ID       Name         Popis                                               Status  Zacatek            "
            "Konec\033[0m" << endl;
    for(const auto & it : events) {
        cout << it->getId() << "         "
             << it->getName() << "        "
             << it->getDescription() << "            "
             << it->getStatus() << "   "
             << it->getDatetimeStart() << "    "
             << it->getDatetimeEnd() << endl;
    }
    cout << "\033[1;33m-------------------------------------------------------------------------------------------"
            "----------------\033[0m" << endl;

    for(auto it : events) { delete it; }
}
/**
 * Method which renders form for creating new calendar
 */
void EventView::createCalendarForm()
{
    EventController controller;
    string name;
    this->getWelcomePage();

    cout << "Pomoci formulare vytvorte kalendar:" << endl << "Nazev: ";
    getline(cin, name);

    if(controller.addNewCalendar(name)) {
        cout << "\033[1;32mNovy kalendar (" << name << ") byl uspesne vytvoren!\033[0m" << endl;
    } else {
        cout << "\033[1;31mNovy kalendar se bohuzel nepodarilo vytvorit.\033[0m" << endl;
    }

    cout << terminal_text;
}
/**
 * Method which renders form for searching through relevant or free space for potential new events
 */
void EventView::createShowView()
{
    EventController controller;
    string calendar_name;
    int variant;
    vector<string> events;

    this->getWelcomePage();
    cout << "Pomoci nasledujiciho formulare si muzete najit volne terminy:" << endl;
    cout << "Nazev kalendare: ";
    getline(cin, calendar_name);
    cout << "Pro vyhledani nejblizsiho mozneho terminu zvolte: 1, pro nejblizsi dostatecny termin zvolte: 2: ";
    int result = scanf(" %d", &variant);

    if(!(result == 1 && (variant == 1 || variant == 2))) {
        cout << "\033[1;31mSpatna volba!\033[0m" << endl;
        return;
    }

    if(variant == 1) {
        try {
            events = controller.getClosestDate(calendar_name, 0, false);

            if(events.size() != 2) {
                cout << "\033[1;32mKalendar je neobsazen.\033[0m" << endl;
            } else {
                cout << "\033[1;34mNejblizsi mozny termin je: \033[0m" << endl;
                cout << "\033[1;32m" << events[0] << " - " << events[1] << "\033[0m" << endl;
            }
        } catch (...) {
            cout << "\033[1;31mKalendar s timto jmenem doposud nemate vytvoreny!\033[0m" << endl;
        }
    } else {
        double time;
        cout << "Zadejte v hodinach, kolik casu na akci potrebujete: ";

        while(true) {
            int result = scanf(" %lf", &time);

            if(result == 1 && time >= 0) {
                break;
            }
        }

        try {
            events = controller.getClosestDate(calendar_name, time, true);

            if(events.size() > 0) {
                cout << "\033[1;34mRelevantni terminy jsou: \033[0m" << endl;

                for(size_t i = 0; i < events.size(); i += 2) {
                    cout << "\033[1;32m" << events[i] << " - ";
                    cout << events[i + 1] << "\033[0m" << endl;
                }
            } else {
                cout << "\033[1;31mKalendar je neobsazen nebo se v nem nenachazi zadne volne misto.\033[0m" << endl;
            }
        } catch (...) {
            cout << "\033[1;31mKalendar s timto jmenem doposud nemate vytvoreny!\033[0m" << endl;
        }
    }
}
/**
 * Method which shows user's calendars and shared calendars.
 * @param calendars (vector<Calendar*>)
 */
void EventView::showCalendars(const vector<Calendar*> & calendars)
{
    if(calendars.size() <= 0) {
        cout << "\033[1;31mZatim nemate zalozeny zadny kalendar a zadny kalendar s vami neni sdilen.\033[0m" << endl;
    } else {
        cout << "\033[1;34mVase a vase sdilene kalendare: \033[0m" << endl;

        for (const auto &it : calendars) { cout << it->getName() << endl; }
    }

    for (auto it : calendars) { delete it; }
}
/**
 * Method which shows events from typed calendar name with pages (paginator). It creates the form.
 */
void EventView::createShowEventForm()
{
    EventController controller;
    int result, page = 1;
    string calendar_name;
    this->getWelcomePage();
    cout << "Zadejte jmeno kalendare, ve kterem chcete vyhledavat udalosti: ";
    getline(cin, calendar_name);
    cout << "Zadejte cislo stranky: ";

    while ((result = scanf(" %d", &page)) == 1) {
        if(page < 0) {
            page = 1;
        }

        if(page == 0) {
            break;
        } else {
            try {
                printEvents(controller.getEvents(calendar_name, page), true, page);
            } catch (...) {
                cout << "\033[1;31mKalendar neexistuje!\033[0m" << endl;
                return;
            }

            cout << "Zadejte cislo stranky: ";
        }
    }

    if(result == 0) {
        cout << "\033[1;31mSpatne zadane cislo stranky!\033[0m" << endl;
    }
}
/**
 * Method which renders form for moving events on another free space or relevant position.
 */
void EventView::createMoveForm()
{
    this->getWelcomePage();
    EventController controller;
    vector<string> events;
    string calendar_name, datetime_start, datetime_end;
    double time;
    bool last = false;
    cout << "Zadejte nazev kalendare: ";
    getline(cin, calendar_name);
    cout << "Kolik casu na udalost potrebujete (v hodinach): ";
    int result = scanf(" %lf", &time);

    if(!(result == 1 && time > 0)) {
        cout << "\033[1;31mSpatny format.\033[0m" << endl;
        return;
    }

    try {
        events = controller.getClosestDate(calendar_name, time, true);

        if(events.size() > 0) {
            cout << "\033[1;34mRelevantni terminy jsou: \033[0m" << endl;

            for(size_t i = 0; i < events.size(); i += 2) {
                cout << "\033[1;32m" << (i / 2) << ". " << events[i] << " - ";
                cout << events[i + 1] << "\033[0m" << endl;
            }
        } else {
            cout << "\033[1;31mKalendar je neobsazen nebo se v nem nenachazi zadne volne misto.\033[0m" << endl;
        }

        int event_id, position;
        cout << "Zadejte ID udalosti, kterou chcete presunout: ";
        int result = scanf(" %d", &event_id);

        if(!(result == 1 && event_id > 0)) {
            cout << "\033[1;31mSpatny format.\033[0m" << endl;
            return;
        }

        cout << "Zadejte pozici, na kterou chcete udalost presunout (cislo pred datumy): ";

        while(true) {
            int result = scanf(" %d", &position);

            if(result == 1 && position >= 0) {
                break;
            }
        }

        if(position >= ((int) events.size() / 2)) {
            cout << "\033[1;31mTakova pozice neni v seznamu!\033[0m" << endl;
        } else {
            cin.ignore(INT32_MAX, '\n');
            position *= 2;

            if(events[position + 1] == "Konec") {
                cout << "Upresnete prosim termin - zadejte pocatecni datum a cas udalosti (YYYY-MM-DD HH:MM:SS): ";
                getline(cin, datetime_start);
                cout << "Upresnete prosim termin - zadejte koncovy datum a cas udalosti (YYYY-MM-DD HH:MM:SS): ";
                getline(cin, datetime_end);
                last = true;
            } else {
                datetime_start = events[position];
                datetime_end = events[position + 1];
            }

            if(controller.updateEvent(event_id, datetime_start, datetime_end, calendar_name, time, last)) {
                cout << "\033[1;32mUdalost byla uspesne presunuta!\033[0m" << endl;
            } else {
                cout << "\033[1;31mPri presouvani udalosti se vyskytla chyba! Zkontrolujte spravnost zadanych udaju "
                        "(datum a cas, zda je udalost presouvatelna - status = 3).\033[0m" << endl;
            }
        }
    } catch (...) {
        cout << "\033[1;31mKalendar s timto jmenem doposud nemate vytvoreny!\033[0m" << endl;
    }
}
