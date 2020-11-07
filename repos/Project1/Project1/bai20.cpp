#include<iostream>
#include<string>
using namespace std;
bool isPalindrome(string str)
{
    bool static check = false;
    bool static res;
    int n = str.length() - 1;
    int static temp = 0;
    int static i = 0;
    if ((n-temp) < i) {
        i = 0;
        temp = 0;
        res = check;
        check = false;
        return false;
    }
    else if (str[i] != ' ') {
        if (str[n-temp] != ' ') {
            if (str[n - temp] == str[i]) {
                check = true;
                i++;
                temp++;
                isPalindrome(str);
            }
            else {
                i = 0;
                temp = 0;
                check = false;
                res=false;
                return false;
            }
        }
        else {
            temp++;
            isPalindrome(str);
        }
    }
    else {
        i++;
        isPalindrome(str);
    }

    i = 0;
    temp = 0;
    return res;
}


int main() {
    cout << isPalindrome("daytad");
    cout << isPalindrome("12345678987654321");

    return 0;
}