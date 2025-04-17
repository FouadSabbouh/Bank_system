#ifndef CLSDELETECLIENTSCREEN_H_INCLUDED
#define CLSDELETECLIENTSCREEN_H_INCLUDED

#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsDeleteClientScreen : protected clsScreen
{
private:
    static void _Print(clsBankClient client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName      : " << client.GetFirstName();
        cout << "\nLastName       : " << client.GetLastName();
        cout << "\nFull Name      : " << client.FullName();
        cout << "\nEmail          : " << client.GetEmail();
        cout << "\nPhone          : " << client.GetPhone();
        cout << "\nAccount Number : " << client.AccountNumber();
        cout << "\nPassword       : " << client.GetPinCode();
        cout << "\nBalance        : " << client.GetAccountBalance();
        cout << "\n___________________\n";

    }
public:

    static void ShowDeleteClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
        {
            return;// this will exit the function and it will not continue
        }

        _DrawScreenHeader("\tDelete Client Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter Client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while(!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _Print(Client1);

        cout << "\nAre you sure you want to delete this Client y/n? ";

        char Answer = 'n';
        cin >> Answer;

        if(Answer == 'y' || Answer == 'Y')
        {
            if(Client1.Delete())
            {
                cout << "\nClient Deleted Successfully :-)\n";

                _Print(Client1);
            }
            else
            {
                cout << "\nError Client was not Deleted\n";
            }
        }
    }
};

#endif // CLSDELETECLIENTSCREEN_H_INCLUDED
