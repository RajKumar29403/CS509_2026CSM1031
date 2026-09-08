#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <random>

using namespace std;

void generateGraph(int V, const string& filename)
{
    random_device rd;
    mt19937 gen(rd());

    int targetEdges = 3 * V;

    vector<set<int>> adj;

    adj.resize(V);

    uniform_int_distribution<> vertexDist(0, V - 1);

    while(targetEdges > 0)
    {
        int u = vertexDist(gen);
        int v = vertexDist(gen);

        if(u == v)
            continue;

        if(adj[u].count(v))
            continue;

        adj[u].insert(v);
        adj[v].insert(u);

        targetEdges--;
    }

    int E = 0;

    for(int i = 0; i < V; i++)
    {
        E += adj[i].size();
    }

    E /= 2;

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

    fout.close();

    cout << filename
         << " generated\n";
}

int main()
{
    generateGraph(10, "color_10.txt");
    generateGraph(100, "color_100.txt");
    generateGraph(10000, "color_10000.txt");
    generateGraph(50000, "color_50000.txt");
    generateGraph(100000, "color_100000.txt");

    return 0;
}