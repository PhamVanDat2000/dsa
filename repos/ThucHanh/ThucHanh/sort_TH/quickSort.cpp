#ifndef SORTING_H
#define SORTING_H
#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;
template <class T>
class Sorting
{
private:
    static T *Partition(T *start, T *end){
        T p  = *start;
        T* i=start+1;
        T* j = end;
        do{
            while(*i<p){
                i++;
            }
            while(*j>p){
                j--;
            }
            swap(*i, *j);
        }while(i<j);
        swap(*i,*j);
        swap(*start, *j);
        return j;
    }

public:
    static void QuickSort(T *start, T *end){
        if(start<end){
            T *res;
            res = Partition(start, end -1 );
            cout << res - start <<" ";
            QuickSort(start, res);
            QuickSort(res+1, end);
        }
    }
};
#endif /* SORTING_H */
int main()
{
    int array[] = {3, 5, 7, 10, 12, 14, 15, 13, 1, 2, 9, 6, 4, 8, 11, 16, 17, 18, 20, 19};
    cout << "Index of pivots: ";
    Sorting<int>::QuickSort(&array[0], &array[20]);
    cout << "\n";
    cout << "Array after sorting: ";
    for (int i : array)
        cout << i << " ";
}