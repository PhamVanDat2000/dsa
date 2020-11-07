#include <iostream>

using namespace std;

void printArray(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
}

void insertionSort(int a[], int n)
{
    int idx;
    int temp;
    for (int i = 1; i < n; i++)
    {
        idx = i;
        temp = a[idx];
        while (temp < a[idx - 1] && idx > 0)
        {
            a[idx] = a[idx - 1];
            idx--;
        }
        a[idx] = temp;
        
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
    insertionSort(a, n);
    printArray(a, n);

    return 0;
}