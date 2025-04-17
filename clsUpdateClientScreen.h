#ifndef CLSUPDATECLIENTSCREEN_H_INCLUDED
#define CLSUPDATECLIENTSCREEN_H_INCLUDED

#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateClientScreen : protected clsScreen
{
private:

    static void _ReadclientInfo (clsBankClient & client)
    {
        cout << "\nEnter FirstName: ";
        client.SetFirstName(clsInputValidate::ReadString());

        cout << "\nEnter LastName: ";
        client.SetLastName(clsInputValidate::ReadString());

        cout << "\nEnter Email: ";
        client.SetEmail(clsInputValidate::ReadString());

        cout << "\nEnter Phone: ";
        client.SetPhone(clsInputValidate::ReadString());

        cout << "\nEnter PinCode: ";
        client.SetPinCode(clsInputValidate::ReadString());

        cout << "\nEnter Account Balance: ";
        client.SetAccountBalance(clsInputValidate::ReadFloatNumber());

    }

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

    static void ShowUpdateClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
        {
            return;// this will exit the function and it will not continue
        }

        _DrawScreenHeader("Update Client Screen");

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

        cout << "\n\nUpdate Client Info:";
        cout << "_______________________";

        _ReadclientInfo(Client1);

        clsBankClient::enSaveResults SaveResult;
        SaveResult = Client1.Save();

        switch(SaveResult)
        {
        case clsBankClient::enSaveResults::svSucceeded:
            {
                cout << "\nAccount Updated Successfully :-)\n";
                _Print(Client1);
                break;
            }
        case clsBankClient::enSaveResults::svFaildEmptyObject:
            cout << "\nError account was not saved because it's Empty";
            break;
        }
    }
};


#endif // CLSUPDATECLIENTSCREEN_H_INCLUDED
