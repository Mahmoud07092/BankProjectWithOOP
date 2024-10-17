#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "Global.h"
#include "clsUtil.h"

class clsLoginScreen :protected clsScreen
{

private:

    static  void _Login() {

        bool LoginFaild = false;
        short Counter = 3;

        string Username, Password;

        do {

            if (LoginFaild) {

                Counter--;
                cout << "\nInvlaid Username/Password!\n";
                cout << "You have " << Counter << " Trials to login.\n\n";
            }

            if (Counter == 0) {

                exit(0);
            }

            cout << "Enter Username? ";
            cin >> Username;

            cout << "Enter Password? ";
            cin >> Password;

            
            CurrentUser = clsUser::Find(Username, Password);

            LoginFaild = CurrentUser.IsEmpty();

        } while (LoginFaild);

        CurrentUser.RegisterLogIn();
        clsMainScreen::ShowMainMenue();

    }

public:


    static void ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Login Screen");
        _Login();

    }

};
