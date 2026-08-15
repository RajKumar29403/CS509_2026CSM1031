#include "../include/mst.h"

#include <algorithm>
#include <queue>
#include <numeric>
#include <climits>

using namespace std;


// ------------------------------------------------------------
// Disjoint Set Union (DSU)
// Used by Kruskal's algorithm to detect cycles.
// ------------------------------------------------------------
class DSU
{
private:
    vector<int> parent;
    vector<int> rankValue;

public:

    DSU(int n)
    {
        parent.resize(n);
        rankValue.assign(n, 0);

        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x)
    {
        if (parent[x] == x)
            return x;

        parent[x] = find(parent[x]);

        return parent[x];
    }

    bool unite(int a, int b)
    {
        int rootA = find(a);
        int rootB = find(b);

        if (rootA == rootB)
            return false;

        if (rankValue[rootA] < rankValue[rootB])
        {
            parent[rootA] = rootB;
        }
        else if (rankValue[rootA] > rankValue[rootB])
        {
            parent[rootB] = rootA;
        }
        else
        {
            parent[rootB] = rootA;
            rankValue[rootA]++;
        }

        return true;
    }
};


// ------------------------------------------------------------
// Kruskal's Algorithm
// ------------------------------------------------------------
MSTResult kruskalMST(const Graph &graph, const CSR &csr)
{
    MSTResult result;

    result.totalWeight = 0;

    vector<MSTEdge> edges;

    // Extract edges from CSR.
    //
    // Since the MST graph is undirected, every edge occurs
    // twice in the adjacency list:
    //
    // u -> v
    // v -> u
    //
    // We therefore keep only u < v so that each edge is
    // considered once.
    for (int u = 0; u < graph.V; u++)
    {
        int start = csr.row_ptr[u];
        int end = csr.row_ptr[u + 1];

        for (int i = start; i < end; i++)
        {
            int v = csr.col_idx[i];
            int weight = csr.values[i];

            if (u < v)
            {
                MSTEdge edge;

                edge.u = u;
                edge.v = v;
                edge.weight = weight;

                edges.push_back(edge);
            }
        }
    }

    // Sort edges according to increasing weight.
    sort(edges.begin(), edges.end(),
        [](const MSTEdge &a, const MSTEdge &b)
        {
            return a.weight < b.weight;
        });


    // Create DSU for cycle detection.
    DSU dsu(graph.V);


    // Process edges in increasing order of weight.
    for (const MSTEdge &edge : edges)
    {
        if (dsu.unite(edge.u, edge.v))
        {
            result.edges.push_back(edge);

            result.totalWeight += edge.weight;

            // MST contains exactly V - 1 edges.
            if (result.edges.size() == graph.V - 1)
                break;
        }
    }

    return result;
}


// ------------------------------------------------------------
// Prim's Algorithm
// ------------------------------------------------------------
MSTResult primMST(const Graph &graph, const CSR &csr)
{
    MSTResult result;

    result.totalWeight = 0;

    if (graph.V == 0)
        return result;


    // Stores the minimum edge that can connect a vertex
    // to the current MST.
    vector<int> minWeight(graph.V, INT_MAX);

    // Stores the parent of every vertex in the MST.
    vector<int> parent(graph.V, -1);

    // Tells whether a vertex has already been included.
    vector<bool> inMST(graph.V, false);


    // Min-priority queue.
    //
    // pair = {edge weight, vertex}
    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;


    // Assignment recommends vertex 0 as the starting vertex.
    minWeight[0] = 0;

    pq.push({0, 0});


    while (!pq.empty())
    {
        int currentWeight = pq.top().first;
        int u = pq.top().second;

        pq.pop();

        // Ignore a vertex if it has already been added.
        if (inMST[u])
            continue;

        inMST[u] = true;


        // If this is not the starting vertex, add the
        // edge that connected it to the MST.
        if (parent[u] != -1)
        {
            MSTEdge edge;

            edge.u = parent[u];
            edge.v = u;
            edge.weight = currentWeight;

            result.edges.push_back(edge);

            result.totalWeight += currentWeight;
        }


        // Traverse the neighbours of u using CSR.
        int start = csr.row_ptr[u];
        int end = csr.row_ptr[u + 1];

        for (int i = start; i < end; i++)
        {
            int v = csr.col_idx[i];
            int weight = csr.values[i];

            if (!inMST[v] && weight < minWeight[v])
            {
                minWeight[v] = weight;
                parent[v] = u;

                pq.push({weight, v});
            }
        }
    }

    return result;
}