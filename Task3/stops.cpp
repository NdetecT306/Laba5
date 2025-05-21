#include <string>
#include <vector>
#include <iostream>
#include <map>
#include "Header.h"
using namespace std;
void stops(const string& trolleybus_name, map<string, Trolleybus>& trolleybuses) {
  setlocale(LC_ALL, "rus");  
  auto it = trolleybuses.find(trolleybus_name);
    if (it == trolleybuses.end()) {
        cout << "Нет такого троллейбуса. " <<  endl;
        return;
    }
    const Trolleybus& target_trolleybus = it->second;
    for (const string& stop : target_trolleybus.stops) {
        cout << "Выводим троллейбусы для остановки " << stop << " :" << endl;
        bool first = true;
        for (const auto& pair : trolleybuses) {
            const Trolleybus& other_trolleybus = pair.second;
            if (other_trolleybus.name != trolleybus_name) {
                if (find(other_trolleybus.stops.begin(), other_trolleybus.stops.end(), stop) != other_trolleybus.stops.end()) {
                    if (!first) {
                        cout << " ";
                    }
                    cout << other_trolleybus.name;
                    first = false;
                }
            }
        }
        if (first) {
            cout << "Нет таких.";
        }
        cout << endl;
    }
}
