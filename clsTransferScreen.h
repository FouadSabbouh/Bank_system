#ifndef CLSTRANSFERSCREEN_H_INCLUDED
#define CLSTRANSFERSCREEN_H_INCLUDED

#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "Global.h"

class clsTransferScreen : protected clsScreen
{
private:
    static void _print(clsBankClient Client)
    {
        cout << "\n Client Card: ";
        cout << "\n---------------------------------------------\n";
        cout << " Full Name      :  " << Client.FullName() << endl;
        cout << " Account Number : " << Client.AccountNumber() << endl;
        cout << " Account Balance: " << Client.GetAccountBalance();
        cout << "\n----------------------------------------------\n";
    }


    static string _ReadAccountNumber()
    {
        string AccountNumber;
        cout << "\nPlease Enter Account Number to Transfer From: ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        return AccountNumber;
    }

    static float ReadAmount(clsBankClient SourceClient)
   {
       float Amount;

       cout << "\nEnter Transfer Amount? ";

       Amount = clsInputValidate::ReadFloatNumber();

       while (Amount > SourceClient.GetAccountBalance())
       {
           cout << "\nAmount Exceeds the available Balance, Enter another Amount ? ";
           Amount = clsInputValidate::ReadDblNumber();
       }
       return Amount;
   }

public:
    static void ShowTransferScreen()
    {
        _DrawScreenHeader("\tTransfer Screen");

        clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber());

        _print(SourceClient);

        clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber());

        _print(DestinationClient);

        float Amount = ReadAmount(SourceClient);


        cout << "\nAre you sure you want to perform this operation? y/n? ";
        char Answer = 'n';
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            if (SourceClient.Transfer(Amount, DestinationClient, CurrentUser.GetUserName()))
            {
                cout << "\nTransfer done successfully\n";
            }
            else
            {
                cout << "\nTransfer Faild \n";
            }
        }

        _print(SourceClient);
        _print(DestinationClient);


    }

};


#endif // CLSTRANSFERSCREEN_H_INCLUDED
