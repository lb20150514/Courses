#ifndef DLIST_IMPL_H
#define DLIST_IMPL_H

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include "dlist.h"

using namespace std;

template <class T>
bool Dlist<T>::isEmpty() const
{
    return !first && !last;
}

template <class T>
void Dlist<T>::insertFront(T *p)
{
    node *np = new node;
    np->op = p;
    np->prev = NULL;
    np->next = first;
    if (isEmpty())
        last = np;
    else
        first->prev = np;
    first = np;
}

template <class T>
void Dlist<T>::insertBack(T *p)
{
   node *np = new node;
    np->op = p;
    np->next = NULL;
    np->prev = last;
    if (isEmpty())
        first = np;
    else
        last->next = np;
    last = np;
}

template <class T>
T * Dlist<T>::removeFront()
{
    if (isEmpty())
    {
        emptyList emp;
        throw emp;
    }

    node *victim = first;
    T *result = victim->op;
    if (first == last)
        first = last = NULL;
    else
    {
        first = first->next;
        first->prev = NULL;
    }
    delete victim;
    return result;
}

template <class T>
T * Dlist<T>::removeBack()
{
    if (isEmpty())
    {
        emptyList emp;
        throw emp;
    }

    node *victim = last;
    T *result = victim->op;
    if (first == last)
        first = last = NULL;
    else
    {
        last = last->prev;
        last->next = NULL;
    }
    delete victim;
    return result;
}

template <class T>
Dlist<T>::Dlist():first(0), last(0)
{
}

template <class T>
Dlist<T>::Dlist(const Dlist<T> &l):first(0), last(0)
{
    copyAll(l);
}

template <class T>
Dlist<T> & Dlist<T>::operator=(const Dlist<T> &l)
{
    if(this != &l)
        copyAll(l);
    return *this;
}

template <class T>
Dlist<T>::~Dlist()
{
    removeAll();
}

template <class T>
void Dlist<T>::removeAll()
{
    while (!isEmpty())
        removeFront();
}

template <class T>
void Dlist<T>::copyAll(const Dlist<T> &l)
{
    removeAll();
    first = NULL;
    last = NULL;
    
    if(l.isEmpty())
        return;
    
    node *np = l.first;
    while (np)
    {
        insertBack(np->op);
        np = np->next;
    }
}
#endif
