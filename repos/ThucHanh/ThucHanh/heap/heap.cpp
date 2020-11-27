#include <bits/stdc++.h>

using namespace std;

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
    int getItem(T item);
    void remove(T item);
    void clear();
    void printHeap()
    {
        cout << "Max Heap [ ";
        for (int i = 0; i < count; i++)
            cout << elements[i] << " ";
        cout << "]\n";
    }

private:
    void ensureCapacity(int minCapacity);
    void reheapUp(int position);
    void reheapDown(int position);
};
template <class T>
void Heap<T>::push(T item)
{
    if (count == capacity)
    {
        ensureCapacity(10);
    }

    elements[count] = item;
    count++;
    reheapUp(count - 1);
}

template <class T>
void Heap<T>::ensureCapacity(int minCapacity)
{
    T *newElement = new T[capacity + 10];
    for (int i = 0; i < count; i++)
    {
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
template <class T>
void Heap<T>::reheapDown(int position)
{
    int large;
    int left = position * 2 + 1;
    int right = position * 2 + 2;
    if (left <= count - 1)
    {
        if (right <= count - 1 && elements[right] > elements[left])
        {
            large = right;
        }
        else
        {
            large = left;
        }
        if (elements[large] > elements[position])
        {
            swap(elements[large], elements[position]);
            reheapDown(large);
        }
    }
}
//=============================================
template <class T>
int Heap<T>::getItem(T item)
{
    for (int i = 0; i < count; i++)
    {
        if (elements[i] == item)
            return i;
    }
    return -1;
}

template <class T>
void Heap<T>::remove(T item)
{
    // TODO: remove the element with value equal to item
    int i = getItem(item);
    elements[i] = move(elements[count - 1]);
    count--;
    reheapDown(i);
}

template <class T>
void Heap<T>::clear()
{
    // TODO: delete all elements in heap
    while (count)
    {
        elements[0] = move(elements[count - 1]);
        count--;
        reheapDown(0);
    }
}
int main()
{
    Heap<int> maxHeap;
    int arr[] = {13, 19, 20, 7, 15, 12, 16, 10, 8, 9, 3, 6, 18, 2, 14, 1, 17, 4, 11, 5};
    for (int i = 0; i < 20; ++i)
        maxHeap.push(arr[i]);
    maxHeap.clear();
    maxHeap.printHeap();
}