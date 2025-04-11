#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <map>
using namespace std;

class Table {
    private:
        vector<int> notAvailTable;
        map<string, int> table;
        const int Max_Table = 6;
    public: 
        // Table(string name="testTEST", int tableNumber=0) {
        //     table[name] = tableNumber;
        // }

        bool addTable(string name, int tableNumber) {
            if(table.count(name) == 1 && table[name] == tableNumber)
                return true;
            for (auto entry : table) {
                if(tableNumber==entry.second) {
                    cout << "This table has been reserved already. Please try again! ❌" << endl;
                    return false;
                }
            }
            if(tableNumber>=7 || tableNumber<=0) {
                cout << "Our restaurant has only 6 tables ❌" << endl;
                return false;
            }
            if(table.find(name) != table.end()) {
                cout << "You can Reserved only 1 Table" << endl;
                return false;
            }
            table[name] = tableNumber;
            return true;
        }

        void clearTable(string Name) {
            table.erase(Name);
        }

        void updatenotAvailTable() {
            notAvailTable.clear();
            if(table.size() != 0) {
                for (auto& entry : table) {
                    notAvailTable.push_back(entry.second);
                }
            }
        }

        void showTable() {
            int i, j;
            int count;

            if(notAvailTable.size() >= Max_Table) {
                cout << "Unavailable for all tables. Please wait for queue... 🚫" << endl;
            }
            else if (notAvailTable.size() == 0) {
                cout << "Available Tables for Booking 🍽️ ✅: ";
                for(i = 1; i < 7; i++) {
                    cout << i << " ";
                }
                cout << endl;
            }
            else {
                cout << "Available Tables for Booking 🍽️ ✅: ";
                for(i = 1; i < Max_Table+1; i++) {
                    count = 0;
                    for(j = 0; j < notAvailTable.size(); j++) {
                        if(notAvailTable[j]==i) {
                            count = 1;
                            break;
                        }
                    }
                    if(count==0) {
                        cout << i << " ";
                    }
                }

                cout << endl << "Unavailable Tables 🚫: ";
                for(i=0; i < notAvailTable.size(); i++) {
                    if(notAvailTable[i] != 0)
                        cout << notAvailTable[i] << " "; 
                }
                cout << endl;
            }
        }
};

#endif