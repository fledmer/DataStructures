#ifndef LIST_H
#define LIST_H
#include <stdexcept>
#include <iostream>
#include <exception>

template<class T> class List
{
private:
    bool isSorted = true;
    int _size;
    class lovList
    {
        public:
            lovList(T t){value = t; right = 0; left = 0;}
            ~lovList(){};
            T value;
            lovList *right;
            lovList *left;
    };
    void MoveRight(lovList *start)
    {
        lovList *current = last;
        while(current != start)
        {
            current->right = current;
            current = current->left;
        }
        start->right = start;
    }
public:
    lovList *first;
    lovList *last;
    List(){_size = 0;first = 0;last = 0;};
    List(const List &list);
    ~List(){
       while(first)
        {
            first = first->right;
            delete first->left;
        }
    }
    void Add(T obj)
    {
        isSorted = false;
        if(!first)
        {
            first = new lovList(obj);
            last = first;
            _size++;
            return;
        }
        last->right = new lovList(obj);
        last->right->left = last;
        last = last->right;
        _size++;
        return;
    }
    void Add(T obj, int poss)
    {
        isSorted = false;
        if(poss == 0)
        {
            if(first == 0)
                first = new lovList(obj);
            else
            {
                lovList *current = new lovList(obj);
                current->right = first;
                first->left = current;
                first = current;
            }
            _size++;
            return;
        }

        if(poss >= _size)
            throw std::out_of_range("Out of range");
        lovList *current_obj = first;
        for(int x = 0; x < poss;x++)
        {
            current_obj = current_obj->right;
        }
        lovList *new_obj = new lovList(obj);
        new_obj->right = current_obj;
        new_obj->left = current_obj->left;
        new_obj->left->right = new_obj;
        new_obj->right->left = new_obj;
        _size++;
    }
    void AddToSorted(T value)
    {
        lovList *curent = first;
        while(curent->value < value)
            curent = curent->right;
        lovList *_new = new lovList(value);
        _new->right = curent;
        _new->left = curent->left;
        curent->left = _new;
        _new->left->right = _new;
    }
    void Remove()
    {
        _size--;
        delete last;
        last = last->left;
        return;
    }
    void Remove(int x)
    {
        if(x < 0 || x >= _size)
            throw std::out_of_range("Out of range");
        else if(x == 0)
        {
            lovList *newfirst = first->right;
            delete first;
            first = newfirst;
            _size--;
            return;
        }
        else if(x == _size-1)
        {
            Remove();
            return;
        }
        else if(x > _size/2)
        {
            lovList *current = last;
            int k = _size-1;
            while(k != x)
            {
                --k;
                current = current->left;
            }
            current->left->right = current->right;
            current->right->left = current->left;
            delete current;
            --_size;
            return;
        }
        else
        {
            lovList *current = first;
            int k = 0;
            while(k != x)
            {
                ++k;
                current = current->right;
            }
            current->left->right = current->right;
            current->right->left = current->left;
            delete current;
            --_size;
            return;
        }
    }
    bool RemoveByValue(T value)
    {
        lovList* current = first;
        while(current)
        {
            if(current->value == value)
            {
                if(current == first)
                {
                    Remove(0);
                    return true;
                }
                if(current == last)
                {
                    Remove(_size-1);
                    return true;
                }
                else
                {
                    current->left->right = current->right;
                    current->right->left = current->left;
                    delete current;
                    --_size;
                    return true;
                }
            }
            current = current->right;
        }
        return false;
    }
    T pop_back()
    {
        T value = last->value;
        Remove();
        return value;
    }
    lovList* Find(T value)
    {
        if(isSorted)
        {
            int l = 0;
            int r = _size-1;
            int m = (l+r)/2;
            int lastr = 0;
            lovList* opr = getElem(m);
            while(l<r)
            {
                if(opr->value == value)
                    return opr;
                else
                {
                    if(r-l==lastr)
                        break;
                    lastr = r-l;
                    if(opr->value < value)
                    {
                        l = m;
                        m = (l+r)/2;
                        for(int x = 0; x < m-l;x++,opr = opr->right);
                    }
                    else
                    {
                        r = m;
                        m = (l+r)/2;
                        for(int x = 0; x < m-l;x++,opr = opr->left);
                    }
                }
                std::cout << r-l << std::endl;
            }
            return 0;

        }
        lovList* current = first;
        while(current)
        {
            if(current->value == value)
                return current;
            else
                current = current->right;
        }
        return 0;
    }
    List* sort()
    {
        qsort(first,last,0,_size-1);
        isSorted = true;
        return this;
    }
private:
    void qsort(lovList* left_p,lovList* right_p,int first_p, int last_p)
    {
        lovList* left = left_p;
        lovList* right = right_p;
        int f = first_p;
        int l = last_p;
        lovList* opr_p = left;
        for(int c = 0; c < (last_p-first_p)/2;c++)
        {
            opr_p = opr_p->right;
        }
        T opr = opr_p->value;
        do
        {
            while ((left->value)<opr){left=left->right;f++;}
            while ((right->value)>opr){right=right->left;l--;}
            if (f<=l) //перестановка элементов
            {
                T zat = left->value;
                left->value = right->value;
                right->value = zat;
                left = left->right;
                right = right->left;
                f++;
                l--;
            }
        } while (f<l);
        if (first_p<l) qsort(left_p,right,first_p, l);
        if (f<last_p) qsort(left,right_p,f, last_p);
    }
public:
    int size(){return _size;};
    T& operator[](int x)
    {
        if(x < 0 || x >= _size)
            throw std::out_of_range("Out of range");
        if(x > _size/2)
        {
            int k = _size-1;
            lovList *current = last;
            while(k-- != x)
                current = current->left;
            return current->value;
        }
        else
        {
            int k = 0;
            lovList *current = first;
            while(k++ != x)
                current = current->right;
            return current->value;
        }
    }
    lovList* getElem(int x)
    {
        if(x < 0 || x >= _size)
            throw std::out_of_range("Out of range");
        if(x > _size/2)
        {
            int k = _size-1;
            lovList *current = last;
            while(k-- != x)
                current = current->left;
            return current;
        }
        else
        {
            int k = 0;
            lovList *current = first;
            while(k++ != x)
                current = current->right;
            return current;
        }
    }
};

#endif // LIST_H
