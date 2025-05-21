#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;
struct Visitor 
{
    string ticket;
    int duration;
};
int RandomNumbers(int start, int end) 
{
    int num;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    ranlux24_base generation(seed);
    uniform_int_distribution<int> distribution(start, end);
    num = distribution(generation);
    return num;
}
int main() 
{
    setlocale(LC_ALL, "rus");
    int N;
    cout << ">>> Введите кол-во окон" << endl;
    cout << "<<< ";
    cin >> N;
    vector<Visitor> queue;
    string command;
    while (true) 
    {
        cout << "<<< ";
        cin >> command;
        if (command == "ENQUEUE") 
        {
            int time;
            cin >> time;
            int randomNum = RandomNumbers(0, 999);
            string ticket = "T" + to_string(randomNum);
            while (ticket.length() < 4)
            {
                ticket = "T0" + ticket.substr(1);
            }
            Visitor visitor = {ticket, time};
            queue.push_back(visitor);
            cout << ">>> " << ticket << endl;
        }
        if (command == "DISTRIBUTE") 
        {
            vector<vector<Visitor>> assignments(N);
            vector<int> times(N, 0);
            sort(queue.begin(), queue.end(), [](const Visitor& a, const Visitor& b){
                return a.duration > b.duration;
                });
            for (const auto& visitor : queue) 
            {
                int index = 0;
                for (int i = 1; i < N; ++i) 
                {
                    if (times[i] < times[index]) index = i;
                }
                assignments[index].push_back(visitor);
                times[index] += visitor.duration;
            }
            for (int i = 0; i < N; ++i)
            {
                cout << ">>> Окно " << i + 1 << " (" << times[i] << " минут): ";
                for (size_t j = 0; j < assignments[i].size(); ++j) 
                {
                    cout << assignments[i][j].ticket;
                    if (j < assignments[i].size() - 1) 
                    {
                        cout << ", ";
                    }
                }
                cout << endl;
            }
            break; 
        }
        else 
        {
            cout << ">>> Неизвестная команда" << endl; 
        }
    }
    return 0;
}
