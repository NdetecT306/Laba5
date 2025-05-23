#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set> 
using namespace std;
vector<int> New(int n, vector<int>& q){
    if (n > 0) {
        cout << "Welcome " << n << " clever students!" << endl;
        if (q.empty()) {
            q.reserve(n);  
            for (int i = 1; i <= n; ++i) {
                q.push_back(i);
            }
        }
        else {
            int ind = q.size();
            q.reserve(ind + n);
            for (int i = ind; i < ind + n; ++i) {
                q.push_back(i + 1); 
            }
        }
    }
    else if (n < 0){
        if (-n <= q.size()){
            cout << "GoodBye " << -n << " clever students!" << endl;
        }
        else{
            cerr << "Incorrect" << endl;
        }
    }
    else {
        cerr << "Incorrect" << endl;
    }
    return q;
}
int main(){
    string command;
    vector<int> allStud;
    vector<int> queue;
    set<int> immortalStud; 
    while (true)
    {
        cin >> command;
        if (command == "NEW_STUDENTS")
        {
            int numbers;
            cin >> numbers;
            if (numbers < 0) {
                if (-numbers <= allStud.size()) 
                {
                    New(numbers, allStud); 
                    vector<int> studentsToRemove;
                    int numToRemove = -numbers;
                    for (int i = allStud.size()-1; i >= 0 && numToRemove > 0; --i) 
                    {
                        if (immortalStud.find(allStud[i]) == immortalStud.end())
                        {
                            studentsToRemove.push_back(allStud[i]);
                            numToRemove--;
                        }
                    }
                    for (int i = 0; i < studentsToRemove.size(); ++i) 
                    {
                        for (int j = 0; j < allStud.size(); ++j)
                        {
                            if (allStud[j] == studentsToRemove[i])
                            {
                                allStud.erase(allStud.begin() + j);
                                break;
                            }
                        }
                    }
                    vector<int> toRemoveQueue;
                    for (int i = 0; i < queue.size(); ++i) 
                    {
                        bool checkStud = false;
                        for (int stud : allStud) 
                        {
                            if (queue[i] == stud) 
                            {
                                checkStud = true;
                                break;
                            }
                        }
                        if (checkStud) {
                            toRemoveQueue.push_back(queue[i]);
                        }
                    }
                    for (int rem : toRemoveQueue) 
                    {
                        for (int i = 0; i < queue.size(); ++i) 
                        {
                            if (queue[i] == rem) {
                                queue.erase(queue.begin() + i);
                                break;
                            }
                        }
                    }

                } 
                else 
                {
                    cerr << "Incorrect" << endl;
                }
            }
            else {
                New(numbers, allStud);
            }
        }
        else if (command == "SUSPICIOUS")
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
            if (!isInAll) cout << "Incorrect" << endl;
            else 
            {
                bool found = false;
                for (int student : queue) 
                {
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
        else if (command == "IMMORTIAL")
        {
            int numberOfStud;
            cin >> numberOfStud;
            bool found = false;
            for (int i = 0; i < queue.size(); ++i) 
            {
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
            immortalStud.insert(numberOfStud); 
        }
        else if (command == "TOP-LIST")
        {
            if (queue.empty()) cout << "No students" << endl;
            else{
                sort(queue.begin(), queue.end());
                cout << "List of students for expulsion: ";
                for (int e : queue){
                    cout << e << " ";
                }
                cout << endl;
            }
        }
        else if (command == "SCOUNT")
        {
            cout << "List of students for expulsion consists of " << queue.size() << " students" << endl;
        }
        else if (command == "EXIT")
        {
            break;
        }
    }
    return 0;
}
