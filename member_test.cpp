#include <iostream>
#include <string>
using namespace std;
#include "LL.h"
#include "member.h"

int main()
{
    LL membership;
    NODE* head = NULL;
    NODE* newMember = NULL; 
    int choice;
    do {
        cout << "\n=== Welcome to Membership System ===\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Go to Function for Membership\n";
        cout << "0. Exit from Membership System\n";
        cout << "Choose an option: ";
        cin >> choice;
        cout << endl;
        cin.ignore(); // clear buffer

        switch (choice) {
            case 1:
                newMember = member::login(head);
                if (newMember != NULL){ 
                    static_cast<member*>(newMember)->memberFunction(newMember, head);
                }
                break;
            case 2:
                newMember = new member();
                static_cast<member*>(newMember)->registerMember(); 
                if (head == NULL) {
                    head = newMember;
                } 
                else {
                    head->insert(newMember);
                }
                membership.add_node(newMember);
                static_cast<member*>(newMember)->saveToFile();
                static_cast<member*>(newMember)->memberFunction(newMember, head);
                break;
            case 3:
                if (newMember != NULL){
                    static_cast<member*>(newMember)->memberFunction(newMember, head);
                }
                else {
                    cout << "Please Login or Register First." << endl;
                }
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


