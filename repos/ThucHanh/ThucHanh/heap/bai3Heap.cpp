#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"
template <class T>
class Heap
{
protected:
    T *elements;
    int capacity;
    int count;

public:
    Heap()
    {
        this->capacity = 10;
        this->count = 0;
        this->elements = new T[capacity];
    }
    ~Heap()
    {
        delete[] elements;
    }
    void push(T item);
    void printHeap()
    {
        cout << "Max Heap [ ";
        for (int i = 0; i < count; i++)
            cout << elements[i] << " ";
        cout << "]";
    }

private:
    void ensureCapacity(int minCapacity);
    void reheapUp(int position);
};

// Your code here
template <class T>
void Heap<T>::push(T item)
{
    if(count == capacity){
        ensureCapacity(10);
    }
    
    elements[count] = item;
    count ++;
    reheapUp(count-1);
}

template <class T>
void Heap<T>::ensureCapacity(int minCapacity)
{
    T * newElement = new T[capacity+10];
    for(int i = 0;i<count;i++){
        newElement[i] = move(elements[i]);
    }
    delete elements;
    elements = newElement;
}

template <class T>
void Heap<T>::reheapUp(int position)
{
    int parent;
    if (position > 0)
    {
        parent = (position - 1) / 2;
        if (elements[position] > elements[parent])
        {
            swap(elements[position], elements[parent]);
            reheapUp(parent);
        }
    }
}

int main()
{
    Heap<int> maxHeap;
    for (int i = 0; i < 5; i++)
        maxHeap.push(i);
    maxHeap.printHeap();
}