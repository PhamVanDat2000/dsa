#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
using namespace std;

//assuming (ask interviewer) case sensitive and whitespace is significant
//assuming character set = ASCII
//if strings are different lengths, they cannot be prmutations of each other
// compare lengths, sort, compare sorted strings
//*could also check to see if they both have identical char counts, by creating an array that operates like hash table, mapping each char to its frequency

bool isPermutation(string str1, string str2){
		//get lengths of both strings
		int firstOne=str1.length();					
		int secondOne=str2.length();
		
		//if lengths don't match, can't be permutatons of each other. 
		if (firstOne!=secondOne)   
			return false;
			
			//sort both strings
			sort(str1.begin(), str1.end());
			sort(str2.begin(), str2.end());
			
			//compare sorted strings
			for (int i=0;i<firstOne;i++)
				if(str1[i]!=str2[i])
				return false;
				
			return true;
}

int main() {

    cout << "Sort Test:" << endl<<endl;
    string str1 = "bestest";
    string str2 = "estxest";
    if(isPermutation(str1, str2))
      cout << str1 << " and " << str2 << " is a permutation of each other" << endl;
    else
      cout << str1 <<" and " << str2 << " is not a permutation of each other" << endl <<endl;
    str1 = "helslo";
    str2 = "soellh";
    if(isPermutation(str1, str2))
      cout << str1 <<" and " << str2 << " is a permutation of each other" << endl;
    else
      cout << str1 <<" and " << str2 << " is not a permutation of each other" << endl;
}