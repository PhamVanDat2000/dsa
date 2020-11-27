#include <iostream>
using namespace std;

void reheapDown(int maxHeap[], int numberOfElements, int index)
{
    int large;
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    if (left <= numberOfElements-1)
    {
        if (right <= numberOfElements - 1 && maxHeap[right] > maxHeap[left])
        {
            large = right;
        }
        else
        {
            large = left;
        }
        if (maxHeap[large] > maxHeap[index])
        {
            swap(maxHeap[large], maxHeap[index]);
            reheapDown(maxHeap,numberOfElements, large);
        }
    }
}
void reheapUp(int maxHeap[],int index)
{
    int parent;
    if (index > 0)
    {
        parent = (index - 1) / 2;
        if (maxHeap[index] > maxHeap[parent])
        {
            swap(maxHeap[index], maxHeap[parent]);
            reheapUp(maxHeap, parent);
        }
    }
}
void reheapUp(int maxHeap[], int numberOfElements, int index)
{
    reheapUp(maxHeap,index);
}

int main()
{
int arr[] = {1,2,3,4,5,6,7,8};
int size = sizeof(arr)/sizeof(arr[0]);
reheapUp(arr,size,7);
cout << "[ ";
for(int i=0;i<size;i++)
    cout << arr[i] << " ";
cout << "]";
}