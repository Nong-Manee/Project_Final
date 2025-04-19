// menu.h
#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <iomanip>

using namespace std;

const int MENU_SIZE = 5;
const int MAX_ORDER = 10;

struct MenuItem {
    int id;
    char name[50];
    double price;
};

MenuItem menu[MENU_SIZE] = {
    {1, "Pad Thai", 50.0},
    {2, "Tom Yum Kung", 80.0},
    {3, "Green Curry Chicken", 70.0},
    {4, "Fried Rice", 45.0},
    {5, "Mango Sticky Rice", 60.0}
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

bool takeOrder(const MenuItem menu[], int menuSize, int orderIDs[], int &orderCount) {
    orderCount = 0;
    int id;

    cout << "\nEnter food ID to order: ";
    cin >> id;

    bool found = false;
    for (int i = 0; i < menuSize; ++i) {
        if (menu[i].id == id) {
            found = true;

            orderIDs[0] = id;
            orderCount = 1;
            break;
        }
    }

    if (!found) {
        cout << "Invalid ID. No order taken.\n";
    }
    return found;
}

#endif
