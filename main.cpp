#include <iostream>
#include <string>
#include "Queue.h"
using namespace std;


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
