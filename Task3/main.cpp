#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include "Header.h"
using namespace std;
enum class Type {
    CREATE_TRL,
    TRL_IN_STOP,
    STOPS_IN_TRL,
    TRLS,
    EXIT,
    UNKNOWN
};
map<string, Trolleybus> trolleybuses;
Type getCommandType(const string& commandString) {
    if (commandString == "CREATE_TRL") {
        return Type::CREATE_TRL;
    }
    else if (commandString == "TRL_IN_STOP") {
        return Type::TRL_IN_STOP;
    }
    else if (commandString == "STOPS_IN_TRL") {
        return Type::STOPS_IN_TRL;
    }
    else if (commandString == "TRLS") {
        return Type::TRLS;
    }
    else if (commandString == "EXIT") {
        return Type::EXIT;
    }
    else {
        return Type::UNKNOWN;
    }
}
int main()
{
    setlocale(LC_ALL, "Russian"); 
    string command;
    while (true)
    {
        getline(cin, command);
        stringstream ss(command);
        string word;
        ss >> word;
        Type commandType = getCommandType(word);
        switch (commandType) {
        case Type::CREATE_TRL: {
            string name;
            ss >> name;
            vector<string> stops;
            string stop;
            while (ss >> stop) {
                stops.push_back(stop);
            }
            create(name, stops, trolleybuses);
            break;
        }
        case Type::TRLS:
            display(trolleybuses);
            break;
        case Type::TRL_IN_STOP: {
            string stop;
            ss >> stop;
            find(stop, trolleybuses);
            break;
        }
        case Type::STOPS_IN_TRL: {
            string name;
            ss >> name;
            stops(name, trolleybuses);
            break;
        }
        case Type::EXIT:
            return 0;
        case Type::UNKNOWN:
            cout << "Неизвестная команда." << endl;
            break; 
        }
    }
    return 0; 
}
