#include <iostream>
using namespace std;
int main()
{
    int d, day, week,  year;

    printf("Nhap so ngay :");
    cin >> d;
    year = d / 365;
    week = (d - year * 365) / 7;
    day = d - 365 * year - week * 7;
    printf("%d Days = %d Years + %d Week + %d Days ", d, year, week, day);
    return 0;
}