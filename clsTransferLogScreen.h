#ifndef CLSTRANSFERLOGSCREEN_H_INCLUDED
#define CLSTRANSFERLOGSCREEN_H_INCLUDED

#pragma once

#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include <fstream>
#include "clsBankClient.h"


class clsTransferLogScreen :protected clsScreen
{
    private:
    static void _PrintRegisterRecordLine(clsBankClient::RegisterLog Reg)
    {
        cout << setw(5) << left << "\t" ;
        cout << "| " << setw(25) << left << Reg.Date;
        cout << "| " << setw(10) << left << Reg.SourceAccountNumber;
        cout << "| " << setw(10) << left << Reg.DestinationAccountNumber;
        cout << "| " << setw(15) << left << Reg.Amount;
        cout << "| " << setw(12) << left << Reg.SourceAccountBalance;
        cout << "| " << setw(12) << left << Reg.DestinationAccountBalance;
        cout << "| " << setw(10) << left << Reg.UserName;

    }

public:

    static void ShowRegisterLoglist()
    {

        vector <clsBankClient::RegisterLog> vRegisters = clsBankClient::GetRegisterLogList();
        string Title = "\t  Register Log List Screen";
        string subTitle = "\t  (" + to_string(vRegisters.size()) + ") Register(s).";

        _DrawScreenHeader(Title, subTitle);

        cout << setw(5) << left << "" << "\n\t_____________________________________________________________";
        cout << "______________________________________________________\n" << endl;

        cout << setw(5) << left << "\t" << "| " << left << setw(25) << "Date";
        cout << "| " << left << setw(10) << "S.AccN";
        cout << "| " << left << setw(10) << "D.AccN";
        cout << "| " << left << setw(15) << "Amount";
        cout << "| " << left << setw(12) << "S.AccB";
        cout << "| " << left << setw(12) << "D.AccB";
        cout << "| " << left << setw(10) << "User";

        cout << setw(5)<< left << "" << "\n\t_____________________________________________________________";
        cout << "______________________________________________________\n" << endl;

        if (vRegisters.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else

            for (clsBankClient::RegisterLog Reg : vRegisters)
            {
               cout << endl;
               _PrintRegisterRecordLine(Reg);
            }

        cout << setw(8) << left << "" << "\n\t_____________________________________________________________";
        cout << "______________________________________________________\n" << endl;
    }

};


#endif // CLSTRANSFERLOGSCREEN_H_INCLUDED
