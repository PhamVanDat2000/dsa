#include<iostream>
using namespace std;
int strLen(char* str)
{
    int static l;
    int static dem = 0;
    if (str[dem] != '\0') {
        dem += 1;
        strLen(str);
    }
    else {
        l = dem;
        dem = 0;
    }
    return l;
}
int main() {
    char str[] = "Truong DH Bach Khoa";
    cout << strLen(str);
    return 0;
}