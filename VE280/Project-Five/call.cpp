#include <iostream>
#include <string>
#include "dlist_impl.h"

using namespace std;

const int STATUSNUM = 4;
const string STATUS[4] = {"regular", "silver", "gold", "platinum"};

struct customer
{
    unsigned int timestamp;
    string name;
    string status;
    unsigned int duration;
};

int queueLine(const string &str)
//MODIFIED: str is in STATUS
//EFFECTS: Return the level of status
{
    for (int i = 0; i < STATUSNUM; i++)
    {
        if (str == STATUS[i])
            return i;
    }
    return STATUSNUM;
}

int answerLine(const unsigned int tick, Dlist<customer> &answer)
//MODIFIED: answer is non-empty
//EFFECTS: If answering the first customer in "answer", report and 
//    return the time needed for answering; else return 0.
{
    customer *temp = answer.removeFront();
    if (temp->timestamp <= tick)
    {
        cout << "Answering call from " << temp->name << endl;
        return temp->duration;
    }
    answer.insertFront(temp);
    return 0;
}

int main()
{
    unsigned int N = 0, tick = 0;
    Dlist<customer> callers, regular, silver, gold, platinum;
    int dtemp = 0;
    cin >> N;
    customer *temp = new customer[N];
    customer *data = new customer[N];
    for (unsigned int i = 0; i < N; i++)
    {
        cin >> temp[i].timestamp >> temp[i].name >> temp[i].status >> temp[i].duration;
        data[i] = temp[i]
        callers.insertBack(&temp[i]);
        int s = queueLine(data[i].status);
        if (s == 0)
            regular.insertBack(&data[i]);
        else if (s == 1)
            silver.insertBack(&data[i]);
        else if (s == 2)
            gold.insertBack(&data[i]);
        else if (s == 3)
            platinum.insertBack(&data[i]);
    }
    while (!regular.isEmpty() || !silver.isEmpty() || !gold.isEmpty() ||!platinum.isEmpty() || dtemp >= 0)
    {
        cout << "Starting tick #" << tick << endl;
        while (!callers.isEmpty())
        {
            customer *caller = callers.removeFront();
            if (caller->timestamp == tick)
                cout << "Call from " << caller->name << " a " << caller->status << " member" << endl;
            else
            {
                callers.insertFront(caller);
                break;
            }
        }
        if (dtemp == 0 && !platinum.isEmpty())
            dtemp = answerLine(tick, platinum);
        if (dtemp == 0 && !gold.isEmpty())
            dtemp = answerLine(tick, gold);
        if (dtemp == 0 && !silver.isEmpty())
            dtemp = answerLine(tick, silver);
        if (dtemp == 0 && !regular.isEmpty())
            dtemp = answerLine(tick, regular);
        dtemp --;
        tick ++;
    }
    delete[] temp;
    delete[] data;
}
