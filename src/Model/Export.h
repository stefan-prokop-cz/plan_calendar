#ifndef PLAN_KALENDAR_EXPORT_H
#define PLAN_KALENDAR_EXPORT_H

#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include "Repository/EventRepository.h"
#include "Repository/CalendarRepository.h"
#include "Entity/Event.h"
#include "Entity/Calendar.h"
#include "../globals.h"
using namespace std;

/**
 * Class which proposes the method which exports all events from calendar
 * @author Steefan Prokop <prokoste>
 */
class Export
{
public:
    bool exportEvents() const;
};

#endif //PLAN_KALENDAR_EXPORT_H