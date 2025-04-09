#include <iostream>
#include <string>
#include <map>
using namespace std;

struct Order {
    int orderId;
    int tableNumber;
    string foodName;
    Order* next;
};

class OrderQueue {
private:
    Order* front;
    Order* rear;
    int nextId;

public:
    OrderQueue() {
        front = rear = nullptr;
        nextId = 1;
    }

    // Add a new order
    void addOrder(const string& foodName, int tableNum) {
        Order* newOrder = new Order{nextId++, tableNum, foodName, nullptr};
        if (rear == nullptr) {
            front = rear = newOrder;
        } else {
            rear->next = newOrder;
            rear = newOrder;
        }
        cout << "✅ Order #" << newOrder->orderId << " for Table " << tableNum << ": " 
             << foodName << " added to queue.\n";
    }

    // Show the current order being processed (at the front)
    void processOrder() {
        if (front == nullptr) {
            cout << "📭 No orders in queue.\n";
            return;
        }
        cout << "👨‍🍳 Preparing Order #" << front->orderId << " for Table " << front->tableNumber
             << ": " << front->foodName << endl;
    }

    // Complete the current order (remove from front)
    void completeOrder() {
        if (front == nullptr) {
            cout << "📭 No orders to complete.\n";
            return;
        }
        Order* temp = front;
        cout << "✅ Order #" << temp->orderId << " for Table " << temp->tableNumber 
             << ": " << temp->foodName << " has been served.\n";
        front = front->next;
        if (front == nullptr) rear = nullptr;
        delete temp;
    }

    // Show all orders in the queue
    void showOrders() {
        if (front == nullptr) {
            cout << "📭 No orders in queue.\n";
            return;
        }

        Order* temp = front;
        cout << "📋 Current Orders in Queue:\n";
        while (temp != nullptr) {
            cout << " - Order #" << temp->orderId << ": " << temp->foodName 
                 << " | Table " << temp->tableNumber << endl;
            temp = temp->next;
        }
    }

    // Cancel an order by ID
    void cancelOrder(int id) {
        if (front == nullptr) {
            cout << "📭 No orders to cancel.\n";
            return;
        }

        Order* current = front;
        Order* prev = nullptr;

        while (current != nullptr && current->orderId != id) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "❌ Order #" << id << " not found.\n";
            return;
        }

        if (current == front) {
            front = front->next;
            if (front == nullptr) rear = nullptr;
        } else {
            prev->next = current->next;
            if (current == rear) rear = prev;
        }

        cout << "🚫 Order #" << current->orderId << " for Table " << current->tableNumber 
             << " canceled.\n";
        delete current;
    }

    // Search orders by food name
    void searchOrder(const string& name) {
        Order* temp = front;
        bool found = false;
        cout << "🔍 Searching for orders with food: " << name << "\n";
        while (temp != nullptr) {
            if (temp->foodName == name) {
                cout << " - Order #" << temp->orderId << " | Table " 
                     << temp->tableNumber << endl;
                found = true;
            }
            temp = temp->next;
        }
        if (!found) {
            cout << "❌ No orders with that food found.\n";
        }
    }

    // Count total orders
    void countOrders() {
        int count = 0;
        Order* temp = front;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        cout << "📦 Total orders in queue: " << count << endl;
    }

    // Show most ordered (popular) items
    void showPopularOrders() {
        map<string, int> foodCount;
        Order* temp = front;
        while (temp != nullptr) {
            foodCount[temp->foodName]++;
            temp = temp->next;
        }

        cout << "🔥 Most popular items:\n";
        bool found = false;
        for (auto& entry : foodCount) {
            if (entry.second > 1) {
                cout << " - " << entry.first << ": " << entry.second << " times\n";
                found = true;
            }
        }
        if (!found) {
            cout << "📉 No duplicate items found yet.\n";
        }
    }

    // Free memory
    ~OrderQueue() {
        while (front != nullptr) {
            Order* temp = front;
            front = front->next;
            delete temp;
        }
    }
};