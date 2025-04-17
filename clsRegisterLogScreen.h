#ifndef CLSREGISTERLOGSCREEN_H_INCLUDED
#define CLSREGISTERLOGSCREEN_H_INCLUDED

#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"

class clsRegisterLogScreen : protected clsScreen
{
private:
    static void _PrintRegisterRecordLine(clsBankClient::RegisterLog Reg)
    {
        std::cout << setw(8) << left << "" ;
        std::cout << "| " << setw(30) << left << Reg.Date;
        std::cout << "| " << setw(12) << left << Reg.SourceAccountNumber;
        std::cout << "| " << setw(12) << left << Reg.DestinationAccountNumber;
        std::cout << "| " << setw(15) << left << Reg.Amount;
        std::cout << "| " << setw(12) << left << Reg.SourceAccountBalance;
        std::cout << "| " << setw(12) << left << Reg.DestinationAccountBalance;
        std::cout << "| " << setw(10) << left << Reg.UserName;

    }

public:

    static void ShowRegisterLoglist()
    {

        vector <clsBankClient::RegisterLog> vRegisters = clsBankClient::GetRegisterLogList();
        string Title = "\t  Register Log List Screen";
        string subTitle = "\t  (" + to_string(vRegisters.size()) + ") Register(s).";

        _DrawScreenHeader(Title, subTitle);

        std::cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        std::cout << "______________________________________________\n" << endl;

        std::cout << setw(8) << left << "" << "| " << left << setw(30) << "Date";
        std::cout << "| " << left << setw(12) << "S.AccN";
        std::cout << "| " << left << setw(12) << "D.AccN";
        std::cout << "| " << left << setw(15) << "Amount";
        std::cout << "| " << left << setw(12) << "S.AccB";
        std::cout << "| " << left << setw(12) << "D.AccB";
        std::cout << "| " << left << setw(10) << "User";

        std::cout << setw(8)<< left << "" << "\n\t_______________________________________________________";
        std::cout << "______________________________________________\n" << endl;

        if (vRegisters.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else

            for (clsBankClient::RegisterLog Reg : vRegisters)
            {
               std::cout << endl;
            }

        std::cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        std::cout << "______________________________________________\n" << endl;


};


#endif // CLSREGISTERLOGSCREEN_H_INCLUDED
