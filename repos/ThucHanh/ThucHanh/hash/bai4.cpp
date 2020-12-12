#include<iostream>
using namespace std;
#include<cstring>
{
    long long a = seed*seed;
    a= a/100;
    int res = 0;
    for(int i=0; i<4; i++){
    res += a- (a/10)*10;
    res = res*10;
    a = a/10;
    }
    return res/10;
}
long int moduloDivision(long int seed, long int mod)
{
    return seed % mod;
}
long int digitExtraction(long int seed,int* extractDigits,int size)
{
    string s = to_string(seed);
    char arr[s.size()];
    strcpy(arr, s.c_str());
    string k ="";
    for(int i = 0; i<size; i++){
        k+= arr[extractDigits[i]-1];
    }
    int res;
    res = atoi(k.c_str());
    return res;
}
int main(){
    int a[]={1,2,5};
cout << digitExtraction(122443,a,3);
}