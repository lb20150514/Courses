#include <cstdlib>
#include <string>
#include <iostream>
#include "dlist_impl.h"
using namespace std;

int value(Dlist<int> &dli)
{
    T* el = dli.removeFront();
    T element = *el;
    delete el;
    return element;
}

int main()
{
    Dlist<int> dli;
    string stemp = "";
    int *a = new int;
    while (stemp != "q")
    {
         cin >> stemp;
         try
         {
             if (stemp == "+")
             {
                 *a = value(dli) + value(dli);
                 dli.insertFront(a);
             }
             else if (stemp == "-")
             {
                 *a = - *dli.removeFront() + *dli.removeFront();
                 dli.insertFront(a);
             }
             else if (stemp == "*")
             {
                 *a = *dli.removeFront() * *dli.removeFront();
                 dli.insertFront(a);
             }
             else if (stemp == "/")
             {
                 *a = *dli.removeFront();
                 if (*a == 0)
                 {
                     cout << "Divide by zero\n";
                     continue;
                 }
                 *a = *dli.removeFront() / *a;
                 dli.insertFront(a);
             }
             else if (stemp == "n")
             {
                 *a = - *dli.removeFront();
                 dli.insertFront(a);
             }
             else if (stemp == "d")
             {
                 *a = *dli.removeFront();
                 dli.insertFront(a);
                 dli.insertFront(a);
             }
             else if (stemp == "r")
             {
                 for (int i = 0; i < 2; i++)
                 {
                     *a = *dli.removeFront();
                     dli.insertFront(a);
                 }
             }
             else if (stemp == "p")
             {
                 *a = *dli.removeFront();
                 cout << *a << endl;
                 dli.insertFront(a);
             }
             else if (stemp == "c")
             {
                 while (!dli.isEmpty())
                     dli.removeFront();
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
            else
            {
                *a = atoi(stemp.c_str());
                if (*a == atof(stemp.c_str()))
                    dli.insertFront(a);
                else
                    cout << "Bad input\n";
            }
        }
        catch (emptyList emp)
        {
            cout << "Not enough operands\n";
            continue;
        }
    }
    delete a;
}
