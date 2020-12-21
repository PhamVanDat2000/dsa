#include<iostream>

using namespace std;

void printArray(int a[], int n){
	for (int i = 0; i < n; i++){
		cout << a[i] << " ";
	}
}
void bubbleSort(int a[], int n){
	int temp;
	bool kiemtra =true;
	for(int  i= n-1;i>1;i--){
		for(int k=0;k<i;k++){
			if(a[k]>a[k+1]){
				temp = a[k];
				a[k]=a[k+1];
				a[k+1]=temp;
				kiemtra = false;
			}
		}
		if(kiemtra)
		return;
	}
} 
int main(){
	int n;
	cin >> n;
	for (int i = 0; i < n; i++){
		cin >> a[i];
	}
	bubbleSort(a, n);
	printArray(a, n);
	
	return 0;
}