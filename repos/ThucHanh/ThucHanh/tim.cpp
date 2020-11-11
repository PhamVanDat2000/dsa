#ifndef SORTING_H
#define SORTING_H
#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;
template <class T>
class Sorting
{
private:
    static void printArray(int *start, int *end)
    {
        int size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << " ";
        cout << start[size - 1];
        cout << endl;
    }

    static void merge(T *start, T *middle, T *end)
    {
        int *pL = start;
        int i, j;
        int n1 = (middle - start) + 1;
        int n2 = (end - middle - 1);
        int L[n1];
        int R[n2];
        int *p = start;
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
    }

public:
    static void InsertionSort(T *start, T *end)
    {
        int n = end - start;
        int idx;
        int temp;
        for (int i = 1; i < n; i++)
        {
            idx = i;
            temp = start[idx];
            while (temp < start[idx - 1] && idx > 0)
            {
                start[idx] = start[idx - 1];
                idx--;
            }
            start[idx] = temp;
        }
    }
    static void TimSort(T *start, T *end, int min_size)
    {
        int n = end - start;
        // Sort individual subarrays of size RUN
        for (int i = 0; i < n; i += min_size)
        {
            InsertionSort(start + i, start + min((i + 4), (n)));
        }
        cout << "Insertion Sort: ";
        printArray(start, end);
        // Start merging from size RUN (or 32).
        // It will merge
        // to form size 64, then 128, 256
        // and so on ....
        for (int size = min_size; size < n; size = 2 * size)
        {

            // pick starting point of
            // left sub array. We
            // are going to merge
            // arr[left..left+size-1]
            // and arr[left+size, left+2*size-1]
            // After every merge, we
            // increase left by 2*size
            for (int left = 0; left < n; left += 2 * size)
            {

                // find ending point of
                // left sub array
                // mid+1 is starting point
                // of right sub array
                int mid = left + size - 1;
                int right = min((left + 2 * size - 1), (n));

                // merge sub array arr[left.....mid] &
                // arr[mid+1....right]
                merge(start + left, start + mid, start + right + 1);
                cout << "Merge: ";
                printArray(start, end);
            }
        }
    }
};
#endif /* SORTING_H */

int main()
{
    int array[] = {19, 20, 18, 17, 12, 13, 14, 15, 1, 2, 9, 6, 4, 7, 11, 16, 10, 8, 5, 3};
    int const min_size = 4;
    Sorting<int>::TimSort(&array[0], &array[20], min_size);
    return 0;
}