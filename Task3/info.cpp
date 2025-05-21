#include <string>
#include <vector>
#include <iostream>
#include <map>
#include "Header.h"
using namespace std;
void display(map<string, Trolleybus>& trolleybuses) {
    setlocale(LC_ALL, "rus");
    if (trolleybuses.empty()) {
        cout << "Нет троллейбусов." << endl;
        return;
    }
    cout << "Троллейбусы:" << endl;
    for (const auto& pair : trolleybuses) {
        cout << "  " << pair.first << ": ";
        for (auto i : pair.second.stops) {
            cout << i << " ";
        }
        cout << endl;
    }
}
