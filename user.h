#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
using namespace std;

class User {
    protected:
        string name;
        int id;
    
    public:
        User(string name = "bob", int id = 0) {
            this->name = name;
            this->id = id;
        }
    
        virtual void showMenu() const {
            cout << "Generic user menu\n";
        }
    
        ~User() {
            cout << "Thankyou!\n";
        }
};

#endif // USER_H