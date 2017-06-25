#include "globals.h"

/// Global variable which represents logged user
User * session = nullptr;
/// Global variable which indicates user session life
bool session_exists = false;
/// Global variable which represents the welcome text
string welcome_page = "";
/// Global variable which is shown as a terminal text after successful login
string terminal_text = "";
/// Global variable which represents max years (this year + this constant = max year) for create a new event
const int max_years = 100;
/// Global variable which represents the database connection for all queries
Connector * connector = nullptr;
/// Global variable which represents the life style constants
LifeStyle * life_style = nullptr;
/// Global variable which represents the max events per one page for paginator
const int events_per_page = 7;