#include <iostream>
#include <string>
using namespace std;

#include "Queue.h"
#include "admin.h"
#include "client.h"
#include "Table.h"
#include "menu.h"

// Main program
int main() {
    OrderQueue queue;
    int choice = 99, userType;
    string foodName, adminName, adminId, clientName, clientTable;
    int tableNum, orderId, Price, Quantity;
    bool exit = false;
    Table ReserveTable;
    int orderIDs[MAX_ORDER];
    int orderQtys[MAX_ORDER];
    int orderCount = 0;
    int i, j;   
    User* Info;


    while (true) {
        cout << "👋 Welcome to the Restaurant Order Management System!\n";
        Info = new User();
        Info->displayInfo();//polymorphism
        cout << "Admin (1) / Client (2) ? (else (exit)): ";
        cin >> userType;

        bool isAdmin = false;
        if (userType == 1) { // Admin [Id needs to be 999 to Login]
            while(!isAdmin){
                cout << "Enter Admin Name: ";
                cin >> adminName;
                cout << "Enter Admin ID: ";
                cin >> adminId;
                Info =new Admin(adminName, stoi(adminId));//polymorphism
                Info->displayInfo();
                isAdmin = Info->adminLogin();
            }

            do {
                cout << "\n=== Restaurant Order Management System [ADMIN] ===\n";
                cout << "1. Complete Order\n";
                cout << "2. Show All Orders\n";
                cout << "3. Search Orders by Food\n";
                cout << "4. Count Total Orders\n";
                cout << "5. Show Popular Orders\n";
                cout << "6. Show All Bills\n";
                cout << "0. Back to Login\n";
                cout << "Choose an option: ";
                cin >> choice;
                cin.ignore(); // clear buffer
        
                switch (choice) {
                    case 1:
                        queue.completeOrder();
                        break;
                    case 2:
                        queue.showallOrders();
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
                    case 6:
                        queue.showAllBills();
                        break;
                    case 0:
                        cout << "👋 Exiting system. Goodbye!\n";
                        break;
                    default:
                        cout << "⚠️ Invalid option. Try again.\n";
                }
        
            } while (choice != 0);
            
        } else if (userType == 2) {
            ReserveTable.updatenotAvailTable();
            cout << "Enter Client Name: ";
            cin >> clientName;
            ReserveTable.showTable();
            cout << "Enter Client Table: ";
            cin >> clientTable;
            Info = new Client(clientName, stoi(clientTable));//polymorphism
            bool tableIsFree = ReserveTable.addTable(Info->getName(), Info->getTableNumber());
            Info->displayInfo();

            do {
                if(tableIsFree == false) break;
                cout << "Welcome, " << Info->getName() << "! Your table number is " << Info->getTableNumber() << ".\n";
                cout << "\n=== Restaurant Order Management System [Client] ===\n";
                cout << "1. Add Order\n";
                cout << "2. Process Next Order\n";
                cout << "3. Show All Orders\n";
                cout << "4. Cancel Order\n";
                cout << "5. Search Orders by Food\n";
                cout << "6. Count Total Orders\n";
                cout << "7. Show Popular Orders\n";
                cout << "8. Check for This meal\n";
                cout << "0. Back to Login\n";
                cout << "Choose an option: ";
                cin >> choice;
                cin.ignore(); // clear buffer

                bool found;
                switch (choice) {
                    case 1:
                    showFoodMenu(menu, MENU_SIZE);
                    found = takeOrder(menu, MENU_SIZE, orderIDs, orderCount);
                    for (i = 0; i < orderCount; ++i) {
                        // Find the name of the food by ID
                        foodName = "";
                        for (j = 0; j < MENU_SIZE; ++j) {
                            if (menu[j].id == orderIDs[i]) {
                                foodName = menu[j].name;
                                Price = menu[j].price;
                                break;
                            }
                        }
                    }
                    if(found){
                        orderId = queue.addOrder(foodName, Info->getTableNumber());
                        queue.addtoBill(foodName, Info->getTableNumber(), Info->getName(), orderId, Price);
                    } 
                    break;
                    case 2:
                        queue.processOrder();
                        break;
                    case 3:
                        queue.showcurrentClientOrders(Info->getTableNumber());
                        break;
                    case 4:
                        cout << "Enter Order ID to cancel: ";
                        cin >> orderId;
                        cin.ignore();
                        queue.cancelOrder(orderId, Info->getTableNumber());
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
                    case 8:
                        ReserveTable.clearTable(Info->getName());
                        queue.showBill(Info->getTableNumber());
                        break;
                    case 0:
                        cout << "👋 Exiting system. Goodbye!\n";
                        break;
                    default:
                        cout << "⚠️ Invalid option. Try again.\n";
                }
            } while (choice != 0 && choice != 8);
        } else {
            cout << "Exiting.\n";
            exit = true;
        }
        if (exit) {
            break;
        }
    }
    return 0;
}

