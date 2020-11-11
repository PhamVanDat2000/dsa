#include <iostream>
using namespace std;

template <class T>
class Sorting
{
public:
    /* Function to print an array */
    static void printArray(T *start, T *end)
    {
        int size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    }

    static void selectionSort(T *start, T *end);
};
template <class T>
void Sorting<T>::selectionSort(T *start, T *end)
{
    int n = end-start;
    T min;
    int idx;
    int i, k;
    for (i = 0; i < n - 1; i++)
    {
        min = start[i];
        idx=i;
        for (k = i; k < n; k++)
        {
            if (start[k] < min)
            {
                min = start[k];
                idx = k;
            }
        }
        if (idx != i)
        {
            start[idx] = start[i];
            start[i] = min;
        }
    printArray(start, end);
    }
}

int main(){
    int arr[] = {9, 2, 8, 1, 0, -2};
Sorting<int>::selectionSort(&arr[0], &arr[6]);
return 0;
}