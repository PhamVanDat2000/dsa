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
        long size = end - start + 1;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << ", ";
        cout << start[size - 1];
        cout << endl;
    }

    static void merge(T *left, T *middle, T *right)
    {
        /*TODO*/
        T *pL = left;
        int i, j;
        int n1 = (middle - left) + 1;
        int n2 = (right - middle);
        T L[n1];
        T R[n2];
        T *p = left;
        for (i = 0; i < n1; i++)
        {
            L[i] = *(p + i);
        }
        p = middle + 1;
        for (j = 0; j < n2; j++)
        {
            R[j] = *(p + j);
        }
        int k = 0;
        i = j = 0;
        while (i < n1 && j < n2)
        {
            if (L[i] <= R[j])
            {
                *(pL + k) = L[i];
                i++;
            }
            else
            {
                *(pL + k) = R[j];
                j++;
            }
            k++;
        }
        while (i < n1)
        {
            *(pL + k) = L[i];
            i++;
            k++;
        }
        while (j < n2)
        {
            *(pL + k) = R[j];
            j++;
            k++;
        }

        Sorting::printArray(left, right);
    }
    static void mergeSort(T *start, T *end)
    {
        /*TODO*/
        if (start < end)
        {
            T *middle = start + (end - start) / 2;
            mergeSort(start, middle);
            mergeSort(middle + 1, end);
            merge(start, middle, end);
        }
    }
};
#endif /* SORTING_H */

int main()
{
    int arr[] = {19, 20, 18, 17 ,12, 13, 14, 15, 1, 2, 9, 6, 4, 7, 11, 16, 10, 8, 5, 3};
    Sorting<int>::mergeSort(&arr[0], &arr[20]);
    cout << endl
         << "=================";
    Sorting<int>::printArray(&arr[0], &arr[10]);
    return 0;
}
