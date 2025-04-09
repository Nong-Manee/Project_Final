#include <iostream>
using namespace std;

struct Order {
    int orderId;
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

    // เพิ่มออเดอร์เข้าไปในคิว
    void addOrder(const string& foodName) {
        Order* newOrder = new Order{nextId++, foodName, nullptr};
        if (rear == nullptr) {
            front = rear = newOrder;
        } else {
            rear->next = newOrder;
            rear = newOrder;
        }
        cout << "✅ เพิ่มออเดอร์ #" << newOrder->orderId << ": " << foodName << " เข้าคิวแล้ว\n";
    }

    // แสดงออเดอร์ที่กำลังดำเนินการ (หน้า queue)
    void processOrder() {
        if (front == nullptr) {
            cout << "📭 ไม่มีออเดอร์ในคิว\n";
            return;
        }
        cout << "👨‍🍳 ดำเนินการออเดอร์ #" << front->orderId << ": " << front->foodName << endl;
    }

    // ลบออเดอร์หน้า queue เมื่ออาหารเสร็จแล้ว
    void completeOrder() {
        if (front == nullptr) {
            cout << "📭 ไม่มีออเดอร์ในคิว\n";
            return;
        }
        Order* temp = front;
        cout << "✅ ออเดอร์ #" << temp->orderId << ": " << temp->foodName << " เสิร์ฟแล้ว\n";
        front = front->next;
        if (front == nullptr) rear = nullptr;
        delete temp;
    }

    // แสดงรายการออเดอร์ทั้งหมด
    void showOrders() {
        if (front == nullptr) {
            cout << "📭 ไม่มีออเดอร์ในคิว\n";
            return;
        }

        Order* temp = front;
        cout << "📋 รายการออเดอร์ในคิว:\n";
        while (temp != nullptr) {
            cout << " - #" << temp->orderId << ": " << temp->foodName << endl;
            temp = temp->next;
        }
    }

    // ยกเลิกออเดอร์ตามหมายเลข
    void cancelOrder(int id) {
        if (front == nullptr) {
            cout << "📭 ไม่มีออเดอร์ในคิว\n";
            return;
        }

        Order* current = front;
        Order* prev = nullptr;

        while (current != nullptr && current->orderId != id) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "❌ ไม่พบออเดอร์หมายเลข #" << id << "\n";
            return;
        }

        if (current == front) {
            front = front->next;
            if (front == nullptr) rear = nullptr;
        } else {
            prev->next = current->next;
            if (current == rear) rear = prev;
        }

        cout << "🚫 ยกเลิกออเดอร์ #" << current->orderId << ": " << current->foodName << " สำเร็จ\n";
        delete current;
    }

    ~OrderQueue() {
        while (front != nullptr) {
            Order* temp = front;
            front = front->next;
            delete temp;
        }
    }
};