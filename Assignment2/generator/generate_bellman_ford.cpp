#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cstdlib>
#include <ctime>

using namespace std;

void generateGraph(string filename, int V, int targetEdges)
{
    ofstream fout(filename);

    if (!fout)
    {
        cout << "Cannot create " << filename << endl;
        return;
    }

    vector<vector<pair<int,int>>> adj(V);

    set<pair<int,int>> usedEdges;

    int E = 0;

    // Different random seed for each graph
    srand(time(NULL) + V);

    // ----------------------------
    // Step 1 : Create a chain
    // ----------------------------

    for (int i = 0; i < V - 1; i++)
    {
        int weight = rand() % 15 + 1;

        // Around 10% negative edges
        if (rand() % 10 == 0)
            weight = -(rand() % 5);

        adj[i].push_back({i + 1, weight});

        usedEdges.insert({i, i + 1});

        E++;
    }

    // ----------------------------
    // Step 2 : Add random edges
    // ----------------------------

    while (E < targetEdges)
    {
        int u = rand() % V;
        int v = rand() % V;

        if (u == v)
            continue;

        if (usedEdges.count({u, v}))
            continue;

        usedEdges.insert({u, v});

        int weight = rand() % 20 + 1;

        if (rand() % 12 == 0)
            weight = -(rand() % 5);

        adj[u].push_back({v, weight});

        E++;
    }

    // ----------------------------
    // Write graph
    // ----------------------------

    fout << V << " " << E << endl;

    for (int i = 0; i < V; i++)
    {
        fout << i << " " << adj[i].size();

        for (auto edge : adj[i])
        {
            fout << " "
                 << edge.first
                 << " "
                 << edge.second;
        }

        fout << endl;
    }

    fout << "SOURCE 0" << endl;

    fout.close();

    cout << filename << " created successfully." << endl;
}

int main()
{
    // V, Target Edges

    generateGraph("input/bellman_ford/bf_10.txt",
                  10,
                  20);

    generateGraph("input/bellman_ford/bf_100.txt",
                  100,
                  300);

    generateGraph("input/bellman_ford/bf_10000.txt",
                  10000,
                  25000);

    generateGraph("input/bellman_ford/bf_50000.txt",
                  50000,
                  120000);

    generateGraph("input/bellman_ford/bf_100000.txt",
                  100000,
                  250000);

    cout << "\nAll Bellman-Ford test files generated successfully.\n";

    return 0;
}