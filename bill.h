#ifndef BILL_H
#define BILL_H

#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

struct Item {
    string menu;
    int quantity;
    float price;
    int tableNumber;
};

class Bill {
    private:
        vector<Item> bill;
    public: 
        void addtoBill(string menu, float price, int tableNum) {
            Item item;
            for(auto& check : bill) {
                if(check.menu == menu && check.tableNumber == tableNum) {
                    check.quantity++;
                    return;
                }
            }
            item.menu = menu;
            item.quantity = 1;
            item.price = price;
            item.tableNumber = tableNum;
            bill.push_back(item);
        }

        void showBill(int tableNum) {
            float subtotal = 0;
            float gst;
            float total;
            int i=0, count = 0;

            for(auto& check : bill) {
                if(check.tableNumber == tableNum) count = 1;
            }
            if(count) {
                cout << "--------------------------------------\n";
                cout << "           THE GRILL HOUSE\n";
                cout << "       123 Food Street, Sydney\n";
                cout << "        Phone: (02) 1234 5678\n";
                cout << "--------------------------------------\n";
                cout << "Date: 11-Apr-2025     Time: 12:34 PM\n";
                cout << "Bill No: 001235\n\n";
    
                cout << left << setw(18) << "Item"
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
};

#endif