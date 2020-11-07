#include<iostream>
using namespace std;
int result = 0;
int num1 = 1;
int num2 = 1;
int sum = 0;
int ways(int x) {
    if(num1>(x/2)) return result;
    if (sum == 0) {
        int num2 = num1+1;
        sum = num1 * num1;
    }
    if ( sum == x) {
        result++;
        sum = 0;
        num1++;
        ways(x);
    }
    else if(sum > x) {
        sum = 0;
        num1++;
        ways(x);
    }
    else {
        num2++;
        sum += num2 * num2;
        ways(x);
    }
    return result;
}
int main() {
    int x = 100;
    cout << ways(x);
    return 0;
}