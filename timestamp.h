#ifndef timestamp_h
#define timestamp_h

#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

string getCurrentTimestamp(int offsetHours) {
    using namespace chrono;

    auto now = system_clock::now() + hours(offsetHours);  // Adjust manually
    time_t now_c = system_clock::to_time_t(now);

    char buf[100];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", gmtime(&now_c)); // use gmtime
    return string(buf);
}

void pressEnter() {
    cout << "Press Enter to continue...";
    cin.get(); 
}

#endif
