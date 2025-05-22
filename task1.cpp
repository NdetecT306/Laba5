#include <iostream>
#include <map>
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>
const int ZONES = 3;
const int RACKS = 14;
const int SECTIONS = 6;
const int SHELVES = 20;
const int CAPACITY = 10;
const int TOTAL_CELLS = ZONES * RACKS * SECTIONS * SHELVES;
const int TOTAL_CAPACITY = TOTAL_CELLS * CAPACITY;
using namespace std;
struct CellAddress 
{
    char zone;
    int rack;
    int section;
    int shelf;
    bool operator<(const CellAddress& other) const
    {
        if (zone != other.zone) return zone < other.zone;
        if (rack != other.rack) return rack < other.rack;
        if (section != other.section) return section < other.section;
        return shelf < other.shelf;
    }
};
bool Address(const CellAddress& address)
{
    if (address.zone < 'A' || address.zone > 'C') return false;
    if (address.rack < 1 || address.rack > RACKS) return false;
    if (address.section < 1 || address.section > SECTIONS) return false;
    if (address.shelf < 1 || address.shelf > SHELVES) return false;
    return true;
}
map<CellAddress, map<string, int>> cells; 
int totalItems = 0;
map<char, int> itemsZone;
int Items(const CellAddress& address)
{
    int count = 0;
    if (cells.count(address)) {
        for (const auto& item : cells.at(address))
        {
            count += item.second;
        }
    }
    return count;
}
bool ADD(const string& item, int colvo, const CellAddress& address) {
    if (!Address(address)) {
        cout << "Неверный адрес ячейки." << endl;
        return false;
    }
    int endColvo = Items(address);
    if (endColvo + colvo > CAPACITY) {
        cout << "Ячейка уже заполнена." << endl;
        return false;
    }
    cells[address][item] += colvo;
    totalItems += colvo;
    itemsZone[address.zone] += colvo;
    cout << "Товар был добавлен" << endl;
    return true;
}
bool REMOVE(const string& item, int colvo, const CellAddress& address)
{
    if (!Address(address))
    {
        cout << "Неверный адрес ячейки" << endl;
        return false;
    }
    if (!cells.count(address) || !cells[address].count(item) || cells[address][item] < colvo)
    {
        cout << "В этой ячейке нет столько товара." << endl;
        return false;
    }
    cells[address][item] -= colvo;
    totalItems -= colvo;
    itemsZone[address.zone] -= colvo;
    if (cells[address][item] == 0)
    {
        cells[address].erase(item);
        if (cells[address].empty())
        {
            cells.erase(address);
        }
    }
    cout << "Товар был удален" << endl;
    return true;
}
void INFO()
{
    double fillPercentage = (static_cast<double>(totalItems) / TOTAL_CAPACITY) * 100;
    cout << "Склад заполнен на: " << fixed << setprecision(2) << fillPercentage << "%" << endl;
    for (char zone = 'A'; zone <= 'C'; ++zone)
    {
        double zoneFillPercentage = (static_cast<double>(itemsZone.count(zone) ? itemsZone[zone] : 0) / (static_cast<double>(TOTAL_CAPACITY) / ZONES)) * 100;
        cout << "Зона " << zone << " заполнена на: " << fixed << setprecision(2) << zoneFillPercentage << "%" << endl;
    }
    cout << "\nЗанятые ячейки:" << endl;
    for (const auto& cell : cells)
    {
        cout << "  " << cell.first.zone << cell.first.rack << cell.first.section << cell.first.shelf << ": ";
        for (const auto& item : cell.second)
        {
            cout << item.first << " (" << item.second << " шт.), ";
        }
        cout << endl;
    }
    cout << "\nСписок свободных ячеек:" << endl;
    for (char z = 'A'; z <= 'C'; ++z)
    {
        cout << "Зона " << z << ":" << endl;
        int count = 0;
        for (int r = 1; r <= RACKS; ++r)
        {
            for (int sect = 1; sect <= SECTIONS; ++sect)
            {
                for (int shelf = 1; shelf <= SHELVES; ++shelf)
                {
                    CellAddress address = { z, r, sect, shelf };
                    if (!cells.count(address))
                    {
                        cout << address.zone << address.rack << address.section << address.shelf << " ";
                        count++;
                    }
                }
                cout << endl;
            }
        }
        if (count == 0)
        {
            cout << "Свободных ячеек нет." << z << "." << endl;
        }
        cout << endl;
    }
}
tuple<string, int, CellAddress> process() {
    string item, ind;
    int quantity;
    cin >> item >> quantity >> ind;
    CellAddress address;
    address.zone = ind[0];
    address.rack = stoi(ind.substr(1, ind.length() - 3));
    address.section = stoi(ind.substr(ind.length() - 2, 1));
    address.shelf = stoi(ind.substr(ind.length() - 1, 1));
    return make_tuple(item, quantity, address);
}
int main() 
{
    setlocale(LC_ALL, "rus");
    string command;
    while (true) 
    {
        cout << "Введите запрос: ";
        cin >> command;
        if (command == "ADD")
        {
            string item;
            int quantity;
            CellAddress address;
            tie(item, quantity, address) = process();
            ADD(item, quantity, address);
        }
        else if (command == "REMOVE") 
        {
            string item;
            int quantity;
            CellAddress address;
            tie(item, quantity, address) = process();
            REMOVE(item, quantity, address);
        }
        else if (command == "INFO") 
        {
            INFO();
        }
        else if (command == "EXIT")
        {
            break;
        }
        else 
        {
            cout << "Неизвестная команда." << endl;
        }
    }
    return 0;
}
