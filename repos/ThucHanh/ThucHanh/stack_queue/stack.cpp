#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <queue>
#include <stdio.h>
using namespace std;
//============================================================

int baseballScore(string ops)
{
    /*TODO*/
    std::stack<int> sta;
    for (int i = 0; i < (int)ops.length(); i++)
    {
        if (48 <= (int)ops[i] && (int)ops[i] <= 57)
            sta.push((int)ops[i] - 48);

        else if (ops[i] == 'C')
            sta.pop();

        else if (ops[i] == 'D')
            sta.push((sta.top()) * 2);

        else if (ops[i] == '+')
        {
            int a = sta.top();
            sta.pop();
            int b = sta.top();
            sta.push(a);
            sta.push(a + b);
        }
    }
    int sum = 0;
    while (!sta.empty())
    {
        sum += sta.top();
        sta.pop();
    }
    return sum;
}
//============================BAI3==========

// bool isValidParentheses(string s)
// {
//     /*TODO*/
//     if ((int)s.length() == 0)
//     {
//         return true;
//     }
//     else
//     {
//         std::stack<char> list;
//         for (int i = 0; i < (int)s.length(); i++)
//         {
//             if (s[i] == '{' || s[i] == '(' || s[i] == '[')
//                 list.push(s[i]);
//             if ((list.top() == '{' && s[i] == '}') || (list.top() == '(' && s[i] == ')') || (list.top() == '[' && s[i] == ']'))
//                 list.pop();
//         }
//         if (list.empty())
//             return true;
//         return false;
//     }
// }

bool isValidParentheses(string s)
{
    bool ans = true;
    stack<char> stk;
    for (int i = 0; i < (int)s.size(); i++)
    {
        if (s[i] == '(')
            stk.push('(');
        else if (s[i] == '{')
            stk.push('{');
        else if (s[i] == '[')
            stk.push('[');
        else if (s[i] == ')')
        {
            if (stk.empty() || stk.top() != '(')
            {
                ans = false;
                break;
            }
            else
                stk.pop();
        }
        else if (s[i] == '}')
        {
            if (stk.empty() || stk.top() != '{')
            {
                ans = false;
                break;
            }
            else
                stk.pop();
        }
        else
        {
            if (stk.empty() || stk.top() != '[')
            {
                ans = false;
                break;
            }
            else
                stk.pop();
        }
    }
    if (stk.empty() && ans == true)
        return true;
    else
        return false;
}

//============BAI4===============
string removeDuplicates(string S)
{
    /*TODO*/
    std::stack<char> list;
    for (int i = 0; i < (int)S.length(); i++)
    {
        if (list.top() == (int)S[i])
            list.pop();
        else
            list.push(S[i]);
    }
    string res;
    for (int i = 0; i < (int)list.size(); i++)
    {
        res[i] = list.top();
        list.pop();
    }
    return res;
}
// ========================================bai 3
void printLevels(vector<vector<int>> graph, int V, int x)
{
    int level[V];
    bool marked[V];
    queue<int> que;
    que.push(x);
    level[x] = 0;
    marked[x] = true;
    while (!que.empty())
    {
        x = que.front();
        que.pop();
        for (int i = 0; i < (int)graph[x].size(); i++)
        {
            int b = graph[x][i];
            if (!marked[b])
            {
                que.push(b);
                level[b] = level[x] + 1;
                marked[b] = true;
            }
        }
    }
    // display
    int temp = level[0];
    int index = 0;
    for (int i = 0; i < V; i++)
    {
        if (level[i] < temp)
        {
            temp = level[i];
            index = i;
        }
    }
    cout << index;
    while (temp < V)
    {
        temp++;
        for (int i = 0; i < V; i++)
        {
            if (level[i] == temp)
            {
                cout << " " << i;
            }
        }
    }
}

void bfs(vector<vector<int>> graph, int start)
{
    printLevels(graph, graph.size(), start);
}

int main()
{
    int init_graph[10][10] = {{0, 1, 1, 0, 1, 0, 1, 0, 1, 0},
                              {0, 0, 1, 1, 0, 0, 0, 1, 0, 0},
                              {0, 1, 0, 0, 0, 1, 1, 0, 1, 1},
                              {1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                              {0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
                              {1, 0, 1, 0, 1, 0, 0, 0, 1, 0},
                              {0, 0, 1, 1, 0, 1, 0, 0, 0, 0},
                              {1, 0, 0, 0, 0, 1, 1, 0, 1, 0},
                              {0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
                              {1, 0, 1, 0, 1, 0, 0, 0, 1, 0}};
    int n = 10;
    vector<vector<int>> graph(n, vector<int>());
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (init_graph[i][j])
                graph[i].push_back(j);
        }
    }

    bfs(graph, 0);
    return 0;
}