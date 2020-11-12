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
    static void printArray(T* start, T* end)
    {
        int  size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << " ";
        cout << start[size - 1];
        cout << endl;
    }

    static void merge(T *start, T *middle, T *end)
    {
        T *pL = start;
        int i, j;
        int n1 = (middle - start) + 1;
        int n2 = (end - middle);
        T L[n1];
        T R[n2];
        T *p = start;
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
        T temp;
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
        int j = 0;
        for (int size = min_size; size < n; size = 2 * size)
        {

            for (int left = 0; left < n; left += 2 * size)
            {
                j++;
                int mid = min(left + size - 1, n - 2);
                int right = min((left + 2 * size - 1), (n - 1));
                
                merge(start + left, start + mid, start + right);
                cout << "Merge " << j << ": ";
                printArray(start, end);
            }
        }
    }
};
#endif /* SORTING_H */

int main()
{
    float array[] = {19.1, 20.1, 18.1, 17.1, 12.1, 13.1, 14.1, 15.1, 1.1, 2.1, 9.1, 6.1, 4.1, 7.1, 11.1, 16.1, 10, 8, 5, 3};
    int min_size = 4;
    Sorting<float>::TimSort(&array[0], &array[20], min_size);
    return 0;
}