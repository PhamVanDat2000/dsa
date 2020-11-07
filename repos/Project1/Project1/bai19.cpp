#include<iostream>
using namespace std;

int myArrayToInt(char* str, int n)
{
    /*
     * STUDENT ANSWER
     */
    int static sum = 0;
    int static num;
    int a = str[n-1] - '0';
    if (n > 0) {
        sum = myArrayToInt(str, n - 1) * 10 + a;
    }
    num = sum;
    sum = 0;
        return num;
}



int main() {
    char str[] = "123456";
    printf("%d", myArrayToInt(str, 6));


    char a[] = "2020";

    printf("%d", myArrayToInt(a, 4));
    system("pause");
    return 0;
}