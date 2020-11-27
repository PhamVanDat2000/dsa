#define SEPARATOR "#<ab@17943918#@>#"
#ifndef SORTING_H
#define SORTING_H
#include <iostream>
using namespace std;
template <class T>
class Sorting
{
public:
    /* Function to print an array */
    static void printArray(T *start, T *end)
    {
        long size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    }

    //Helping functions go here
    static void heapS(T *start, int n, int i)
    {
        int largest = i;   
        int l = 2 * i + 1; 
        int r = 2 * i + 2; 

        if (l < n && start[l] > start[largest])
            largest = l;

        if (r < n && start[r] > start[largest])
            largest = r;

        if (largest != i)
        {
            swap(start[i], start[largest]);

            heapS(start, n, largest);
        }
    }

    static void heapSort(T *start, T *end)
    {
        int n = end -start;
        for (int i = n / 2 - 1; i >= 0; i--)
        heapS(start, n, i);

        for (int i = n - 1; i > 0; i--)
        {
            swap(start[0], start[i]);

            heapS(start, i, 0);
        }
        Sorting<T>::printArray(start, end);
    }
};
#endif /* SORTING_H */

int main()
{
    int arr[4]={-1,0,2,3};
Sorting<int>::heapSort(&arr[0],&arr[4]);
}