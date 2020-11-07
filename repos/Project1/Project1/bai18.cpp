#include<iostream>
using namespace std;

void printHailstone(int number)
{
    /*
     * STUDENT ANSWER
     */
    if (number == 1) {
        cout << number;
        return;
    }
    cout << number << " " ;
    if (number % 2 == 0) {
        number = number / 2;
        printHailstone(number);
    }
    else {
        number = number * 3 + 1;
        printHailstone(number);
    }
}
int main() {
    printHailstone(32);
    return 0;
}