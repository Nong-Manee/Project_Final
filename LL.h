#include <iostream>
#include <string>
using namespace std;

#ifndef LL_H
#define LL_H

class Node {
     public:
          Node* next;
          int quantity;
          string foodname;

          Node(string f) : quantity(1), foodname(f), next(nullptr) {}
};

class PopularLL {
     private:
         Node* hol;
     public:
          PopularLL() : hol(nullptr) {}
          void addNode(Node*&);
          void sortingPopular();
          void displayPopular();
};

void PopularLL::addNode(Node*& a) {
     if (hol == nullptr) {
         hol = a;
         return;
     }
 
     Node* t = hol;
     while (t != nullptr) {
         if (t->foodname == a->foodname) {
             t->quantity++;
             delete a;
             return;
         }
         if (t->next == nullptr) break;
         t = t->next;
     }
 
     // No duplicate found, append new node
     t->next = a;
 }
 

void PopularLL::sortingPopular() {
     if (!hol || !hol->next) return;

     bool swapped;
     Node **ptr;
 
     do {
         swapped = false;
         ptr = &hol;
 
         while ((*ptr)->next != nullptr) {
             Node* a = *ptr;
             Node* b = a->next;
 
             if (a->quantity < b->quantity) {  // descending order
                 // Swap nodes by changing links
                 a->next = b->next;
                 b->next = a;
                 *ptr = b;
                 swapped = true;
             }
 
             ptr = &((*ptr)->next);  // move to next pointer-to-pointer
         }
     } while (swapped);
}

void PopularLL::displayPopular() {
     if(hol==nullptr) {
          cout << "📉 No duplicate items found yet.\n";
          return;
     }
     sortingPopular();
     cout << "🔥 Most popular items:\n";
     Node* t = hol;
     while(t->next != nullptr) {
          cout << " - " << t->foodname << ": " << t->quantity << " times\n";
          t = t->next;
     }
     cout << " - " << t->foodname << ": " << t->quantity << " times\n";
}

#endif 
