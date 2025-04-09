#include <iostream>
#include <string>
#include "Queue.h"
using namespace std;


// Main program
int main() {
    OrderQueue queue;
    int choice;
    string foodName;
    int tableNum, orderId;

    do {
        cout << "\n=== Restaurant Order Management System ===\n";
        cout << "1. Add Order\n";
        cout << "2. Process Next Order\n";
        cout << "3. Complete Order\n";
        cout << "4. Show All Orders\n";
        cout << "5. Cancel Order\n";
        cout << "6. Search Orders by Food\n";
        cout << "7. Count Total Orders\n";
        cout << "8. Show Popular Orders\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore(); // clear buffer

        switch (choice) {
            case 1:
                cout << "Enter food name: ";
                getline(cin, foodName);
                cout << "Enter table number: ";
                cin >> tableNum;
                cin.ignore();
                queue.addOrder(foodName, tableNum);
                break;
            case 2:
                queue.processOrder();
                break;
            case 3:
                queue.completeOrder();
                break;
            case 4:
                queue.showOrders();
                break;
            case 5:
                cout << "Enter Order ID to cancel: ";
                cin >> orderId;
                cin.ignore();
                queue.cancelOrder(orderId);
                break;
            case 6:
                cout << "Enter food name to search: ";
                getline(cin, foodName);
                queue.searchOrder(foodName);
                break;
            case 7:
                queue.countOrders();
                break;
            case 8:
                queue.showPopularOrders();
                break;
            case 0:
                cout << "👋 Exiting system. Goodbye!\n";
                break;
            default:
                cout << "⚠️ Invalid option. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
