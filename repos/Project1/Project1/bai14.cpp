// Example program
#include <iostream>
#include <string>
using namespace std;
int findLCM(int a, int b)
{
    int static temp = b;
    if (b % a == 0) return b;
    return findLCM(a, b + temp);
}
int main()
{
    cout << findLCM(10, 102);
    return 0;
}