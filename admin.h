#include <iostream>
#include <string>
#include <map>
using namespace std;

#include "user.h"

class Admin : public User {
    public:
        Admin(string name, int id){
            this->name = name;
            this->id = id;
        }

        bool adminLogin() {
            if (id == 999) {
                cout << "Admin login successful!\n";
                cout << "Welcome, " << name << "!\n";
                return true;
            } else {
                cout << "❌ Invalid admin ID.\n";
                return false;
            }
            return false;
        }
        
        void displayInfo() {
            cout << "Admin Name: " << name << ", ID: " << id << endl;
        }
};