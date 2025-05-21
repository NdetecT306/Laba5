#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <set>
#include "Header.h"
using namespace std;
void create(const string& name, const vector<string>& stops, map<string, Trolleybus>& trolleybuses) {
    if (trolleybuses.find(name) != trolleybuses.end())
    {
        cout << "Троллейбус " << name << " уже существует." << endl;
        return;
    }
    if (stops.size() <= 1) {
        cout << "Троллейбус должен иметь больше 1 остановки." << endl;
        return;
    }
    set<string> uniqueStop;
    for (const string& stop : stops) {
        if (uniqueStop.count(stop) > 0) {
            cout << "Остановки не могут повторяться." << endl;
            return;
        }
        uniqueStop.insert(stop);
    }
    Trolleybus newTrl;
    newTrl.name = name;
    newTrl.stops = stops;
    trolleybuses[name] = newTrl;
    cout << "Троллейбус " << name << " создан." << endl;
}
