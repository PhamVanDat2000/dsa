#include<iostream>
#include<vector>
#include<list>
#include<sstream>
using namespace std;

//void DList<T>::Insert(const T& a, int idx) {
//	if (pCur == nullptr) {
//		pCur = new Node(a, nullptr, nullptr);
//		curIdx = 0;
//	}
//	else if (idx >= nE) {
//		while (pCur->pNext) pCur = pCur->pNext;
//		pCur->pNext = new Node(a, nullptr, pCur);
//		pCur = pCur->pNext;
//		curIdx = nE;
//	}
//	else {
//		while (idx > curIdx) {
//			pCur = pCur->pNext;
//			curIdx++;
//		}
//		while (idx < curIdx) {
//			pCur = pCur->pNext;
//			curIdx--;
//		}
//		pCur->pNext = new Node(a, pCur, pCur);
//	}
//
//	}
int main() {
	int** fragmentPointers = new int *[2];
	fragmentPointers[0] = NULL;
	fragmentPointers[1] = NULL;
	cout << fragmentPointers[0] << endl;
	cout << fragmentPointers[1] << endl;





	return 0;
}