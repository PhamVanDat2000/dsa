#include <iostream>

using namespace std;

void printArray(int a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}
void shellSort(int a[], int n)
{

    int interval, i, idx, temp;
    for (interval = n / 2; interval > 0; interval /= 2)
    {
        for (int i = interval; i < n; k++)
        {
            idx = i;
            temp = a[idx];
            while (a[idx - interval] > temp && idx > 0)
            {
                a[idx - interval] = a[idx];
                idx -= interval;
            }
            a[i] = temp;
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
        a[i] = 100 - 3 * i;
    }
    shellSort(a, n);
    printArray(a, n);
    return 0;
}