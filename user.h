#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include "menu.h"
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

        virtual void displayInfo(){
            showFoodMenu(menu,MENU_SIZE);
        }

        virtual bool adminLogin(){
            return false;
        }

        virtual int getTableNumber() {
            return 1;
        }

        virtual string getName() {
            return name;
        }

        virtual ~User() {
            cout << "Thankyou!\n";
        }
};

#endif // USER_H