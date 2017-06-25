#ifndef PLAN_KALENDAR_DEFAULTVIEW_H
#define PLAN_KALENDAR_DEFAULTVIEW_H

#include <iostream>
#include "BaseView.h"
using namespace std;

/**
 * Class which represents the default view. It propose method which renders start menu. This class is extended by
 * BaseView class.
 * @author Stefan Prokop <prokoste>
 */
class DefaultView : public BaseView
{
public:
    virtual void show() {}
    void showWelcomePage();
};

#endif //PLAN_KALENDAR_DEFAULTVIEW_H
