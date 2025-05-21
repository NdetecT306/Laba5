#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "Header.h"
using namespace std;
void find(const string& stop, map<string, Trolleybus>& trolleybuses) {
    setlocale(LC_ALL, "rus");
    bool found = false;
    for (const auto& pair : trolleybuses) {
        const Trolleybus& trolleybus = pair.second;
        for (const string& stop : trolleybus.stops) {
            if (stop == stop) {
                cout << trolleybus.name << endl;
                found = true;
                break;
            }
        }
    }
    if (!found) {
        cout << "Нет троллейбусов с остановкой " << stop << endl;
    }
}
