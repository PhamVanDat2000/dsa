#include <iostream>

using namespace std;
void printArray(int n)
{
    /*
     * STUDENT ANSWER
     */
    int static i = 0;
    if (i == 0) {
        cout << i;
    }
    i++;
    if (i <= n) {
        cout << ", " << i;
        printArray(n);
    }
    i = 0;
}
int main()
{
    printArray(19);
    printArray(5);
    return 0;
}
