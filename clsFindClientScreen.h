#ifndef CLSFINDCLIENTSCREEN_H_INCLUDED
#define CLSFINDCLIENTSCREEN_H_INCLUDED

#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsFindClientScreen : protected clsScreen
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

    static void ShowFindClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pFindClient))
        {
            return;// this will exit the function and it will not continue
        }

        _DrawScreenHeader("\tFind Client Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter Client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while(!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);

        if(!Client1.IsEmpty())
        {
            cout << "\nClient Found :-)\n";

            _Print(Client1);
        }
        else
        {
            cout << "\nClient was not Found :-(\n";
        }
    }
};


#endif // CLSFINDCLIENTSCREEN_H_INCLUDED
