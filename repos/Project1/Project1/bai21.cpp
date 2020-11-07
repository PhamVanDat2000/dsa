#include<iostream>
#include<string>
using namespace std;


int findMax(int* arr, int length)
{
    /*
     * STUDENT ANSWER
     */

    int static max = -100000;
    int static res;
    if (length >= 1) {
        if (max < arr[length - 1]) {
            max = arr[length - 1];
            findMax(arr, length - 1);

        }
        else
            findMax(arr, length - 1);
    }
    else {
        res = max;
        max = -100000;
        return res;
    }
}


int main() {
    int arr[] = { 10, 5, 7, 9, 15, 6, 11, 8, 12, 2 };
    cout << findMax(arr, 10);
    int a[] = { 1, 5, 7, 9, 15, 6, 11, 8, 12, 2, 100  };
    cout << findMax(a, 11);
    int b[] = { -5,-6,-7 };
    cout << findMax(b, 3);
    system("pause");
    return 0;
}