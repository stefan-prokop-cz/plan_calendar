#include "BaseView.h"

/**
 * Method which renders view with the welcome text (Plan Calendar logo). For the first time it takes data from text file
 * (welcome_page.txt) and stores into the variable. Then works with this variable (welcome_page).
 */
void BaseView::getWelcomePage()
{
    if(welcome_page == "") {
        string tmp;
        ifstream stream("src/welcome_page.txt");

        if (!stream.fail()) {
            while (getline(stream, tmp)) {
                welcome_page += tmp + "\n";
            }

            welcome_page += "\n";
        }

        stream.close();
    }

    system("clear");
    cout << welcome_page;
}
