#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <map>
#include <vector>
#include <set>
using namespace std;
bool findPairs(int arr[], int n)
{
    map<int, pair<int, int>> Hash;

    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            int sum = arr[i] + arr[j];
            if (Hash.find(sum) == Hash.end())
                Hash[sum] = make_pair(i, j);

            else
                pair<int, int> pp = Hash[sum];
            cout << "(" << arr[pp.first] << ", " << arr[pp.second]
                 << ") and (" << arr[i] << ", " << arr[j] << ")n";
            return true;
        }
    }
    return false;
}
bool findPairs(int arr[], int n,pair<int, int> pair1,pair<int, int> pair2){
    return findPairs(arr, n);
}

int main()
{
    int arr[] = {3, 4, 7, 1, 2, 9, 8};
    int n = sizeof arr / sizeof arr[0];
    pair<int, int> pair1, pair2;
    if (findPairs(arr, n, pair1, pair2))
    {
        if (checkAnswer(arr, n, pair1, pair2))
        {
            printf("Your answer is correct.\n");
        }
        else
            printf("Your answer is incorrect.\n");
    }
    else
        printf("No pair found.\n"); 
}