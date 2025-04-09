#include <iostream>
#include <string>
using namespace std;

#include "Queue.h"
#include "admin.h"
#include "client.h"

// Main program
int main() {
    OrderQueue queue;
    int choice = 99, userType;
    string foodName, adminName, adminId, clientName, clientTable;
    int tableNum, orderId;
    bool exit = false;

    while (true) {
        cout << "👋 Welcome to the Restaurant Order Management System!\n";
        cout << "Admin (1) / Client (2) ? (else (exit)): ";
        cin >> userType;

        bool isAdmin = false;
        if (userType == 1) { // Admin [Id needs to be 999 to Login]
            while(!isAdmin){
                cout << "Enter Admin Name: ";
                cin >> adminName;
                cout << "Enter Admin ID: ";
                cin >> adminId;
                Admin admin(adminName, stoi(adminId));
                isAdmin = admin.adminLogin();
            }

            do {
                cout << "\n=== Restaurant Order Management System [ADMIN] ===\n";
                cout << "1. Complete Order\n";
                cout << "2. Show All Orders\n";
                cout << "3. Search Orders by Food\n";
                cout << "4. Count Total Orders\n";
                cout << "5. Show Popular Orders\n";
                cout << "0. Back to Login\n";
                cout << "Choose an option: ";
                cin >> choice;
                cin.ignore(); // clear buffer
        
                switch (choice) {
                    case 1:
                        queue.completeOrder();
                        break;
                    case 2:
                        queue.showOrders();
                        break;
                    case 3:
                        cout << "Enter food name to search: ";
                        getline(cin, foodName);
                        queue.searchOrder(foodName);
                        break;
                    case 4:
                        queue.countOrders();
                        break;
                    case 5:
                        queue.showPopularOrders();
                        break;
                    case 0:
                        cout << "👋 Exiting system. Goodbye!\n";
                        break;
                    default:
                        cout << "⚠️ Invalid option. Try again.\n";
                }
        
            } while (choice != 0);
            
        } else if (userType == 2) {
            cout << "Enter Client Name: ";
            cin >> clientName;
            cout << "Enter Client Table: ";
            cin >> clientTable;
            Client client(clientName, stoi(clientTable));

            do {
                cout << "\n=== Restaurant Order Management System [Client] ===\n";
                cout << "1. Add Order\n";
                cout << "2. Process Next Order\n";
                cout << "3. Show All Orders\n";
                cout << "4. Cancel Order\n";
                cout << "5. Search Orders by Food\n";
                cout << "6. Count Total Orders\n";
                cout << "7. Show Popular Orders\n";
                cout << "0. Back to Login\n";
                cout << "Choose an option: ";
                cin >> choice;
                cin.ignore(); // clear buffer
        
                switch (choice) {
                    case 1:
                        cout << "Enter food name: ";
                        getline(cin, foodName);
                        queue.addOrder(foodName, client.getTableNumber());
                        break;
                    case 2:
                        queue.processOrder();
                        break;
                    case 3:
                        queue.showOrders();
                        break;
                    case 4:
                        cout << "Enter Order ID to cancel: ";
                        cin >> orderId;
                        cin.ignore();
                        queue.cancelOrder(orderId);
                        break;
                    case 5:
                        cout << "Enter food name to search: ";
                        getline(cin, foodName);
                        queue.searchOrder(foodName);
                        break;
                    case 6:
                        queue.countOrders();
                        break;
                    case 7:
                        queue.showPopularOrders();
                        break;
                    case 0:
                        cout << "👋 Exiting system. Goodbye!\n";
                        break;
                    default:
                        cout << "⚠️ Invalid option. Try again.\n";
                }
            } while (choice != 0);
        } else {
            cout << "❌ Invalid user type. Exiting.\n";
            exit = true;
        }
        if (exit) {
            break;
        }
    }
    return 0;
}
