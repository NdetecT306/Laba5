#include <string>
#include <vector>
#include <map>
using namespace std;
struct Trolleybus {
    string name;
    vector<string> stops;
};
void stops(const string& trolleybus_name, map<string, Trolleybus>& trolleybuses);
void find(const string& stop_name, map<string, Trolleybus>& trolleybuses);
void display(map<string, Trolleybus>& trolleybuses);
void create(const string& name, const vector<string>& stops, map<string, Trolleybus>& trolleybuses);
