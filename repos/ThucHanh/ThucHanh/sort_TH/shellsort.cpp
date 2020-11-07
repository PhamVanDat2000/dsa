#include <sstream>
#include <iostream>
#include <type_traits>
using namespace std;

template <class T>
class Sorting
{
private:
    static void printArray(T *start, T *end)
    {
        int size = end - start;
        for (int i = 0; i < size; i++)
            cout << start[i] << " ";
        cout << endl;
    }

    static void sortSegment(T *start, T *end, int segment_idx, int cur_segment_total);

public:
    static void ShellSort(T *start, T *end, int *num_segment_list, int num_phases);
};

template <class T>
static void sortSegment(T *start, T *end, int segment_idx, int cur_segment_total)
{
    // TODO
    int size = end - start;
    for (int i = 0; i < size; i += cur_segment_total)
    {
        if (start[i] > start[i + cur_segment_total])
        {
            T temp = start[i];
            start[i] = start[i + cur_segment_total];
            start[i + cur_segment_total] = temp;
        }
    }
}
template <class T>
static void ShellSort(T *start, T *end, int *num_segment_list, int num_phases)
{
    // TODO
    // Note: You must print out the array after sorting segments to check whether your algorithm is true.
    for (int i = num_phases; i >0; i--)
    {
        for(int j =0; j<num_segment_list[num_phases-1];j++)
        sortSegment(start, end,j,num_segment_list[num_phases-1]);
    }

    printArray(start, end);
}
int main()
{
    int num_segment_list[] = {1, 3, 5};
    int num_phases = 3;
    int array[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    Sorting<int>::ShellSort(&array[0], &array[10], &num_segment_list[0], num_phases);
}
