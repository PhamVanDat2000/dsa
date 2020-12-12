#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <map>
#include <vector>
#include <set>
using namespace std;
struct Graph
{
    int V, E;
    vector<pair<int, pair<int, int>>> edges;
    // Constructor
    Graph(int V, int E)
    {
        this->V = V;
        this->E = E;
    }
    void addEdge(int u, int v, int w)
    {
        edges.push_back({w, {u, v}});
    }
    //YOUR CODE HERE
    // Some helping functions
    int kruskalMST()
    {
        // TODO: return weight of the minimum spanning tree.
        edges[1];
    }
};
int main()
{
    int V = 2, E = 1;
    Graph g(V, E);
    g.addEdge(0, 1, 2);

    cout << g.kruskalMST();
}
