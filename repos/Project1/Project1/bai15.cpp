#include <iostream>
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
bool containsPattern(char* text, char* pattern)
{
    /*
     * STUDENT ANSWER
     */
    int l1 = strLen(text);
    int l2 = strLen(pattern);

    bool static check = false;
    int static i = 0;
    int static j = 0;
    if (i >= l1) {
        i = 0;
        j = 0;
        return check;
    }
    else if (text[i] == pattern[j]) {
        check = true;
        j++;
        i++;
        if (j < l2)
            containsPattern(text, pattern);
        i = 0;
        j = 0;
        return check;
    }
    i = i - j + 1;
    j = 0;
    check = false;
    if(i<l1)
        containsPattern(text, pattern);
    i = 0;
    j = 0;
    return check;
}
int main()
{
    cout << containsPattern((char*)"Dai hoc Bach Khoa", (char*)"Bach K");
    cout << containsPattern((char*)"Dai hoc Bach Khoa", (char*)"Bach K");

    return 0;
}
// KHONG DC XAI STRLEN(), DUNG LAI HAM TINH CHUOI BAI 12