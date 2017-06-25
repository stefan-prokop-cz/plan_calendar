#ifndef PLAN_KALENDAR_GLOBALS_H
#define PLAN_KALENDAR_GLOBALS_H
#include <string>
#include "Model/Entity/User.h"
#include "Model/Entity/LifeStyle.h"
#include "Service/MySQL/Connector.h"
using namespace std;

extern User * session;
extern bool session_exists;
extern string welcome_page;
extern string terminal_text;
extern const string night_start;
extern const string night_end;
extern const int max_years;
extern Connector * connector;
extern LifeStyle * life_style;
extern const int events_per_page;

#endif //PLAN_KALENDAR_GLOBALS_H