#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "Global.h"




class clsTransferScreen : private clsScreen {

private:

    static void _PrintClient(clsBankClient Client) {

        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";
    }

  /*  static clsBankClient _GetClint(std::string Str) {

        std::string ClientAcc;
        bool ClientExist = false;
        clsBankClient Client = clsBankClient::Find(ClientAcc);

        do {

            std::cout << Str;
            ClientAcc = clsInputValidate::ReadString();

            if (clsBankClient::IsClientExist(ClientAcc)) {

                Client = clsBankClient::Find(ClientAcc);
                ClientExist = false;
            }
            else {

                ClientExist = true;
                std::cout << "Client Not Found! \n";
            }

        } while (ClientExist);

        return Client;
    }*/

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

        while (Amount > SourceClient.AccountBalance)
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

        _PrintClient(SourceClient);

        clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber());

        _PrintClient(DestinationClient);

        float Amount = ReadAmount(SourceClient);


        cout << "\nAre you sure you want to perform this operation? y/n? ";
        char Answer = 'n';
        cin >> Answer;
        if (Answer == 'Y' || Answer == 'y')
        {
            if (SourceClient.Transfer(Amount, DestinationClient))
            {
                cout << "\nTransfer done successfully\n";
                CurrentUser.RegisterTransfer(SourceClient, DestinationClient, Amount);
            }
            else
            {
                cout << "\nTransfer Faild \n";
            }
        }

        _PrintClient(SourceClient);
        _PrintClient(DestinationClient);
    }   
    


	/*static void Transfer() {

		clsScreen::_DrawScreenHeader("Transfer Screen");

        clsBankClient TransferFromClient = _GetClint("Enter Account Number to Transfer From: ");
        _PrintClient(TransferFromClient);

        clsBankClient TransferToClient = _GetClint("Enter Account Number to Transfer To: ");
        _PrintClient(TransferToClient);


        bool AmountExceeds = true;

        while (AmountExceeds) {

            std::cout << "Enter Transfer Amount: ";
            double Amount = clsInputValidate::ReadDblNumber();

            if (TransferFromClient.AccountBalance >= Amount) {
                
                std::cout << "Are you sure you want to perform this operation? y/n: ";
                std::string ToDo = clsInputValidate::ReadString();
                
                if (ToDo == "y" || ToDo == "Y") {

                    TransferFromClient.Withdraw(Amount);
                    TransferToClient.Deposit(Amount);
                }

                _PrintClient(TransferFromClient);
                _PrintClient(TransferToClient);
                CurrentUser.RegisterTransfer(TransferFromClient, TransferToClient, Amount);
                AmountExceeds = false;
            }
            else {

                std::cout << "\nAmount Exceeds The available Balance, Enter Another Amount.\n" << std::endl;
            }
        }
	}     */


};

