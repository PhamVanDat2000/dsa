#include <iostream>
#include <list>
using namespace std;
class DirectedGraph
{
    int V;
    list<int> *adj;
    bool isCyclicUtil(int v, bool visited[], bool *rs)
    {
        if (visited[v] == false)
        {
            // Mark the current node as visited and part of recursion stack
            visited[v] = true;
            rs[v] = true;

            // Recur for all the vertices adjacent to this vertex
            list<int>::iterator i;
            for (i = adj[v].begin(); i != adj[v].end(); ++i)
            {
                if (!visited[*i] && isCyclicUtil(*i, visited, rs))
                    return true;
                else if (rs[*i])
                    return true;
            }
        }
        rs[v] = false; // remove the vertex from recursion stack
        return false;
    }

public:
    DirectedGraph()
    {
        V = 0;
        adj = NULL;
    }
    DirectedGraph(int V)
    {
        this->V = V;
        adj = new list<int>[V];
    }
    void addEdge(int v, int w)
    {
        adj[v].push_back(w);
    }
    bool isCyclic()
    {
        // // Student answer
        // bool *visited = new bool[V]{};
        // bool *recStack = new bool[V]{};
        bool *visited = new bool[V];
        bool *recStack = new bool[V];
        for (int i = 0; i < V; i++)
        {
            visited[i] = false;
            recStack[i] = false;
        }
        for (int i = 0; i < V; i++)
        {
            if (!visited[i] && isCyclicUtil(i, visited, recStack))
                return true;
        }
        return false;
    }
};
int main()
{
    DirectedGraph g(8);
    int edege[][2] = {{0, 6}, {1, 2}, {1, 4}, {1, 6}, {3, 0}, {3, 4}, {5, 1}, {7, 0}, {7, 1}};
    for (int i = 0; i < 9; i++)
        g.addEdge(edege[i][0], edege[i][1]);
    if (g.isCyclic())
        cout << "Graph contains cycle";
    else
        cout << "Graph doesn't contain cycle";
    return 0;
}