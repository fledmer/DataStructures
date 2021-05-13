#include "list.h"
#include <iostream>
#include <queue.h>
#include <vector>
#include "time.h"
#include "list.h"
#include "queue"
#include "binarytree.h"
using namespace std;

#define MAX(a,b) a>b?a:b;

//typedef int (*MY)(int a);
using MY = int(*)(int a);


int main()
{
    BinaryTree<int> a(10);
    a.insert(a.opr,1);
    a.insert(a.opr,2);
    a.insert(a.opr,3);
    a.insert(a.opr,4);
    a.Push(15);
    a.Push(5);
    /*
    a.Push(7);
    a.Push(6);
    a.Push(8);
    a.Push(9);
    a.Push(3);
    a.Push(4);
    a.Push(2);
    a.Push(1);
    a.Push(13);
    a.Push(17);
    a.Push(18);
    a.Push(19);
    a.Push(11);
    a.Push(12);
    a.Push(19);
    a.Push(20);
    a.Push(18);
    a.Push(14);
    a.Push(16);*/
    vector<int> b = a.Convert_ToVector();
    cout << endl;
    for(int x = 0; x < b.size();x++)
    {
        cout << b[x] << endl;
    }
    /*cout << a.Remove(15) << endl;
    cout << a.Out(1) << endl;
    cout << a.Out(2) << endl;
    cout << a.Out(3) << endl;
    cout << a.Search(17) << endl;*/
}
