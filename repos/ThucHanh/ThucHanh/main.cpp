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

    static void sortSegment(T *start, T *end, int segment_idx, int cur_segment_total)
    {
        int n = end - start;
        int interval = n / cur_segment_total;
        int i, j;
        T temp;
        for (i = interval; i < n; i++)
        {
            temp = start[i];
            for (j = i; j >= interval && start[j - interval] > temp; j -= interval)
            {
                start[j] = start[j - interval];
            }
            start[j] = temp;
        }
    }

public:
    static void ShellSort(T *start, T *end, int *num_segment_list, int num_phases)
    {
        for (int i = num_phases - 1; i > -1; i--)
        {
            int cur_segment_total = (end - start) / num_segment_list[i];
            sortSegment(start, end, 0, cur_segment_total);
            cout << num_segment_list[i] << " segments: ";
            printArray(start, end);
        }
    }
};

int main()
{
    int num_segment_list[] = {1, 3, 5};
    int num_phases = 3;
    int array[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    Sorting<int>::ShellSort(&array[0], &array[10], &num_segment_list[0], num_phases);
    return 0;
}