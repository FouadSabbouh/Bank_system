#ifndef CLSTRANSACTIONSSCREEN_H_INCLUDED
#define CLSTRANSACTIONSSCREEN_H_INCLUDED


#pragma once

#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"





class clsTransactionsScreen : protected clsScreen
{
private:
    enum enTransactionsMenuOptions { eDeposit = 1, eWithdraw = 2, eShowTotalBalances = 3, eTransfer = 4, eRegisterLog = 5, eShowMainMenu = 6};

    static short _ReadTransactionsOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number Between 1 to 6? ");

        return choice;
    }

    static void _ShowDepositScreen()
    {
       // cout << "\nDeposit Screen will be here.\n";
       clsDepositScreen::ShowDepositScreen();
    }

    static void _ShowWithdrawScreen()
    {
        //cout << "\n Withdraw Screen will be here.\n";
        clsWithdrawScreen::ShowWithdrawScreen();
    }

    static void _ShowTotalBalancesScreen()
    {
        //cout << "\nBalances Screen will be here.\n";
        clsTotalBalancesScreen::ShowTotalBalances();
    }

    static void _ShowTransferScreen()
    {
        clsTransferScreen::ShowTransferScreen();
    }

     static void _ShowRegisterLogScreen()
    {
        cout << "\nRegister Log Screen will be here.\n";
        //clsRegisterLogScreen::ShowRegisterLoglist();
        clsTransferLogScreen::ShowRegisterLoglist();
    }

    static void _GoBackToTransactionsMenu()
    {
        cout << "\n\nPress any key to go back to Transactions Menu...";
        system("pause>0");
        ShowTransactiosMenu();
    }


    static void _PerformTransactionsMenuOption(enTransactionsMenuOptions TransactionsMenuOption)
    {
        switch(TransactionsMenuOption)
        {

        case enTransactionsMenuOptions::eDeposit:
            {
                system("cls");
                _ShowDepositScreen();
                _GoBackToTransactionsMenu();
                break;
            }

        case enTransactionsMenuOptions::eWithdraw:
            {
                system("cls");
                _ShowWithdrawScreen();
                _GoBackToTransactionsMenu();
                break;
            }

        case enTransactionsMenuOptions::eShowTotalBalances:
            {
                system("cls");
                _ShowTotalBalancesScreen();
                _GoBackToTransactionsMenu();
                break;
            }

        case enTransactionsMenuOptions::eTransfer:
            {
                system("cls");
                _ShowTransferScreen();
                _GoBackToTransactionsMenu();
                break;
            }

        case enTransactionsMenuOptions::eRegisterLog:
            {
                system("cls");
                _ShowRegisterLogScreen();
                _GoBackToTransactionsMenu();
                break;
            }

        case enTransactionsMenuOptions::eShowMainMenu:
            {
                //do nothing here the main screen will handle it :-) ;
            }
        }
    }


public:


    static void ShowTransactiosMenu()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pTranactions))
        {
            cout << "Press any key to go back main screen...";
            system("pause>0");
            return;// this will exit the function and it will not continue
        }

        system("cls");

        _DrawScreenHeader("\tTransactions Screen");


        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tTransactions Menu \n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Transfer.\n";
        cout << setw(37) << left << "" << "\t[5] Register Log List.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformTransactionsMenuOption((enTransactionsMenuOptions) _ReadTransactionsOption());

    }
};


#endif // CLSTRANSACTIONSSCREEN_H_INCLUDED
