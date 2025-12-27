#include "Heap.h"
#include <iostream>
using namespace std;
int main () 
{
    MinHeap<int> heap;
    heap.push (1);
    heap.push (-100);
    heap.push (10000);
    cout << heap.top() << endl;
    heap.pop();
    cout << heap.top() << endl;
    MaxHeap<int> heap2;
    heap2.push (1);
    heap2.push (-100);
    heap2.push (10000);
    cout << heap2.top() << endl;
    // tree.push(20, 200);
    // tree.push(5, 50);           
}