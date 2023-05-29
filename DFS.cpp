#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

class Graph
{
public:
    map<int, bool> visited;
    map<int, list<int>> adj;

    // function to add an edge to the graph
    void addEdge(int v, int w);

    // DFS traversal of the vertices reachable from v
    void DFS(int v);
};

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v's list.
}

void Graph::DFS(int v)
{
    visited[v] = true; // Mark the current node as visited
    cout << v << " "; // Print the current node

    // Recur for all the vertices adjacent to this vertex
    #pragma omp parallel
    for (auto i = adj[v].begin(); i != adj[v].end(); ++i)
    {
        if (!visited[*i]) // If the adjacent vertex is not visited, recursively call DFS on it
        {
            DFS(*i);
        }
    }
}

int main()
{
    omp_set_num_threads(4); // Set the number of threads to use
    int z, edges;
    Graph g;

    cout << "Enter the number of edges: ";
    cin >> edges;

    cout << "Enter the edges (format: vertex1 vertex2):" << endl;
    for (int i = 0; i < edges; i++)
    {
        int v, w;
        cin >> v >> w;
        g.addEdge(v, w); // Add the edge to the graph
    }

    cout << "Enter the vertex to start the DFS traversal with: ";
    cin >> z;

    cout << "\nDepth First Traversal: \n";
    double startTime = omp_get_wtime();
    g.DFS(z); // Perform DFS traversal starting from the given vertex
    double endTime = omp_get_wtime();
    cout << endl;
    cout<<"Total Time Taken "<< endTime - startTime<<" sec"<<endl;
    return 0;
}
