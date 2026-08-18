#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <random>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> sizes = {
        10,
        100,
        10000,
        50000,
        100000
    };
    mt19937 rng(20260815);
    for (int V : sizes)
    {
        int E = 2 * V;
        cout << "\nGenerating mst_"
             << V << ".txt ..." << endl;
        set<pair<int, int>> edges;
        for (int u = 0; u < V; u++)
        {
            int v = (u + 1) % V;

            if (u != v)
            {
                int a = min(u, v);
                int b = max(u, v);

                edges.insert({a, b});
            }
        }
        uniform_int_distribution<int> vertexDist(0, V - 1);
        while ((int)edges.size() < E)
        {
            int u = vertexDist(rng);
            int v = vertexDist(rng);

            if (u == v)
                continue;

            int a = min(u, v);
            int b = max(u, v);

            edges.insert({a, b});
        }
        vector<vector<pair<int, int>>> adj(V);
        uniform_int_distribution<int> weightDist(1, 100);
        for (auto edge : edges)
        {
            int u = edge.first;
            int v = edge.second;

            int weight = weightDist(rng);

            adj[u].push_back({v, weight});
            adj[v].push_back({u, weight});
        }
        for (int u = 0; u < V; u++)
        {
            sort(adj[u].begin(), adj[u].end());
        }
        string filename =
            "Assignment 3/input/mst/mst_" +
            to_string(V) +
            ".txt";
        ofstream fout(filename);
        if (!fout)
        {
            cout << "Error creating file: "
                 << filename << endl;

            return 1;
        }
        fout << V << " " << E << "\n";
        for (int u = 0; u < V; u++)
        {
            fout << u << " "
                 << adj[u].size();

            for (auto edge : adj[u])
            {
                int neighbour = edge.first;
                int weight = edge.second;

                fout << " "
                     << neighbour
                     << " "
                     << weight;
            }

            fout << "\n";
        }
        fout.close();
        cout << "Created: "
             << filename
             << " | V = " << V
             << " | E = " << E
             << endl;
    }
    cout << "\nAll MST input files generated successfully."
         << endl;
    return 0;
}