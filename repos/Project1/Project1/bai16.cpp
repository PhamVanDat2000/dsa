
#include <iostream>

using namespace std;

void printPattern(int n)
{
    /*
     * STUDENT ANSWER
     */
    int static check = 0;
    int static temp = 0;
    if (temp == 0 && check == 0)
        cout << n;
    temp += 5;
    cout << " " << (n-temp) ;
    if (temp < (n) && check == 0) {
        printPattern(n);
    }
    else
    {
        check = 1;
        if (temp > 0) {
            temp -= 10;
            printPattern(n);
        }
    }
    temp = 0;
    check = 0;
}
int main()
{
    printPattern(10);
    return 0;
}
