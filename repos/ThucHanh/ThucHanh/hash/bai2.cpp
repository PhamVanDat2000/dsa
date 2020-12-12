#include<iostream>
#include<cstring>
using namespace std;
int foldShift(long long key, int addressSize){
    int res =0;
    string s = to_string(key);
    int szkey = s.size();
    char arr[szkey];
    strcpy(arr, s.c_str());
    string k = "";
    int add = addressSize;
    int i=0;
    while(i<szkey){
        k = "";
        while(i<addressSize){
            k+=arr[i];
            i++;
        }
        res+= atoi(k.c_str());
        addressSize += add;
    }
    return res;
}

int rotation(long long key, int addressSize){
    int res =0;
    string s = to_string(key);
    int szkey = s.size();
    char arr[szkey];

    strcpy(arr, s.c_str());
    string k = "";
    k+=arr[szkey-1];
    k+=arr[0];
    res += atoi(k.c_str());
    int add = addressSize;
    int i=1;
    while(i<szkey-1){
        k = "";
        while(i<addressSize+1){
            k+=arr[i];
            i++;
        }
        res+= atoi(k.c_str());
        addressSize += add;
    }
    return res;
}
int main(){
    cout << rotation(500101, 2);
    return 0;
}