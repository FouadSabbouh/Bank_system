#ifndef CLSBANKCLIENT_H_INCLUDED
#define CLSBANKCLIENT_H_INCLUDED

#pragma once
#include <iostream>
#include <string>
#include "Person.h"
#include "clsString.h"
#include <vector>
#include <fstream>

using namespace std;
class clsBankClient : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;
    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkForDelete = false;

    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
    {
        vector<string> vClientData;
        vClientData = clsString::Split(Line, Seperator);

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

    }

    static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
    {

        string stClientRecord = "";
        stClientRecord += Client.GetFirstName() + Seperator;
        stClientRecord += Client.GetLastName() + Seperator;
        stClientRecord += Client.GetEmail() + Seperator;
        stClientRecord += Client.GetPhone() + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += Client.GetPinCode() + Seperator;
        stClientRecord += to_string(Client.GetAccountBalance());

        return stClientRecord;

    }

    static  vector <clsBankClient> _LoadClientsDataFromFile()
    {

        vector <clsBankClient> vClients;

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                clsBankClient Client = _ConvertLinetoClientObject(Line);

                vClients.push_back(Client);
            }

            MyFile.close();

        }

        return vClients;

    }

    static void _SaveCleintsDataToFile(vector <clsBankClient> vClients)
    {

        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsBankClient C : vClients)
            {
                if(C.MarkForDeleted() == false )
                {
                    //we only write records that are not marked for delete.
                    DataLine = _ConverClientObjectToLine(C);
                    MyFile << DataLine << endl;
                }

            }

            MyFile.close();

        }

    }

    void _Update()
    {
        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();

        for (clsBankClient& C : _vClients)
        {
            if (C.AccountNumber() == AccountNumber())
            {
                C = *this;
                break;
            }

        }

        _SaveCleintsDataToFile(_vClients);

    }

    void _AddNew ()
    {
        _AddDataLineToFile(_ConverClientObjectToLine(*this));
    }

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }





    string _PrepareTransferLogRecord(float Amount,clsBankClient DestinationClient,
                                     string UserName, string Seperator = "#//#")
    {
        string TransferLogRecord = "";
        TransferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
        TransferLogRecord += _AccountNumber + Seperator;
        TransferLogRecord += DestinationClient.AccountNumber() + Seperator;
        TransferLogRecord += to_string(Amount) + Seperator;
        TransferLogRecord += to_string(_AccountBalance) + Seperator;
        TransferLogRecord += to_string(DestinationClient.GetAccountBalance()) + Seperator;
        TransferLogRecord += UserName;
        return TransferLogRecord;
    }

    void _RegisterTransferLog(float Amount, clsBankClient DestinationClient, string UserName)
    {

        string stDataLine = _PrepareTransferLogRecord( Amount,  DestinationClient,  UserName);

        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }



public:


    struct RegisterLog
    {
        string Date;
        string SourceAccountNumber;
        string DestinationAccountNumber;
        string Amount;
        string SourceAccountBalance;
        string DestinationAccountBalance;
        string UserName;
    };

    static RegisterLog _ConvertLineRegisterLogToRecord (string line, string Seperator = "#//#")
    {
        vector<string> VRegister = clsString::Split(line, Seperator);

        RegisterLog Reg;
        Reg.Date = VRegister[0];
        Reg.SourceAccountNumber = VRegister[1];
        Reg.DestinationAccountNumber = VRegister[2];
        Reg.Amount = VRegister[3];
        Reg.SourceAccountBalance = VRegister[4];
        Reg.DestinationAccountBalance = VRegister[5];
        Reg.UserName = VRegister[6];

        return Reg;

    }

    static vector<RegisterLog> _loadDataRegisterlogFromFile()
    {
        vector<RegisterLog> VRegister;

        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::in);// Read Mode

        if(MyFile.is_open())
        {
            string line;

            while(getline(MyFile, line))
            {
                RegisterLog Reg = _ConvertLineRegisterLogToRecord(line);
                VRegister.push_back(Reg);
            }

            MyFile.close();
        }

        return VRegister;
    }


    clsBankClient(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string AccountNumber, string PinCode,
        float AccountBalance) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;

    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }


    string AccountNumber()
    {
        return _AccountNumber;
    }
    bool MarkForDeleted()
    {
        return _MarkForDelete;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    string GetPinCode()
    {
        return _PinCode;
    }

    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    float GetAccountBalance()
    {
        return _AccountBalance;
    }

    void Deposit (double Amount)
    {
        _AccountBalance += Amount;
        Save();
    }

    bool Withdraw (double Amount)
    {
        if(Amount > _AccountBalance)
        {
            return false;
        }
        else
        {
            _AccountBalance -= Amount;
            Save();
            return true;
        }
    }
/*
    NOTE: not allow to use UI code in class
    void Print()
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName      : " << this->GetFirstName();
        cout << "\nLastName       : " << this->GetLastName();
        cout << "\nFull Name      : " << FullName();
        cout << "\nEmail          : " << this->GetEmail();
        cout << "\nPhone          : " << this->GetPhone();
        cout << "\nAccount Number : " << _AccountNumber;
        cout << "\nPassword       : " << _PinCode;
        cout << "\nBalance        : " << _AccountBalance;
        cout << "\n___________________\n";

    }

*/

   static clsBankClient Find(string AccountNumber)
    {


        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }

        return _GetEmptyClientObject();
    }

    static clsBankClient Find(string AccountNumber, string PinCode)
    {



        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber && Client.GetPinCode() == PinCode)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }
        return _GetEmptyClientObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFailAccountNumberExists = 2 };

    enSaveResults Save()
    {

        switch (_Mode)
        {
        case enMode::EmptyMode:
        {

                return enSaveResults::svFaildEmptyObject;
        }

        case enMode::UpdateMode:
        {


            _Update();

            return enSaveResults::svSucceeded;

            break;
        }

        case enMode::AddNewMode:
        {
            if(clsBankClient::IsClientExist(_AccountNumber))
            {
                return enSaveResults::svFailAccountNumberExists;
            }
            else
            {
                //we need to set the mode to update after add new
                _AddNew();
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }
        }
        }

    }

    static bool IsClientExist(string AccountNumber)
    {

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        return (!Client1.IsEmpty());
    }

    bool Delete()
    {
        vector <clsBankClient> _vClients;
        _vClients = _LoadClientsDataFromFile();

        for(clsBankClient & c : _vClients)
        {
            if(c.AccountNumber() == _AccountNumber)
            {
                c._MarkForDelete = true;
                break;
            }
        }


        _SaveCleintsDataToFile(_vClients);

        *this = _GetEmptyClientObject();

        return true;

    }

    static clsBankClient GetAddNewClientObject (string AccountNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }

    static vector<clsBankClient> GetClientsList()
    {
        return _LoadClientsDataFromFile();
    }

    static double GetTotalBalances()
	{
	    vector <clsBankClient> vClients = _LoadClientsDataFromFile();

	    double TotalBalances = 0;

	    for(clsBankClient client : vClients)
        {
            TotalBalances += client.GetAccountBalance();
        }

        return TotalBalances;
	}

	bool Transfer (int Amount, clsBankClient & Client, string UserName)
	{
	    if(Amount > _AccountBalance)
        {
            return false;
        }

        Withdraw(Amount);

        Client.Deposit(Amount);

        _RegisterTransferLog(Amount, Client, UserName);

        return true;
	}

	static vector<RegisterLog> GetRegisterLogList()
	{
	    return _loadDataRegisterlogFromFile();
	}

};


#endif // CLSBANKCLIENT_H_INCLUDED
