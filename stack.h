#ifndef STACK_H
#define STACK_H

#include <list.h>
#include <exception>

template<class T>
class Stack
{
private:
    List<T> list;
public:
    Stack()
    {

    }
    void Push(T obj)
    {
        list.Add(obj);
    }
    T Pop()
    {
        if(list.last)
        {
            T obj = list.last->value;
            list.Remove();
            return obj;
        }
        throw std::out_of_range("Out of range");
    }
    bool empty()
    {
        return !list.last;
    }

};

#endif // STACK_H
