#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;
vector<int> New(int n, vector<int>& q)
{
    if (n > 0) 
    {
        cout << "Welcome " << n << " clever students!" << endl;
        if (q.empty()) 
        {
            q.reserve(n);  
            for (int i = 1; i <= n; ++i) 
            {
                q.push_back(i);
            }
        }
        else 
        {
            int ind = q.size();
            q.reserve(ind + n);
            for (int i = ind; i < ind + n; ++i) 
            {
                q.push_back(i + 1); 
            }
        }
    }
    else if (n < 0)
    {
        if (-n <= q.size())
        {
            cout << "GoodBye " << -n << " clever students!" << endl;
            q.erase(q.end() + n, q.end()); 
        }
        else
        {
            cerr << "Incorrect" << endl;
        }
    }
    else {
        cerr << "Incorrect" << endl;
    }
    return q;
}
int main()
{
    string command;
    vector<int> allStud;
    vector<int> queue;
    while (true)
    {
        cin >> command;
        if (command == "NEW_STUDENTS")
        {
            int numbers;
            cin >> numbers;
            New(numbers, allStud);
        }
        if (command == "SUSPICIOUS")
        {
            int numberOfStud;
            cin >> numberOfStud;
            bool isInAll = false;
            for (int student : allStud) {
                if (student == numberOfStud) {
                    isInAll = true;
                    break;
                }
            }
            if (!isInAll) {
                cout << "Incorrect" << endl;
            }
            else {
                bool found = false;
                for (int student : queue) {
                    if (student == numberOfStud) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "The suspected student " << numberOfStud << endl;
                    queue.push_back(numberOfStud);
                }
                else {
                    cout << "Incorrect" << endl;
                }
            }
        }
        if (command == "IMMORTIAL")
        {
            int numberOfStud;
            cin >> numberOfStud;
            bool found = false;
            for (int i = 0; i < queue.size(); ++i) {
                if (queue[i] == numberOfStud) {
                    cout << "Student " << numberOfStud << " is immortal!" << endl;
                    queue.erase(queue.begin() + i);
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Incorrect" << endl;
            }
        }
        if (command == "TOP-LIST"){
            if (queue.empty()) cout << "Incorrect" << endl;
            else{
                sort(queue.begin(), queue.end());
                cout << "List of students for expulsion: ";
                for (int e : queue)
                {
                    cout << e << " ";
                }
                cout << endl;
            }
        }
        if (command == "SCOUNT")
        {
            cout << "List of students for expulsion consists of " << queue.size() << " students" << endl;
        }
        if (command == "EXIT")
        {
            break;
        }
    }
}
