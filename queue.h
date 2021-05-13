#ifndef QUEUE_H
#define QUEUE_H

#include <list.h>
#include <exception>
#include <iostream>
#include <vector>

template<class T>
class Queue
{
private:
    List<T> list;
    //std::vector<T> list;
public:
    Queue()
    {

    }
    void Push(T obj)
    {
        list.Add(obj);
        //list.push_back(obj);
    }
    T Pop()
    {
        T obj = list.first->value;
        list.Remove(0);
        //T obj = list[0];
        //list.erase(list.first);
        return obj;
    }
    bool empty()
    {
        return !list.size();
    }

};
#endif // QUEUE_H
