#ifndef CLSLOGINSCREEN_H_INCLUDED
#define CLSLOGINSCREEN_H_INCLUDED

#pragma once
#include <iostream>
#include "clsUser.h"
#include "clsScreen.h"
#include "Global.h"
#include "clsMainScreen.h"



class clsLoginScreen : protected clsScreen
{
private:

    static bool _Login()
    {
        bool LoginFalid = false;

        string Username, password;

        short FalidLoginCount = 3;


        do
        {



            if(LoginFalid)
            {
                FalidLoginCount--;
                cout << "\nInvalid Username / password!\n";
                cout << "You have " << FalidLoginCount << " Trial (s) to login\n\n";
            }

            if(FalidLoginCount == 0)
            {
                cout << "\nYou are Locked after 3 faild trials \n\n";
                return false;
            }

            cout << "Enter Username: "; cin >> Username;
            cout << "Enter Password: "; cin >> password;


            CurrentUser = clsUser::Find(Username, password);

            LoginFalid = CurrentUser.IsEmpty();

        }while(LoginFalid && FalidLoginCount);


        if(FalidLoginCount)
        {
            CurrentUser.RegisterLogIn();
            clsMainScreen::ShowMainMenue();
            return true;
        }

    }

public:

    static bool ShowLoginScreen ()
    {
        system("cls");
        _DrawScreenHeader("\t       Login Screen");
        return _Login();
    }
};




#endif // CLSLOGINSCREEN_H_INCLUDED
