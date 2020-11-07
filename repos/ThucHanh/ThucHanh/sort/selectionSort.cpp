#include <iostream>

using namespace std;

void printArray(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
}
void selectionSort(int a[], int n)
{
    int min, idx;
    int i, k;
    for (i = 0; i < n - 1; i++)
    {
        min = a[i];
        idx=i;
        for (k = i; k < n; k++)
        {
            if (a[k] < min)
            {
                min = a[k];
                idx = k;
            }
        }
        if (idx != i)
        {
            a[idx] = a[i];
            a[i] = min;
        }
    }
}
int a[100001];
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    selectionSort(a, n);
    printArray(a, n);

    return 0;
}