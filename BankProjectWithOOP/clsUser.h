#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"
#include <vector>
#include <fstream>
#include "clsBankClient.h"
#include "clsUtil.h"
#include "GlobalFiles.h"


using namespace std;

//string UsersFile = "\\Users.txt";
//string LoginRegisterFile = "\\LoginRegister.txt";
//string TransferRegisterFile = "\\TransferRegister.txt";

class clsUser : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;
    string _UserName;
    string _Password;
    int _Permissions;

    bool _MarkedForDelete = false;

    struct stLoginRegisterRecord;
    static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
    {
        stLoginRegisterRecord LoginRegisterRecord;


        vector <string> LoginRegisterDataLine = clsString::Split(Line, Seperator);
        LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
        LoginRegisterRecord.UserName = LoginRegisterDataLine[1];
        LoginRegisterRecord.Password = clsUtil::DecryptText(LoginRegisterDataLine[2]);
        LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);

        return LoginRegisterRecord;

    }

    struct stTransferRegisterRecord;
    static stTransferRegisterRecord _ConvertTransferRegisterLineToRecord(string Line, string Seperator = "#//#")
    {
        stTransferRegisterRecord LoginRegisterRecord;


        vector <string> LoginRegisterDataLine = clsString::Split(Line, Seperator);
        LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
        LoginRegisterRecord.AccountNumberSend = LoginRegisterDataLine[1];
        LoginRegisterRecord.AccountNumberTake = LoginRegisterDataLine[2];
        LoginRegisterRecord.Amount = stod(LoginRegisterDataLine[3]);
        LoginRegisterRecord.AccountSendBalans = stod(LoginRegisterDataLine[4]);
        LoginRegisterRecord.AccountTakeBalans = stod(LoginRegisterDataLine[5]);
        LoginRegisterRecord.UserName = LoginRegisterDataLine[6];

        return LoginRegisterRecord;

    }


    string _PrepareLogInRecord(string Seperator = " #//#") {

        string LoginRecord = "";
        LoginRecord += clsDate::DateToString(clsDate()) + "  ";
        LoginRecord += clsDate::GetsystemTimeString() + Seperator;
        LoginRecord += UserName + Seperator;
        LoginRecord += clsUtil::EncryptText(Password) + Seperator;
        LoginRecord += to_string(Permissions);

        return LoginRecord;
    }

    string _PrepareTransferRecord(clsBankClient From, clsBankClient To, double Amount, string Seperator = " #//#") {

        

        string LoginRecord = "";
        LoginRecord += clsDate::DateToString(clsDate()) + "  ";
        LoginRecord += clsDate::GetsystemTimeString() + Seperator;
        LoginRecord += From.AccountNumber() + Seperator;
        LoginRecord += To.AccountNumber() + Seperator;
        LoginRecord += to_string(Amount) + Seperator;
        LoginRecord += to_string(From.AccountBalance) + Seperator;
        LoginRecord += to_string(To.AccountBalance) + Seperator;
        LoginRecord += UserName;

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

        string UserRecord = "";
        UserRecord += User.FirstName + Seperator;
        UserRecord += User.LastName + Seperator;
        UserRecord += User.Email + Seperator;
        UserRecord += User.Phone + Seperator;
        UserRecord += User.UserName + Seperator;
        UserRecord += clsUtil::EncryptText(User.Password) + Seperator;
        UserRecord += to_string(User.Permissions);

        return UserRecord;

    }

    static  vector <clsUser> _LoadUsersDataFromFile()
    {

        vector <clsUser> vUsers;

        fstream MyFile;
        MyFile.open(UsersFile, ios::in);//read Mode

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
        MyFile.open(UsersFile, ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsUser U : vUsers)
            {
                if (U.MarkedForDeleted() == false)
                {
                    //we only write records that are not marked for delete.  
                    DataLine = _ConverUserObjectToLine(U);
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

        for (clsUser& U : _vUsers)
        {
            if (U.UserName == UserName)
            {
                U = *this;
                break;
            }

        }

        _SaveUsersDataToFile(_vUsers);

    }

    void _AddNew()
    {

        _AddDataLineToFile(_ConverUserObjectToLine(*this));
    }

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open(UsersFile, ios::out | ios::app);

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

    struct stTransferRegisterRecord {

        string DateTime;
        string AccountNumberSend;
        string AccountNumberTake;
        double Amount;
        double AccountSendBalans;
        double AccountTakeBalans;
        string UserName;
    };

    enum enPermissions {
        eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
        pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64, pShowLogInRegister = 128
    };

    struct stLoginRegisterRecord {

        string DateTime;
        string UserName;
        string Password;
        int Permissions;
    };

    clsUser(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string UserName, string Password,
        int Permissions) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;
    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    bool MarkedForDeleted()
    {
        return _MarkedForDelete;
    }

    string GetUserName()
    {
        return _UserName;
    }

    void SetUserName(string UserName)
    {
        _UserName = UserName;
    }

    __declspec(property(get = GetUserName, put = SetUserName)) string UserName;



    void SetPassword(string Password)
    {
        _Password = Password;
    }

    string GetPassword()
    {
        return _Password;
    }

    __declspec(property(get = GetPassword, put = SetPassword)) string Password;



    void SetPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }

    int GetPermissions()
    {
        return _Permissions;
    }

    __declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;



    static clsUser Find(string UserName)
    {
        fstream MyFile;
        MyFile.open(UsersFile, ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName == UserName)
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
        MyFile.open(UsersFile, ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName == UserName && User.Password == Password)
                {
                    MyFile.close();
                    return User;
                }

            }

            MyFile.close();

        }
        return _GetEmptyUserObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

    enSaveResults Save()
    {

        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if (IsEmpty())
            {
                return enSaveResults::svFaildEmptyObject;
            }
        }

        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResults::svSucceeded;

            break;
        }

        case enMode::AddNewMode:
        {
            //This will add new record to file or database
            if (clsUser::IsUserExist(_UserName))
            {
                return enSaveResults::svFaildUserExists;
            }
            else
            {
                _AddNew();
                //We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }

            break;
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

        for (clsUser& U : _vUsers)
        {
            if (U.UserName == _UserName)
            {
                U._MarkedForDelete = true;
                break;
            }

        }

        _SaveUsersDataToFile(_vUsers);

        *this = _GetEmptyUserObject();

        return true;

    }

    static clsUser GetAddNewUserObject(string UserName)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    }

    static vector <clsUser> GetUsersList()
    {
        return _LoadUsersDataFromFile();
    }

    bool CheckAccessPermission(enPermissions Permission) {

        if (this->Permissions == enPermissions::eAll)
            return true;

        if ((Permission & this->Permissions) == Permission)
            return true;
        else
            return false;
    }

    void RegisterLogIn() {

        string stDataLine = _PrepareLogInRecord();

        fstream MyFile;
        MyFile.open(LoginRegisterFile, ios::out | ios::app);

        if(MyFile.is_open()) {
        
            MyFile << stDataLine << endl;

            MyFile.close();
        }
    }

    void RegisterTransfer(clsBankClient From, clsBankClient To, double Amount) {

        string stDataLine = _PrepareTransferRecord(From, To, Amount);

        fstream MyFile;
        MyFile.open(TransferRegisterFile, ios::out | ios::app);

        if (MyFile.is_open()) {

            MyFile << stDataLine << endl;

            MyFile.close();
        }
    }

    static  vector <stLoginRegisterRecord> GetLoginRegisterList()
    {
        vector <stLoginRegisterRecord> vLoginRegisterRecord;

        fstream MyFile;
        MyFile.open(LoginRegisterFile, ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;

            stLoginRegisterRecord LoginRegisterRecord;

            while (getline(MyFile, Line))
            {

                LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);

                vLoginRegisterRecord.push_back(LoginRegisterRecord);

            }

            MyFile.close();

        }

        return vLoginRegisterRecord;
    }

    static  vector <stTransferRegisterRecord> GetTransferRegisterList()
    {
        vector <stTransferRegisterRecord> vTransferRegisterRecord;

        fstream MyFile;
        MyFile.open(TransferRegisterFile, ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;

            stTransferRegisterRecord TransferRegisterRecord;

            while (getline(MyFile, Line))
            {

                TransferRegisterRecord = _ConvertTransferRegisterLineToRecord(Line);

                vTransferRegisterRecord.push_back(TransferRegisterRecord);

            }

            MyFile.close();
        }

        return vTransferRegisterRecord;
    }

};
