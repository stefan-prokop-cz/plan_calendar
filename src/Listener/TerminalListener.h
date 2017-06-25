#ifndef PLAN_KALENDAR_TERMINALLISTENER_H
#define PLAN_KALENDAR_TERMINALLISTENER_H

#include <iostream>
#include <algorithm>
#include "../View/AuthView.h"
#include "../View/RegistrationView.h"
#include "../View/EventView.h"
#include "../Controller/EventController.h"
#include "../globals.h"
#include "../Model/Export.h"
using namespace std;

/**
 * Class provide methods for catching the user's input from terminal and these methods works with input before sign in
 * and after sign in and then call specific methods for each mode
 *
 * @author Stefan Prokop <prokoste>
 */
class TerminalListener
{
public:
    void preAuthenticate() const;
    void postAuthenticate() const;

private:
    string & trim(string & text) const;
};

#endif //PLAN_KALENDAR_TERMINALLISTENER_H
