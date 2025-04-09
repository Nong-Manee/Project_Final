#include <iostream>
#include <string>
#include <map>
using namespace std;

#include "user.h"


class Client : public User {
    private:
        string name;
        int tableNumber;

    public:
        Client(string name, int tableNumber) {
            this->name = name;
            this->tableNumber = tableNumber;
            cout << "Welcome, " << name << "! Your table number is " << tableNumber << ".\n";
        }
        
        void displayInfo() {
            cout << "Client Name: " << name << "Table number: " << tableNumber << endl;
        }

        int getTableNumber() {
            return tableNumber;
        }

};