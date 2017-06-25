#ifndef PLAN_KALENDAR_BASEVIEW_H
#define PLAN_KALENDAR_BASEVIEW_H

#include <iostream>
#include <string>
#include <fstream>
#include "../globals.h"
using namespace std;

/**
 * Class which is a parent of all views. Define method which renders the welcome page
 * @author Stefan Prokop <prokoste>
 */
class BaseView
{
public:
    void getWelcomePage();
    virtual void show() = 0;
};

#endif //PLAN_KALENDAR_BASEVIEW_H
