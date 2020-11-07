#include<iostream>
using namespace std;
int decimalToBinary(int decimal_number)
{
    /*
     * STUDENT ANSWER
     */
    int b;
    if (decimal_number == 0)
        return 0;
    else
        b = decimal_number % 2;
    return decimalToBinary(decimal_number / 2) * 10 + b;
}
int main() {
    cout << decimalToBinary(20);
    return 0;
}