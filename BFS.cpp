#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

class Graph
{
public:
    map<int, bool> visited;
    map<int, list<int>> adjacencyList;

    // function to add an edge to the graph
    void addEdge(int v, int w);

    // BFS traversal of the vertices reachable from v
    void breadthFirstTraversal(int v);
};

void Graph::addEdge(int v, int w)
{
    adjacencyList[v].push_back(w); // Add w to v's list.
}

void Graph::breadthFirstTraversal(int v)
{
    queue<int> queue;
    visited[v] = true;
    queue.push(v);

    while (!queue.empty())
    {
        v = queue.front(); // Get the front element of the queue
        cout << v << " "; // Print the current vertex
        queue.pop(); // Remove the front element from the queue

        #pragma omp parallel
        for (auto it = adjacencyList[v].begin(); it != adjacencyList[v].end(); ++it)
        {
            if (!visited[*it]) // Check if the neighbor is not visited
            {
                visited[*it] = true; // Mark the neighbor as visited
                queue.push(*it); // Add the neighbor to the queue
            }
        }
    }
}

int main()
{
    omp_set_num_threads(4);
    int startVertex, edges;
    Graph graph;

    cout << "Enter the number of edges: ";
    cin >> edges;

    cout << "Enter the Vertex (format: vertex1 vertex2):" << endl;
    for (int i = 0; i < edges; i++)
    {
        int v, w;
        cin >> v >> w;
        graph.addEdge(v, w); // Add an edge to the graph
    }

    cout << "Enter the vertex to start the BFS traversal with: ";
    cin >> startVertex;

    cout << "\nBreadth First Traversal: \n";
    graph.breadthFirstTraversal(startVertex); // Perform breadth-first traversal
    cout << endl;

    return 0;
}
