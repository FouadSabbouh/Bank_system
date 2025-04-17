#ifndef CLSDEPOSITSCREEN_H_INCLUDED
#define CLSDEPOSITSCREEN_H_INCLUDED

#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsDepositScreen : protected clsScreen
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

    static void ShowDepositScreen()
    {
        _DrawScreenHeader("\t Deposit Screen");

        string AccountNumber = _ReadAccountNumber();

        while(!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _Print(Client1);

        double Amount = 0;
        cout << "\nPlease Enter Deposit Amount : ";
        Amount = clsInputValidate::ReadDblNumber();

        cout << "\nAre you sure you want to perform this transaction (Y/N)? ";
        char Answer = 'n';
        cin >> Answer;

        if(Answer == 'y' || Answer == 'Y')
        {
          Client1.Deposit(Amount);
          cout << "\nAmount Deposited Successfully.\n";
          cout << "\nNew Balance is: " << Client1.GetAccountBalance();
        }else{

            cout << "\nOperation was  canceled. \n";
        }
    }
};




#endif // CLSDEPOSITSCREEN_H_INCLUDED
