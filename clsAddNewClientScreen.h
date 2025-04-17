#ifndef CLSADDNEWCLIENTSCREEN_H_INCLUDED
#define CLSADDNEWCLIENTSCREEN_H_INCLUDED

#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;


class clsAddNewClientScreen : protected clsScreen
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
    static void ShowAddNewClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
        {
            return;// this will exit the function and it will not continue
        }

        _DrawScreenHeader("\tAdd New Client");

        string AccountNumber = "";

        cout << "\nPlease Enter Client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while(clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount is already used, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

        _ReadclientInfo(NewClient);

        clsBankClient::enSaveResults SaveResult;

        SaveResult = NewClient.Save();

        switch(SaveResult)
        {
            case clsBankClient::enSaveResults::svSucceeded:
                cout << "\nAccount Added Successfully :-)\n";
                _Print(NewClient);
                break;

            case clsBankClient::enSaveResults::svFaildEmptyObject:
                cout << "\nError account was not saved because it's Empty\n";
                break;

            case clsBankClient::enSaveResults::svFailAccountNumberExists:
                cout << "\nError account was not saved because account number is used!\n";
                break;
        }
    }
};


#endif // CLSADDNEWCLIENTSCREEN_H_INCLUDED
