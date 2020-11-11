#ifndef SORTING_H
#define SORTING_H
#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;
template <class T>
class Sorting {
private:
    static void printArray(T* start, T* end)
    {
        int  size = end - start;
        for (int i = 0; i < size - 1; i++)
            cout << start[i] << " ";
        cout << start[size - 1];
        cout << endl;
    }

    static void merge(T* start, T* middle, T* end) {
        int len1 = middle - start + 1, len2 = end - middle; 
        int left[len1], right[len2]; 
        for (int i = 0; i < len1; i++) 
            left[i] = start[i]; 
        for (int i = 0; i < len2; i++) 
            right[i] = middle[1 + i]; 
    
        int i = 0; 
        int j = 0; 
        T* k = start; 
    
        // After comparing, we  
        // merge those two array 
        // in larger sub array 
        while (i < len1 && j < len2) 
        { 
            if (left[i] <= right[j]) 
            { 
                arr[k] = left[i]; 
                i++; 
            } 
            else
            { 
                arr[k] = right[j]; 
                j++; 
            } 
            k++; 
        } 
    
        // Copy remaining elements of left, if any 
        while (i < len1) 
        { 
            arr[k] = left[i]; 
            k++; 
            i++; 
        } 
    
        // Copy remaining element of right, if any 
        while (j < len2) 
        { 
            arr[k] = right[j]; 
            k++; 
            j++; 
        } 
    }
public:
    static void InsertionSort(T* start, T* end) {
        for (int i = left + 1; i <= right; i++) 
        { 
            int temp = arr[i]; 
            int j = i - 1; 
            while (j >= left && arr[j] > temp) 
            { 
                arr[j+1] = arr[j]; 
                j--; 
            } 
            arr[j+1] = temp; 
        }
    }
    static void TimSort(T* start, T* end, int min_size){
        
        for (int i = 0; i < n; i+=RUN) 
        insertionSort(arr, i, min((i+31), (n-1))); 
        for (int size = RUN; size < n; size = 2*size) 
        {
            for (int left = 0; left < n; left += 2*size) 
            { 
                int mid = left + size - 1; 
                int right = min((left + 2*size - 1), (n-1)); 
    
                merge(arr, left, mid, right); 
            } 
        } 
    }
};
#endif /* SORTING_H */
int main(){
    int array[] = { 19, 20, 18, 17 ,12, 13, 14, 15, 1, 2, 9, 6, 4, 7, 11, 16, 10, 8, 5, 3 };
int min_size = 4;
Sorting<int>::TimSort(&array[0], &array[20], min_size);
return 0;
}