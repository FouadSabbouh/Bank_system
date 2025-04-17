#ifndef CLSUSER_H_INCLUDED
#define CLSUSER_H_INCLUDED

#pragma once
#include <iostream>
#include "Person.h"
#include "clsString.h"
#include "clsDate.h"
#include <vector>
#include <fstream>
#include <string>
#include "clsUtil.h"


using namespace std;


class clsUser : public clsPerson
{
private:
    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;
    string _UserName;
    string _Password;
    int _Permissions;

    bool _MarkForDelete = false;



    string _PrepareLogInRecord( string Seperator = "#//#")
    {
        string LoginRecord = "";
        LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
        LoginRecord += _UserName + Seperator;
        LoginRecord += clsUtil::EncryptText(_Password) + Seperator;
        LoginRecord += to_string(_Permissions);
        return LoginRecord;
    }

    static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
    {
        vector<string> vUserData;
        vUserData = clsString::Split(Line, Seperator);

        return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
            vUserData[3], vUserData[4], clsUtil::DecryptText(vUserData[5]), stoi(vUserData[6]));

    }

    static string _ConverUserObjectToLine(clsUser User, string Seperator = "#//#")
    {

        string stUserRecord = "";
        stUserRecord += User.GetFirstName() + Seperator;
        stUserRecord += User.GetLastName() + Seperator;
        stUserRecord += User.GetEmail() + Seperator;
        stUserRecord += User.GetPhone() + Seperator;
        stUserRecord += User.GetUserName() + Seperator;
        stUserRecord += clsUtil::EncryptText(User.GetPassword()) + Seperator;
        stUserRecord += to_string(User.GetPermission());

        return stUserRecord;

    }

    static  vector <clsUser> _LoadUsersDataFromFile()
    {

        vector <clsUser> vUsers;

        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;


            while (getline(MyFile, Line))
            {

                clsUser User = _ConvertLinetoUserObject(Line);

                vUsers.push_back(User);
            }

            MyFile.close();

        }

        return vUsers;

    }

    static void _SaveUsersDataToFile(vector <clsUser> vUsers)
    {

        fstream MyFile;
        MyFile.open("Users.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsUser C : vUsers)
            {
                if(C.MarkForDeleted() == false )
                {
                    //we only write records that are not marked for delete.
                    DataLine = _ConverUserObjectToLine(C);
                    MyFile << DataLine << endl;
                }

            }

            MyFile.close();

        }

    }

    void _Update()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser& C : _vUsers)
        {
            if (C.GetUserName() == _UserName)
            {
                C = *this;
                break;
            }

        }

        _SaveUsersDataToFile(_vUsers);

    }

    void _AddNew ()
    {
        _AddDataLineToFile(_ConverUserObjectToLine(*this));
    }

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static clsUser _GetEmptyUserObject()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

public:


    enum enPermissions {
        eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
        pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64, pLoginRegister = 128
    };

    struct stLoginRegisterRecord
    {
        string DateTime;
        string UserName;
        string Password;
        int Permissions;

    };

    static stLoginRegisterRecord ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
    {
        stLoginRegisterRecord LoginRegisterRecord;


        vector <string> LoginRegisterDataLine = clsString::Split(Line, Seperator);
        LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
        LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
        LoginRegisterRecord.Password = LoginRegisterDataLine[2];
        LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);

        return LoginRegisterRecord;

    }

    // constractor
    clsUser(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string UserName, string Password, int Permission) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permission;

    }

    // check is this object empty
    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }



    //set and get for Username
    void SetUserName (string UserName)
    {
        _UserName = UserName;
    }

    string GetUserName()
    {
        return _UserName;
    }


    // set and get for Password
    void SetPassword (string Password)
    {
        _Password = Password;
    }
    string GetPassword()
    {
        return _Password;
    }

    // set and get for Permission
    void SetPermission (int Permission)
    {
        _Permissions = Permission;
    }
    int GetPermission()
    {
        return _Permissions;
    }




    // get mark for deleted boolean
    bool MarkForDeleted()
    {
        return _MarkForDelete;
    }


    static clsUser Find(string UserName)
    {


        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.GetUserName() == UserName)
                {
                    MyFile.close();
                    return User;
                }

            }

            MyFile.close();

        }

        return _GetEmptyUserObject();
    }

   static clsUser Find(string UserName, string Password)
    {


        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.GetUserName() == UserName && User.GetPassword() == Password)
                {
                    MyFile.close();
                    return User;
                }

            }

            MyFile.close();

        }

        return _GetEmptyUserObject();
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
            if(clsUser::IsUserExist(_UserName))
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

    static bool IsUserExist(string UserName)
    {

        clsUser User = clsUser::Find(UserName);
        return (!User.IsEmpty());
    }

    bool Delete()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for(clsUser & c : _vUsers)
        {
            if(c.GetUserName() == _UserName)
            {
                c._MarkForDelete = true;
                break;
            }
        }


        _SaveUsersDataToFile(_vUsers);

        *this = _GetEmptyUserObject();

        return true;

    }

    static clsUser GetAddNewUserObject (string UserName)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    }

    static vector<clsUser> GetUsersList()
    {
        return _LoadUsersDataFromFile();
    }

    bool CheckAccessPermission (enPermissions Permission)
    {
        if(Permission == enPermissions::eAll)
            return true;
        if((this->GetPermission() & Permission) == Permission)
            return true;
        else
            return false;
    }


     void RegisterLogIn()
    {

        string stDataLine = _PrepareLogInRecord();

        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

     static  vector <stLoginRegisterRecord> GetLoginRegisterList()
     {
         vector <stLoginRegisterRecord> vLoginRegisterRecord;

         fstream MyFile;
         MyFile.open("LoginRegister.txt", ios::in);//read Mode

         if (MyFile.is_open())
         {

             string Line;

             stLoginRegisterRecord LoginRegisterRecord;

             while (getline(MyFile, Line))
             {

                 LoginRegisterRecord = ConvertLoginRegisterLineToRecord(Line);

                 vLoginRegisterRecord.push_back(LoginRegisterRecord);

             }

             MyFile.close();

         }

         return vLoginRegisterRecord;

     }


};


#endif // CLSUSER_H_INCLUDED
