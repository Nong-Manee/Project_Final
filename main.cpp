#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

#include "Queue.h"
#include "admin.h"
#include "client.h"
#include "Table.h"
#include "menu.h"
#include "LL.h"
#include "timestamp.h"

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
    PopularLL popular;
    User* Info;


    while (true) {
        cout << "👋 Welcome to the Restaurant Order Management System!\n";
        Info = new User();
        Info->displayInfo();//polymorphism
        cout << "Admin (1) / Client (2) ? (else = exit): ";
    while (!(cin >> userType)) {
        cin.clear(); // clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
        cout << "⚠️ Invalid input. Please enter a number: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // remove any leftover characters
    system("clear");

        bool isAdmin = false;
        if (userType == 1) { // Admin [Id needs to be 999 to Login]
            while(!isAdmin){
                cout << "Enter Admin Name: ";
                cin >> adminName;
                cout << "Enter Admin ID: ";
                cin >> adminId;
                Info =new Admin(adminName, stoi(adminId));//polymorphism
                isAdmin = Info->adminLogin();
            }
            system("clear");
            do {
                Info->displayInfo();
                cout << "\n=== Restaurant Order Management System [ADMIN] ===\n";
                cout << "1. Complete Order\n";
                cout << "2. Show All Orders\n";
                cout << "3. Search Orders by Food\n";
                cout << "4. Count Total Orders\n";
                cout << "5. Show All Bills\n";
                cout << "0. Back to Login\n";
                cout << "Choose an option: ";
                cin >> choice;
                cin.ignore(); // clear buffer
                system("clear");
                switch (choice) {
                    case 1:
                        queue.completeOrder();
                        pressEnter();
                        break;
                    case 2:
                        queue.showallOrders();
                        pressEnter();
                        break;
                    case 3:
                        showFoodMenu(menu, MENU_SIZE);
                        cout << "Enter food name to search: ";
                        getline(cin, foodName);
                        queue.searchOrder(foodName);
                        pressEnter();
                        break;
                    case 4:
                        queue.countOrders();
                        pressEnter();
                        break;
                    case 5:
                        queue.showAllBills();
                        pressEnter();
                        break;
                    case 0:
                        cout << "👋 Exiting system. Goodbye!\n";
                        break;
                    default:
                        cout << "⚠️ Invalid option. Try again.\n";
                }
                system("clear");
            } while (choice != 0);
        } 
        else if (userType == 2) {
            ReserveTable.updatenotAvailTable();
            cout << "Enter Client Name: ";
            cin >> clientName;
            ReserveTable.showTable();
            cout << "Enter Client Table: ";
            cin >> clientTable;
            Info = new Client(clientName, stoi(clientTable));//polymorphism
            bool tableIsFree = ReserveTable.addTable(Info->getName(), Info->getTableNumber());
            cin.ignore();
            system("clear");
            do {
                if(tableIsFree == false) break;
                Info->displayInfo();
                cout << "\n=== Restaurant Order Management System [Client] ===\n";
                cout << "1. Add Order\n";
                cout << "2. Process Next Order\n";
                cout << "3. Show all your orders\n";
                cout << "4. Cancel Order\n";
                cout << "5. Count Total Orders\n";
                cout << "6. Show Popular Orders\n";
                cout << "7. Check for This meal\n";
                cout << "0. Back to Login\n";
                cout << "Choose an option: ";
                cin >> choice;
                cin.ignore(); // clear buffer
                system("clear");
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
                            cin.ignore();
                            Node* a = new Node(foodName);
                            popular.addNode(a);
                        } 
                        break;
                    case 2:
                        queue.processOrder();
                        pressEnter();
                        break;
                    case 3:
                        queue.showcurrentClientOrders(Info->getTableNumber());
                        pressEnter();
                        break;
                    case 4:
                        queue.showcurrentClientOrders(Info->getTableNumber());
                        cout << "Enter Order ID to cancel: ";
                        cin >> orderId;
                        cin.ignore();
                        queue.cancelOrder(orderId, Info->getTableNumber());
                        pressEnter();
                        break;
                    case 5:
                        queue.countOrders();
                        pressEnter();
                        break;
                    case 6:
                        popular.displayPopular();
                        pressEnter();
                        break;
                    case 7:
                        ReserveTable.clearTable(Info->getName());
                        queue.showBill(Info->getTableNumber());
                        pressEnter();
                        break;
                    case 0:
                        cout << "👋 Exiting system. Goodbye!\n";
                        break;
                    default:
                        cout << "⚠️ Invalid option. Try again.\n";
                        pressEnter();
                }
                system("clear");
            } while (choice != 0 && choice != 7);
        } 
        else {
            cout << "Exiting.\n";
            exit = true;
        }
        if (exit) {
            break;
        }
    }
    return 0;
}

