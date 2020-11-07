#ifndef SORTING_H
#define SORTING_H
#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;
template <class T>
class Sorting {
private:
    static T* Partition(T* start, T* end){
    // pivot (Element to be placed at right position)
    int i= 1;
    int j = end - start ;
    T pivot = *start;
    T temp;

    while (i <= j)
    {
        while (start[i] <= pivot)
            i++;
        while (start[j] > pivot)
            j--;
        if (i <= j)
        {
            temp = start[i];
            start[i] = start[j];
            start[j] = temp;
            i++;
            j--;
        }
    }
    start[0] = start[j];
    start[j] = pivot;
    return &start[j];
    }
public:
    static void QuickSort(T* start, T* end){
        T static  *begin = start;
        cout << "  begin"<< *begin << "begin  " ; 
        bool static a = true;
        if(a){
        end--;
        }
        if (end - start +1 > 1){
        if (start < end)
        {
            T *res;
            /* pi is partitioning index, arr[pi] is now
           at right place */
           if(a){
            res = Partition(start, end);
            cout << (int)(res-begin);
           }else{
            res = Partition(start, end);
            cout <<", "<< (int)(res-begin);
           }
            a=false;
            QuickSort(start, res - 1);  // Before pi
            QuickSort(res + 1, end); // After pi
        }
}
    }
};
#endif /* SORTING_H */

int main(){
    int array[] = { 3, 5, 7, 10 ,12, 14, 15, 13, 1, 2, 9, 6, 4, 8, 11, 16, 17, 18, 20, 19 };
    cout << "Index of pivots: ";
    Sorting<int>::QuickSort(&array[0], &array[20]);
    cout << "\n";
    cout << "Array after sorting: ";
    for (int i : array) cout << i << " ";
    return 0;
}