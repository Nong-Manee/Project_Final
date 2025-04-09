#include <iostream>
#include <string>
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

// ตัวอย่างการใช้งาน
int main() {
    OrderQueue queue;
    int choice;
    string foodName;
    int orderId;

    do {
        cout << "\n=== ระบบจัดการออเดอร์ร้านอาหาร ===\n";
        cout << "1. เพิ่มออเดอร์\n";
        cout << "2. ดำเนินการออเดอร์\n";
        cout << "3. ออเดอร์เสร็จสิ้น\n";
        cout << "4. แสดงรายการออเดอร์\n";
        cout << "5. ยกเลิกออเดอร์\n";
        cout << "0. ออกจากระบบ\n";
        cout << "เลือกเมนู: ";
        cin >> choice;
        cin.ignore(); // สำหรับล้าง buffer

        switch (choice) {
            case 1:
                cout << "กรอกชื่ออาหาร: ";
                getline(cin, foodName);
                queue.addOrder(foodName);
                break;
            case 2:
                queue.processOrder();
                break;
            case 3:
                queue.completeOrder();
                break;
            case 4:
                queue.showOrders();
                break;
            case 5:
                cout << "กรอกหมายเลขออเดอร์ที่ต้องการยกเลิก: ";
                cin >> orderId;
                queue.cancelOrder(orderId);
                break;
            case 0:
                cout << "👋 ออกจากระบบแล้ว\n";
                break;
            default:
                cout << "⚠️ เมนูไม่ถูกต้อง\n";
        }

    } while (choice != 0);

    return 0;
}
