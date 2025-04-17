#ifndef CLSFINDUSERSCREEN_H_INCLUDED
#define CLSFINDUSERSCREEN_H_INCLUDED

#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"


class clsFindUserScreen : protected clsScreen
{
private:
      static void _Print(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName      : " << User.GetFirstName();
        cout << "\nLastName       : " << User.GetLastName();
        cout << "\nFull Name      : " << User.FullName();
        cout << "\nEmail          : " << User.GetEmail();
        cout << "\nPhone          : " << User.GetPhone();
        cout << "\nUserName       : " << User.GetUserName();
        cout << "\nPassword       : " << User.GetPassword();
        cout << "\nPermissions    : " << User.GetPermission();
        cout << "\n___________________\n";

    }

public:

    static void ShowFindUserScreen()
    {
        _DrawScreenHeader("\tFind User Screen");

        string UserName = "";

        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate::ReadString();

        while(!clsUser::IsUserExist(UserName))
        {
            cout << "\nUser is not found, choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User1 = clsUser::Find(UserName);

        if(!User1.IsEmpty())
        {
            cout << "\nUser Found :-)\n";

            _Print(User1);
        }
        else
        {
            cout << "\nUser was not Found :-(\n";
        }
    }
};

#endif // CLSFINDUSERSCREEN_H_INCLUDED
