#ifndef BILL_H
#define BILL_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include "timestamp.h"

using namespace std;

struct Item {
    string menu;
    int quantity;
    float price;
    int tableNumber;
    string clientName;
    int orderId;
};

class Bill {
    private:
        vector<Item> bill;
        vector<Item> dailyBills;
    public: 
        void addtoBill(string menu, float price, int tableNum, string clientName, int orderId, int Quantity) {
            Item item;
            for(auto& check : bill) {
                if(check.menu == menu && check.tableNumber == tableNum && check.clientName == clientName) {
                    check.quantity+=Quantity;
                    return;
                }
            }
            item.menu = menu;
            item.quantity = Quantity;
            item.price = price;
            item.tableNumber = tableNum;
            item.clientName = clientName;
            item.orderId = orderId;
            bill.push_back(item);
            dailyBills.push_back(item);
        }

        void remove (int orderId)
        {
            bill.erase(remove_if(bill.begin(), bill.end(), 
            [orderId](const Item& item) { return item.orderId == orderId; }), bill.end());
    
            dailyBills.erase(remove_if(dailyBills.begin(), dailyBills.end(), 
            [orderId](const Item& item) { return item.orderId == orderId; }), dailyBills.end());
        }

        void showBill(int tableNum) {
            float subtotal = 0;
            float gst;
            float total;
            int i=0, count = 0;
            static int billno = 1;

            for(auto& check : bill) {
                if(check.tableNumber == tableNum) count = 1;
            }
            if(count) {
                cout << "--------------------------------------\n";
                cout << "           THE GRILL HOUSE\n";
                cout << "   123 Bantadtong Street, Thailand\n";
                cout << "         Phone: 021 123 5678\n";
                cout << "--------------------------------------\n";
                cout << "Date: "<< getCurrentTimestamp(7) << " PM\n";
                cout << "Bill No: " << right << setw(6) << setfill('0') << billno << "\n\n";
                billno++;
    
                cout << left << setw(18) << setfill(' ') << "Item"
                << setw(6) << "Qty"
                << setw(8) << "Price"
                << setw(8) << "Total" << endl;
       
                cout << "--------------------------------------\n";
                
                for(const auto& check : bill) { 
                    if(check.tableNumber == tableNum){
                        total = check.quantity * check.price;
                        cout << left << setw(18) << check.menu
                        << setw(6) << check.quantity
                        << setw(8) << fixed << setprecision(2) << check.price
                        << setw(8) << total << endl;
                        subtotal+=total;
                    }
                }
    
                cout << "--------------------------------------\n";
       
                gst = subtotal * 0.10;
                total = subtotal + gst;
       
                cout << left << setw(32) << "Subtotal"
                << setw(8) << fixed << setprecision(2) << subtotal << endl;
       
                cout << left << setw(33) << "GST (10%)"
                << setw(8) << gst << endl;
       
                cout << "--------------------------------------\n";
       
                cout << left << setw(32) << "Total Amount"
                << setw(8) << total << endl;
       
                cout << "--------------------------------------\n";
                cout << "Payment Method: Cash\n";
                cout << "Thank you! Please visit again. 😊\n";
                cout << "--------------------------------------\n";
                
                for(auto& check : bill) {
                    if(check.tableNumber == tableNum) {
                        bill.erase(bill.begin()+i);
                    }
                    i++;
                }
    
                bill.shrink_to_fit();
            }
            else {
                cout << "Your receipt have print already\n";
            }
        }
        

        void showAllBills() { //for admin
            Item item;
            if (dailyBills.empty()) {
                cout << "📭 No bills available today.\n";
                return;
            }
            cout << "\n📊 All Bills for Today:\n\n";

            vector<pair<int, string>> shownTables;
            for (auto& check : dailyBills) {
                pair<int, string> NumAndName = make_pair(check.tableNumber, check.clientName);
                if (find(shownTables.begin(), shownTables.end(), NumAndName) != shownTables.end()) {
                    continue; 
                }
                cout << "🧍 Client: " << check.clientName << " | 🪑 Table: " << check.tableNumber << endl;
                cout << left << setw(18) << "Item"
                     << setw(6) << "Qty"
                     << setw(8) << "Price"
                     << setw(8) << "Total" << endl;
                cout << "--------------------------------------\n";
        
                float subtotal = 0;
                for (auto& item : dailyBills) {
                    if (item.tableNumber == check.tableNumber && item.clientName == check.clientName) {
                        float total = item.price * item.quantity;
                        cout << left << setw(18) << item.menu
                             << setw(6) << item.quantity
                             << setw(8) << fixed << setprecision(2) << item.price
                             << setw(8) << total << endl;
                        subtotal += total;
                    }
                }
        
                float gst = subtotal * 0.10;
                float total = subtotal + gst;
                cout << "--------------------------------------\n";
                cout << left << setw(32) << "Subtotal" << setw(8) << fixed << setprecision(2) << subtotal << endl;
                cout << left << setw(33) << "GST (10%)" << setw(8) << gst << endl;
                cout << left << setw(32) << "Total Amount" << setw(8) << total << endl;
                cout << "--------------------------------------\n\n";
                shownTables.push_back(NumAndName);
            }
        }
};

#endif
