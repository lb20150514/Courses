#include <cstdlib>
#include <string>
#include <iostream>
#include "dlist_impl.h"

using namespace std;

bool isint(string &temp)
{
    int len = temp.length();
    const char *p = temp.c_str();
    if ((p[0] <= '9' && p[0] >= '0') || p[0] == '-')
    {
        for (int i = 1; i < len; i ++)
        {
            if (p[i] > '9' || p[i] < '0')
                return false;
        }
        return true;
    }
    return false;
}

int main()
{
    Dlist<int> dli;
    string stemp;
    cin >> stemp;
    while (stemp != "q")
    {
        if (stemp == "c")
        {
            while (!dli.isEmpty())
            {
                int *a = dli.removeFront();
                delete a;
            }
        }
        else if (stemp == "a")
        {
            if (dli.isEmpty())
                cout << endl;
            else
            {
                Dlist<int> litemp = dli;
                while (!litemp.isEmpty())
                    cout << *litemp.removeFront() << endl;
            }
        }
        else if (stemp == "n" || stemp == "d" || stemp == "p")
        {
            if (dli.isEmpty())
                cout << "Not enough operands\n";
            else
            {
                int *a = dli.removeFront();
                if (stemp == "n")
                    dli.insertFront(new int(-*a));
                else if (stemp == "d")
                {
                    dli.insertFront(new int(*a));
                    dli.insertFront(new int(*a));
                }
                else if (stemp == "p")
                {
                    cout << *a << endl;
                    dli.insertFront(new int(*a));
                }
                delete a;
            }
        }
        else if (stemp == "+" || stemp == "-" || stemp == "*" || stemp == "/" || stemp == "r")
        {
            if (dli.isEmpty())
                cout << "Not enough operands\n";
            else
            {
                int *a = dli.removeFront();
                if (dli.isEmpty())
                {
                    cout << "Not enough operands\n";
                    dli.insertFront(new int(*a));
                }
                else
                {
                    int *b = dli.removeFront();
                    if (stemp == "+")
                        dli.insertFront(new int(*a + *b));
                    else if (stemp == "-")
                        dli.insertFront(new int(*b - *a));
                    else if (stemp == "*")
                        dli.insertFront(new int(*a * *b));
                    else if (stemp == "/")
                    {
                        if (*a == 0)
                            cout << "Divide by zero\n";
                        else
                            dli.insertFront(new int(*b / *a));
                    }
                    else if (stemp == "r")
                    {
                        dli.insertFront(new int(*a));
                        dli.insertFront(new int(*b));
                    }
                    delete b;
                }
                delete a;
            }
        }
        else if (isint(stemp))
            dli.insertFront(new int(atoi(stemp.cstr())));
        else
            cout << "Bad input\n";
        cin >> stemp;
    }
    while (!dli.isEmpty())
    {
        int *a = dli.removeFront();
        delete a;
    }
}
