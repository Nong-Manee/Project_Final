// menu.h
#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <iomanip>
#include "menu.h"

using namespace std;

const int MENU_SIZE = 5;
const int MAX_ORDER = 10;

struct MenuItem {
    int id;
    char name[50];
    double price;
};

void showFoodMenu(const MenuItem menu[], int size) {
    cout << "=========== Food Menu ===========\n";
    cout << left << setw(5) << "ID" << setw(25) << "Name" << setw(10) << "Price" << endl;
    cout << "----------------------------------\n";

    for (int i = 0; i < size; ++i) {
        cout << left << setw(5) << menu[i].id
             << setw(25) << menu[i].name
             << fixed << setprecision(2) << menu[i].price << " Baht" << endl;
    }

    cout << "==================================\n";
}

/*void takeOrder(const MenuItem menu[], int menuSize, int orderIDs[], int orderQtys[], int &orderCount) {
    orderCount = 0;
    int id, qty;

    while (true) {
        cout << "\nEnter food ID to order (0 to finish): ";
        cin >> id;

        if (id == 0) break;

        bool found = false;
        for (int i = 0; i < menuSize; ++i) {
            if (menu[i].id == id) {
                found = true;
                cout << "Enter quantity: ";
                cin >> qty;

                if (orderCount < MAX_ORDER) {
                    orderIDs[orderCount] = id;
                    orderQtys[orderCount] = qty;
                    orderCount++;
                } else {
                    cout << "Order list is full.\n";
                }

                break;
            }
        }

        if (!found) {
            cout << "Invalid ID. Please try again.\n";
        }
    }
}*/

void takeOrder(const MenuItem menu[], int menuSize, int orderIDs[], int orderQtys[], int &orderCount) {
    orderCount = 0;
    int id, qty;

    cout << "\nEnter food ID to order: ";
    cin >> id;

    bool found = false;
    for (int i = 0; i < menuSize; ++i) {
        if (menu[i].id == id) {
            found = true;
            //cout << "Enter quantity: ";
            //cin >> qty;

            orderIDs[0] = id;
            //orderQtys[0] = qty;
            orderCount = 1;
            break;
        }
    }

    if (!found) {
        cout << "Invalid ID. No order taken.\n";
    }
}


#endif
