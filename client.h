#ifndef CLIENT_H
#define CLIENT_H

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
        }
        
        void displayInfo() {
            cout << "Client Name: " << name << ", Table number: " << tableNumber << endl;
        }

        int getTableNumber() {
            return tableNumber;
        }

        string getName() {
            return name;
        }

};

#endif