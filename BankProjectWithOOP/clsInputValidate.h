#pragma once

#include <iostream>
#include <string>
#include "clsString.h"
#include "clsDate.h"



class clsInputValidate {
public:

    static bool IsNumberBetween(int Num, int From, int To) {

        return (Num >= From && Num <= To) ? true : false;
    };

    static bool IsNumberBetween(double Num, double From, double To) {

        return (Num >= From && Num <= To) ? true : false;
    };

    static bool IsDateBetween(clsDate Date, clsDate FromDate, clsDate ToDate) {

        if (!clsDate::IsDate1BeforeDate2(FromDate, ToDate)) {

            clsDate::SwapDates(FromDate, ToDate);
        }

        /*if (clsDate::IsDate1EqualDate2(Date, FromDate) || clsDate::IsDate1AfterDate2(Date, FromDate)) {

            if (clsDate::IsDate1BeforeDate2(Date, ToDate) || clsDate::IsDate1EqualDate2(Date, ToDate)) {

                return true;
            }
        }

        return false;*/

        return ((clsDate::IsDate1EqualDate2(Date, FromDate) || clsDate::IsDate1AfterDate2(Date, FromDate))
            && (clsDate::IsDate1BeforeDate2(Date, ToDate) || clsDate::IsDate1EqualDate2(Date, ToDate))) ? true : false;
    }

    static int ReadIntNumber(std::string Message = "Invalid Number, Enter again: \n") {

        int Number = 0;
        cin >> Number;

        while (cin.fail()) {

            //user didn't input Number
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << Message << std::endl;
            cin >> Number;
        }

        return Number;
    }

    static double ReadDblNumber(std::string Message = "Invalid Number, Enter again: \n") {

        double Number = 0;
        cin >> Number;

        while (cin.fail()) {

            //user didn't input Number
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << Message << std::endl;
            cin >> Number;
        }

        return Number;
    }

    static int ReadIntNumberBetween(int From, int To, std::string Message) {

        int Number = ReadIntNumber();

        while (Number < From || Number > To) {

            std::cout << Message << std::endl;

            Number = ReadIntNumber();
        }

        return Number;
    }

    static int ReadDblNumberBetween(int From, int To, std::string Message) {

        int Number = ReadIntNumber("Invalid Number, Enter again: \n");

        while (Number < From || Number > To) {

            std::cout << Message << std::endl;

            Number = ReadIntNumber("Invalid Number, Enter again: \n");
        }

        return Number;
    }

    static double ReadFloatNumber(string ErrorMessage = "Invalid Number, Enter again\n")
    {
        float Number;
        while (!(cin >> Number)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
        }
        return Number;
    }

    static double ReadFloatNumberBetween(double From, double To, string ErrorMessage = "Number is not within range, Enter again:\n")
    {
        float Number = ReadFloatNumber();

        while (!IsNumberBetween(Number, From, To)) {

            cout << ErrorMessage;
            Number = ReadDblNumber();
        }
        return Number;
    }

    static short ReadShortNumber(string ErrorMessage = "Invalid Number, Enter again\n")
    {
        short Number;
        while (!(cin >> Number)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << ErrorMessage;
        }
        return Number;
    }

    static short ReadShortNumberBetween(short From, short To, string ErrorMessage = "Number is not within range, Enter again:\n")
    {
        int Number = ReadShortNumber();

        while (!IsNumberBetween(Number, From, To))
        {
            cout << ErrorMessage;
            Number = ReadShortNumber();
        }
        return Number;
    }

    static bool IsValideDate(clsDate Date)
    {
        return	clsDate::IsValidDate(Date);
    }

    static string ReadString()
    {
        string  S1 = "";
        // Usage of std::ws will extract allthe whitespace character
        getline(cin >> ws, S1);
        return S1;
    }
};