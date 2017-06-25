#include <iostream>

#include "Model/Repository/UserRepository.h"
#include "Model/Repository/LifeStyleRepository.h"
#include "Listener/TerminalListener.h"
#include "View/DefaultView.h"
#include "globals.h"

using namespace std;

int main()
{
    string start;
    cout << "Pro zapoceti prace v programu napiste 'start': ";
    getline(cin, start);

    if(start != "start") { return 0; }

    TerminalListener listener;
    DefaultView view;
    LifeStyleRepository life_style_repository;
    view.showWelcomePage();
    connector = new Connector();
    map<string, string> params;
    life_style = life_style_repository.findBy(params, false, "", "", false)[0];

    try {
        listener.preAuthenticate();
    } catch (char const * ex) {
        cout << ex << endl;
    }

    if(session_exists) {
        try {
            listener.postAuthenticate();
        } catch (...) {}
    }

    delete session;
    delete connector;
    delete life_style;
    mysql_library_end();

    return EXIT_SUCCESS;
}
