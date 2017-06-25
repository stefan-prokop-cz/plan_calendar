#include "RegistrationView.h"

/**
 * Method which renders sign in form. Then send user defined data into the controller and then shows the login result
 * (fail or successful login) message
 */
void RegistrationView::show()
{
    AuthController controller;
    string username, password;

    this->getWelcomePage();
    cout << "Uzivatelske jmeno: ";
    cin >> username;
    cout << "Heslo: ";

    setStdinEcho(false);
    cin >> password;
    setStdinEcho(true);

    if(controller.login(username, password)) {
        cout << "\n\033[1;32mByl/a jste uspesne prihlasen/a!\033[0m" << endl;
    } else {
        cout << "\n\033[1;31mSpatne zadane prihlasovaci udaje!\033[0m" << endl;
    }
}
/**
 * Method which updates the ECHO for stdin. It hides characters which user write to the terminal. It helps with
 * some safety. Takes parameter a bool enable which indicates state - true = enable hiding and false = disable
 * hiding. Method operates with two situations - stdin for windows and stdin for other systems.
 * - use: http://stackoverflow.com/questions/1413445/reading-a-password-from-stdcin (08. 04. 2017, 10:55)
 * @param enable (bool)
 */
void RegistrationView::setStdinEcho(bool enable)
{
#ifdef WIN32
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);

    if( !enable ) {
        mode &= ~ENABLE_ECHO_INPUT;
    } else {
        mode |= ENABLE_ECHO_INPUT;
    }

    SetConsoleMode(hStdin, mode );
#else
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);

    if( !enable ) {
        tty.c_lflag &= ~ECHO;
    } else {
        tty.c_lflag |= ECHO;
    }

    (void) tcsetattr(STDIN_FILENO, TCSANOW, &tty);
#endif
}
