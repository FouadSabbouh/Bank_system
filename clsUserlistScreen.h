#ifndef CLSUSERLISTSCREEN_H_INCLUDED
#define CLSUSERLISTSCREEN_H_INCLUDED

#pragma once
#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>


class clsUserListScreen : protected clsScreen
{
private:
    static void _PrintUserRecordLine(clsUser User)
    {
        cout << setw(8) << left << "" ;
        cout << "| " << setw(20) << left << User.FullName();
        cout << "| " << setw(12) << left << User.GetPhone();
        cout << "| " << setw(25) << left << User.GetEmail();
        cout << "| " << setw(10) << left << User.GetUserName();
        cout << "| " << setw(10) << left << User.GetPassword();
        cout << "| " << setw(10) << left << User.GetPermission();

    }

public:

    static void ShowUserslist()
    {

        vector <clsUser> vUsers = clsUser::GetUsersList();
        string Title = "\t  User List Screen";
        string subTitle = "\t  (" + to_string(vUsers.size()) + ") User(s).";

        _DrawScreenHeader(Title, subTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(20) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(25) << "Email";
        cout << "| " << left << setw(10) << "User Name";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(10) << "Permissions";

        cout << setw(8)<< left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        if (vUsers.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else

            for (clsUser User : vUsers)
            {
                _PrintUserRecordLine(User);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

}


};

#endif // CLSUSERLISTSCREEN_H_INCLUDED
