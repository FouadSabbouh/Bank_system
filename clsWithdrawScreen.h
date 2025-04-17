#ifndef CLSWITHDRAWSCREEN_H_INCLUDED
#define CLSWITHDRAWSCREEN_H_INCLUDED

#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsWithdrawScreen : protected clsScreen
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

    static string _ReadAccountNumber()
    {
        string AccountNumber = "";
        cout << "\nPlease enter Account Number: ";
        cin >> AccountNumber;

        return AccountNumber;
    }

public:
    static void ShowWithdrawScreen()
    {
        _DrawScreenHeader("\t Withdraw Screen");

        string AccountNumber = _ReadAccountNumber();

        while(!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _Print(Client1);

        double Amount = 0;
        cout << "\nPlease Enter Withdraw Amount : ";
        Amount = clsInputValidate::ReadDblNumber();

        cout << "\nAre you sure you want to perform this transaction (Y/N)? ";
        char Answer = 'n';
        cin >> Answer;

        if(Answer == 'y' || Answer == 'Y')
        {
            if(Client1.Withdraw(Amount))
            {
                cout << "\nAmount Withdraw Successfully.\n";
                cout << "\nNew Balance is: " << Client1.GetAccountBalance();
            }
            else
            {
                cout << "\nCannot withdraw Insuffecient Balance!\n";
                cout << "\nAmount to withdraw is: " << Amount;
                cout << "\n Your Balance is: " << Client1.GetAccountBalance();
            }
        }
        else
        {
            cout << "\nOperation was canceled.\n";
        }
    }
};

#endif // CLSWITHDRAWSCREEN_H_INCLUDED
