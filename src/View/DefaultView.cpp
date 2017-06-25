#include "DefaultView.h"

/**
 * Method which renders view after start of the application.
 */
void DefaultView::showWelcomePage()
{
    this->getWelcomePage();
    cout << "Pro prihlaseni zvolte" << "\033[1;33m 1\033[0m nebo pro registraci zvolte" << "\033[1;33m 2\033[0m: ";
}