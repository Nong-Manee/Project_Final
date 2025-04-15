#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
#include <string>
#include <map>
#include <regex>
#include <cctype>
#include <fstream>
#include <sstream>
#include "Node.h"
using namespace std;

class member: public NODE {
    private:
        string email;
        string phone;
        string password;
        string confirmPassword;
        string dateOfBirth;
        string dateOfRegis;
        int point = 0;
        string memberType = "Bronze";
    
    public:

        member() : NODE() {} 

        bool checkEmail (const string& email){
            regex emailPattern (R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.(com|net|org|co\.th|ac\.th)$)");
            return regex_match(email, emailPattern);
        }

        bool checkPhone (const string& phoneStr){
            regex phonePattern(R"(^\d{10}$)");
            return regex_match(phoneStr, phonePattern);
        }

        bool checkPassword (const string& password){
            bool upper = false, lower = false, digit = false, speChar = false;
            for (char c : password){
                if (isupper(c)) upper = true;
                if (islower(c)) lower = true;
                if (isdigit(c)) digit = true;
                if (!isalnum(c)) speChar = true;
            }
            
            bool have = true;
            if (password.length() < 8){
                cout << "Password must be at least 8 characters." << endl;
                have = false;
            }
            if (!upper){
                cout << "There is no Uppercase letter in Password. Please add at least 1 Uppercase letter" << endl;
                have =  false;
            }
            if (!lower){
                cout << "There is no Lowercase letter in Password. Please add at least 1 Lowercase letter" << endl;
                have = false;
            }
            if (!digit){
                cout << "There is no Digit in Password. Please add at least 1 Digit" << endl;
                have = false;
            }
            if (!speChar){
                cout << "There is no Special Character in Password. Please add at least 1 Special Character" << endl;
                have = false;
            }
            return have;
        }

        bool checkDate (const string& date){
            regex datePattern(R"(^(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[012])/\d{4}$)");
            return regex_match(date, datePattern);
        }

        void saveToFile (){
            ofstream toFile("Membership.txt", ios::app);
            if (toFile.is_open()){
                toFile << memberId << ","
                       << name << ","
                       << email << ","
                       << phone << ","
                       << password << ","
                       << dateOfBirth << ","
                       << dateOfRegis << ","
                       << point << ","
                       << memberType << endl;
                toFile.close();
                cout << "Your Registation is in Our System!" << endl;
            }
            else cout << "Cannot Open File" << endl;
        }

        static void readFromFile(NODE*& head){
            head = NULL;
            ifstream fromFile("Membership.txt");
            if (!fromFile.is_open()){
                cout << "Cannot Open File" << endl;
                return;
            }
            string line;
            NODE* currentPtr = NULL;
            while (getline(fromFile, line)){
                stringstream ss(line);
                member* memberFromFile = new member;
                string phoneStr;
       
                ss >> memberFromFile->memberId;
                ss.ignore(); 
                getline(ss, memberFromFile->name, ',');
                getline(ss, memberFromFile->email, ',');
                getline(ss, phoneStr, ',');
                memberFromFile->phone = stoll(phoneStr);
                getline(ss, memberFromFile->password, ',');
                getline(ss, memberFromFile->dateOfBirth, ',');
                getline(ss, memberFromFile->dateOfRegis, ',');
                ss >> memberFromFile->point;
                ss.ignore(); 
                getline(ss, memberFromFile->memberType, ',');
                memberFromFile->insert(NULL);
                if (head == NULL){
                    head = memberFromFile;
                    currentPtr = head;
                }
                else{
                    currentPtr->insert(memberFromFile);
                    currentPtr = memberFromFile;
                }
            }
            fromFile.close();
        }

        void updateData(NODE* head, long Id){
            NODE* currentPtr = head;
            while (currentPtr != NULL){
                member* memberEdit = dynamic_cast<member*>(currentPtr);
                if (memberEdit && memberEdit->memberId == Id){
                    cout << "Member Found!" << endl;
                    int choice;
                    do {
                        memberEdit->showInformation();
                        cout << "Please Enter the Number of Information you want to Edit (1-6), or 0 to back to Menu ";
                        cin >> choice;
                        if (choice >= 1 && choice <= 6) {
                            memberEdit->editInformation(choice);
                        }
                    } while (choice != 0);
                    cout << "Member information updated!" << endl;
                    return;
                    }
                    currentPtr = currentPtr->move_next();
                }
                cout << "Member ID " << Id << "is not Found" << endl;
            }

        void saveEditToFile(NODE* head){
            ofstream toFile("Membership.txt");
            if (!toFile.is_open()) {
                cout << "Cannot open File" << endl;
                return;
            }
            NODE* currentPtr = head;
            while (currentPtr != NULL){
                member* memberToFile = dynamic_cast<member*>(currentPtr);
                if (memberToFile){
                    toFile << memberToFile->memberId << ","
                           << memberToFile->name << ","
                           << memberToFile->email << ","
                           << memberToFile->phone << ","
                           << memberToFile->password << ","
                           << memberToFile->dateOfBirth << ","
                           << memberToFile->dateOfRegis << ","
                           << memberToFile->point << ","
                           << memberToFile->memberType << endl;
                }
                currentPtr = currentPtr->move_next();
            }
            toFile.close();
            cout << "Your Edit Information is in Our System!";
        }

        static member* login(NODE*& head){
            string inputEmail, inputPassword;
            char again;
            readFromFile(head);
            do {
                cout << "Welcome To Our Restaurant's Membership !" << endl;
                cout << "Please Fill in The Information for Login" << endl;

                cout << "Please Enter your Email : ";
                getline(cin, inputEmail);

                cout << "Please Enter your Password : ";
                getline(cin, inputPassword);

                NODE* currentPtr = head;
                while (currentPtr != NULL){
                    member* login = dynamic_cast<member*>(currentPtr);
                    if (login && login->email == inputEmail && login->password == inputPassword){
                        cout << "Login Successful!" << endl;
                        return login;
                    }
                    currentPtr = currentPtr->move_next();
                }

                cout << "This Email or Password is not correct." << endl;
                cout << "Do yot want to try again? (Y/N)" << endl;
                cin >> again;
                cin.ignore();
                again = toupper(again);
                if (again != 'Y'){
                    cout << "Back to Menu" << endl;
                    return NULL;
                }
            } while (true);
        }

        void registerMember(){
            cout << "Welcome To Our Restaurant's Membership !" << endl;
            cout << "Please Fill in The Information for Registration" << endl;

            cout << "Please Enter your Name : ";
            getline(cin, name);

            while (true) {
                cout << "Please Enter your Email : ";
                getline(cin, email);
                if (!checkEmail(email)){
                    cout << "Email is not Correct. Please Try Again" << endl;
                    continue;
                }
                break;
            }

            while (true) {
                cout << "Please Enter your Phone Number : ";
                cin >> phone;
                if (!checkPhone(phone)){
                    cout << "Phone number is not Correct. Please Try Again" << endl;
                    continue;
                }
                break;
            }

            while (true){
                cout << "Please Enter your Password : ";
                cin >> password;
                if (!checkPassword(password)) continue;
                break;
            }
            while (true)
            {
                cout << "Please Confirm Password : ";
                cin >> confirmPassword;
                if (password == confirmPassword){
                    cout << "Password confirmed successfully!" << endl;
                    break;
                }
                else {
                    cout << "Password do not Match. Please Try Again" << endl;
                }
            }

            while (true) {
                cout << "Please Enter your Date of Birth (DD/MM/YYYY): ";
                cin >> dateOfBirth;
                if (!checkDate(dateOfBirth)){
                    cout << "Date of Birth is not Correct. Please Try Again" << endl;
                    continue;
                }
                break;
            }
            
            while (true) {
                cout << "Please Enter your Date of Registation (DD/MM/YYYY): ";
                cin >> dateOfRegis;
                if (!checkDate(dateOfRegis)){
                    cout << "Date of Registation is not Correct. Please Try Again" << endl;
                    continue;
                }
                break;
            }
            cout << endl << " Registation Complete!" << endl;
            showInformation();
            char edit;
            do {
                cout << endl << "Do you want to Edit your Information? (Y/N)" << endl;
                cin >> edit;
                cin.ignore();
                edit = toupper(edit);
                if (edit == 'Y'){
                    int choice;
                    do {
                        showInformation();
                        cout << "Please Enter the Number of Information you want to Edit (1-6), or 0 to go back ";
                        cin >> choice;
                        if (choice >= 1 && choice <= 6){
                            editInformation(choice);
                        }
                    } while (choice != 0);
                    break;
                }
                else if (edit == 'N') break;
                else cout << "Please Enter Y or N." << endl;
            } while (true);
        }

        void showInformation(){
            cout << endl << "=== Your Information ===" << endl;
            show_node();
            cout << "1. Name : " << name << endl;
            cout << "2. Email : " << email << endl;
            cout << "3. Phone Number : " << phone << endl;
            cout << "4. Password : " << password << endl;
            cout << "5. Date of Birth : " << dateOfBirth << endl;
            cout << "6. Date of Registation : " << dateOfRegis << endl;
            cout << "7. Point : " << point << endl;
            cout << "8. Member Type : " << memberType << endl;
        }
        
        void editInformation(int choice){
            cin.ignore();
            switch (choice) {
                case 1 :
                    cout << "Please Enter New Name : ";
                    getline(cin, name);
                    break;
                case 2 :
                    while (true) {
                        cout << "Please Enter New Email : ";
                        getline(cin, email);
                        if (!checkEmail(email)){
                            cout << "Email is not Correct. Please Try Again" << endl;
                            continue;
                        }
                        break;
                    }
                    break;
                case 3 : 
                    while (true) {
                        cout << "Please Enter New Phone Number : ";
                        cin >> phone;
                        if (!checkPhone(phone)){
                            cout << "Phone number is not Correct. Please Try Again" << endl;
                            continue;
                        }
                        break;
                    }
                    break;
                case 4 :
                    while (true){
                        cout << "Please Enter New Password : ";
                        cin >> password;
                        if (!checkPassword(password)) continue;
                        break;
                    }
                    while (true)
                    {
                        cout << "Please Confirm Password : ";
                        cin >> confirmPassword;
                        if (password == confirmPassword){
                            cout << "Password confirmed successfully!" << endl;
                            break;
                        }
                        else {
                            cout << "Password do not Match. Please Try Again" << endl;
                        }
                    }
                    break;
                case 5 :
                    while (true) {
                        cout << "Please Enter New Date of Birth (DD/MM/YYYY): ";
                        cin >> dateOfBirth;
                        if (!checkDate(dateOfBirth)){
                            cout << "Date of Birth is not Correct. Please Try Again" << endl;
                            continue;
                        }
                        break;
                    }
                    break;
                case 6 :
                    while (true) {
                        cout << "Please Enter New Date of Registation (DD/MM/YYYY): ";
                        cin >> dateOfRegis;
                        if (!checkDate(dateOfRegis)){
                            cout << "Date of Registation is not Correct. Please Try Again" << endl;
                            continue;
                        }
                        break;
                    }
                    break;
                case 0 :
                    cout << "Back to Menu" << endl;
                    break;
                default :
                    cout << "Please Enter 0-6" << endl;
                }
            }

            void memberFunction(NODE* newMember, NODE* head) {
                int choose;
                do {
                    cout << "=== Function for Membership ===\n";
                    cout << "1. Show All Promotions\n";
                    cout << "2. Show My Membership Information\n";
                    cout << "3. Edit My Information\n";
                    cout << "4. Cancle Membership\n";
                    cout << "0. Back to Menu\n";
                    cout << "Choose an option: ";
                    cin >> choose;
                    cout << endl;
                    cin.ignore();

                    switch(choose) {
                        case 1 :
                            cout << "All Promotions\n";
                            break;
                        case 2 :
                            if (newMember != NULL){
                                static_cast<member*>(newMember)->showInformation();
                            }
                            break;
                        case 3 : {
                            int edit;
                            do {
                                static_cast<member*>(newMember)->showInformation();
                                cout << "Please Enter the Number of Information you want to Edit (1-6), or 0 to go back" << endl;
                                cin >> edit;
                                if (edit >= 1 && edit <= 6){
                                    static_cast<member*>(newMember)->editInformation(edit);
                                } 
                            } while (edit != 0);
                            static_cast<member*>(newMember)->saveEditToFile(newMember);
                        }
                        break;
                        case 4 :
                            cout << "Cancle Membership\n";
                            break;
                        case 0:
                            cout << "👋 Back to Menu\n";    
                            break;
                        default:
                            cout << "⚠️ Invalid option. Try again.\n";
                        }
                } while (choose != 0);
            }
};

#endif