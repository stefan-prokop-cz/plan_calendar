#ifndef PLAN_KALENDAR_AUTHVIEW_H
#define PLAN_KALENDAR_AUTHVIEW_H

#include <iostream>
#include <string>
#include "BaseView.h"
#include "../Controller/AuthController.h"
using namespace std;

#ifdef WIN32
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif

/**
 * Class which represents the View. Provides methods which cooperates with user interface (termminal) and shows the
 * forms for login and registration. Also cooperates with AuthController. Class is extended by the BaseView class.
 * @author Stefan Prokop <prokoste>
 */
class AuthView : public BaseView
{
public:
    virtual void show();

private:
    void setStdinEcho(bool enable);
};

#endif //PLAN_KALENDAR_AUTHVIEW_H
