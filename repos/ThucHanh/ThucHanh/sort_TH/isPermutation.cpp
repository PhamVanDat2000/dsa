#ifndef SORTINGAPPLICATION_H
#define SORTINGAPPLICATION_H
#include <iostream>
#include <string>
using namespace std;

template <class T>
class Sorting
{
public:
    /* Function to print an array */

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

bool isPermutation(string a, string b)
{
    int firstOne = a.length();
    int secondOne = b.length();

    //if lengths don't match, can't be permutatons of each other.
    if (firstOne != secondOne)
        return false;

    //sort both strings
    Sorting<char>::mergeSort(&a[0], &a[firstOne - 1]);
    Sorting<char>::mergeSort(&b[0], &b[secondOne - 1]);

    //compare sorted strings
    for (int i = 0; i < firstOne; i++)
        if (a[i] != b[i])
            return false;

    return true;
}
#endif /* SORTINGAPPLICATION_H */

int main()
{
    string a = "abbac";
    string b = "baba";
    cout << isPermutation(a, b);
    return 0;
}