#include <bits/stdc++.h>

using namespace std;
struct data
{
    int arrvalTime;
    int completeTime;
};
int minWaitingTime(int n, int arrvalTime[], int completeTime[])
{
    // YOUR CODE HERE
    data foodTime[n];
    for (int i = 0; i < n; i++)
    {
        foodTime[i].arrvalTime = arrvalTime[i];
        foodTime[i].completeTime = completeTime[i];
    }
    int curTime = 0;
    int waitTime = 0;
    priority_queue<data, vector<data>, greater<data>> pq;
    for (int i = 0; i < n; i++)
    {
        pq.push(foodTime[i]);
    }
    while(pq.size())
    {
        if (pq.top().arrvalTime<=curTime){
            curTime += pq.top().completeTime;
            waitTime += curTime-pq.top().arrvalTime;
            pq.pop();
        }
        else{
            
        }
    }
}
int main()
{
    priority_queue<
    int n = 4;
    int arrvalTime[] = {0, 4, 2, 5};
    int completeTime[] = {4, 2, 3, 4};
    cout << minWaitingTime(n, arrvalTime, completeTime);
    return 0;
}