#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <random>

using namespace std;

void generateGraph(int V,
                   const string& filename)
{
    random_device rd;
    mt19937 gen(rd());

    int targetEdges = 4 * V;

    vector<set<int>> adj(V);

    uniform_int_distribution<> vertexDist(
        0,
        V - 1
    );

    while(targetEdges > 0)
    {
        int u = vertexDist(gen);
        int v = vertexDist(gen);

        if(u == v)
            continue;

        if(adj[u].count(v))
            continue;

        adj[u].insert(v);

        targetEdges--;
    }

    int E = 0;

    for(int i = 0; i < V; i++)
    {
        E += adj[i].size();
    }

    ofstream fout(filename);

    fout << V << " "
         << E
         << "\n";

    for(int i = 0; i < V; i++)
    {
        fout << i << " "
             << adj[i].size();

        for(int v : adj[i])
        {
            fout << " "
                 << v;
        }

        fout << "\n";
    }

    fout << 0.85 << "\n";
    fout << 1e-6 << "\n";
    fout << 100 << "\n";

    fout.close();

    cout << filename
         << " generated\n";
}

int main()
{
    generateGraph(10, "pagerank_10.txt");
    generateGraph(100, "pagerank_100.txt");
    generateGraph(1000, "pagerank_1000.txt");
    generateGraph(10000, "pagerank_10000.txt");
    generateGraph(50000, "pagerank_50000.txt");

    return 0;
}