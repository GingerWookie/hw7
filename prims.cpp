#include <iostream>
using std::cout;
#include <vector>
using std::vector;
#include <utility>
using std::pair;
using std::make_pair;
#include <queue>
using std::priority_queue;
#include <functional>
using std::greater;
#include <climits>

void addEdges(vector<pair<int, int>> edges[], int vertex_one, int vertex_two, int weight)
{
    edges[vertex_one].push_back(make_pair(vertex_two, weight));
    edges[vertex_two].push_back(make_pair(vertex_one, weight));
}

void printPrim(vector<pair<int, int>> edges[], int vertex_amount, int source_vertex)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> weighted_queue;
    vector<int> weights(vertex_amount, INT_MAX);
    vector<int> tree(vertex_amount, -1);
    vector<bool> vertex_included(vertex_amount, false);
    int total_weight = 0;

    weighted_queue.push(make_pair(0,source_vertex));
    weights[source_vertex] = 0;

    while(!weighted_queue.empty())
    {
        int vertex = weighted_queue.top().second;
        weighted_queue.pop();

        vertex_included[vertex] = true;

        for(auto edge : edges[vertex])
        {
            int v = edge.first;
            int weight = edge.second;

            if(vertex_included[v] == false && weights[v] > weight)
            {
                weights[v] = weight;
                weighted_queue.push(make_pair(weights[v], v));
                tree[v] = vertex;
            }
        }
    }

    for(int i = 0; i < vertex_amount; ++i)
    {
        total_weight += weights[i];
        if(tree[i] == -1)
        {
            cout << "Vertex - " << i << " is the source vertex" << "\n";
            continue;
        }
        cout << "Vertex - " << i << " is attached via edge " << i << " - " << tree[i] << "\n";
    }
    cout << "Total Weight of Path is = " << total_weight << "\n";
}

int main()
{
    int vertex_amount = 10;
    int source_vertex = 9;
    vector<pair<int, int>> edges[vertex_amount];

    /*    GRAPH
            0
           / \
          1   2
         / \ / \
        3   4   5
       / \ / \ / \
      6   7   8   9
       \         /
        \-------/
    */
    addEdges(edges, 0, 1, 5);
    addEdges(edges, 0, 2, 2);
    addEdges(edges, 1, 3, 9);
    addEdges(edges, 1, 4, 1);
    addEdges(edges, 2, 4, 3);
    addEdges(edges, 2, 5, 6);
    addEdges(edges, 3, 6, 2);
    addEdges(edges, 3, 7, 2);
    addEdges(edges, 4, 7, 7);
    addEdges(edges, 4, 8, 5);
    addEdges(edges, 5, 8, 8);
    addEdges(edges, 5, 9, 1);
    addEdges(edges, 6, 9, 9);

    printPrim(edges, vertex_amount, source_vertex);
}
