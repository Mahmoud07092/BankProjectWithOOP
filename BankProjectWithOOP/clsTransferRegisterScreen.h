#pragma once

#include <iostream>
#include <vector>
#include "clsScreen.h"
#include "clsString.h"
#include <string>
#include <iomanip>
#include <fstream>
#include "clsUser.h"


using namespace std;


class clsTransferRegisterScreen : private clsScreen {

private:

    static void _PrintLoginRegisterRecordLine(clsUser::stTransferRegisterRecord TransferRegisterRecord)
    {

        cout << setw(8) << left << "" << "| " << setw(25) << left << TransferRegisterRecord.DateTime;
        cout << "| " << setw(10) << left << TransferRegisterRecord.AccountNumberSend;
        cout << "| " << setw(10) << left << TransferRegisterRecord.AccountNumberTake;
        cout << "| " << setw(10) << left << TransferRegisterRecord.Amount;
        cout << "| " << setw(10) << left << TransferRegisterRecord.AccountSendBalans;
        cout << "| " << setw(10) << left << TransferRegisterRecord.AccountTakeBalans;
        cout << "| " << setw(10) << left << TransferRegisterRecord.UserName;
    }

public:

    static void ShowTransferLogScreen() {

        vector <clsUser::stTransferRegisterRecord> vTransferRegisterRecord = clsUser::GetTransferRegisterList();

        string Title = "\tTransfer Register List Screen";
        string SubTitle = "\t\t(" + to_string(vTransferRegisterRecord.size()) + ") Record(s).";

        _DrawScreenHeader("Title, SubTitle");

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(25) << "Date/Time";
        cout << "| " << left << setw(10) << "s.Acct";
        cout << "| " << left << setw(10) << "s.Acct";
        cout << "| " << left << setw(10) << "Amount";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "User";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vTransferRegisterRecord.size() == 0)
            cout << "\t\t\t\tNo Transfer Available In the System!";
        else

            for (clsUser::stTransferRegisterRecord Record : vTransferRegisterRecord)
            {

                _PrintLoginRegisterRecordLine(Record);
                std::cout << std::endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }

};

