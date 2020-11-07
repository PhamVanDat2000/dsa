#include <iostream>
#include <stack>
#include <string>

#include <stdio.h>
using namespace std;
string removeDuplicates(string s) {
		if (s.empty())
			return "";

		int n = s.length();
		int ptr = -1;
        int  i = 0;
		while (i < n) {
			if (ptr == -1 || s[ptr] != s[i]) {
				ptr++;
				s[ptr] = s[i];
				i++;
			}
			else {
				while (i < n && ptr>-1 && s[ptr] == s[i]) {
					ptr--;
					i++;
				}
			}
		}

		return s.substr(0,ptr+1);
	}
int main()
{
    cout << removeDuplicates("abbaca");
    return 0;
}