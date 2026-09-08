#include "../include/csr_graph.h"
#include "../include/csr_converter.h"
#include "../include/vertex_coloring.h"
#include "../include/pagerank.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;


void runVertexColoring(const string& filename);
void runPageRank(const string& filename);

int assignment4()
{
    int choice;

    while(true)
    {
        cout << "\n=====================================\n";
        cout << "           Assignment 4\n";
        cout << "=====================================\n";

        cout << "1. Vertex Coloring\n";
        cout << "2. PageRank\n";
        cout << "0. Back\n\n";

        cout << "Enter your choice : ";
        cin >> choice;

        if(choice == 0)
        {
            return 0;
        }

        string filename;

        cout << "Enter input file path : ";
        cin >> filename;

        switch(choice)
        {
            case 1:
                runVertexColoring(filename);
                break;

            case 2:
                runPageRank(filename);
                break;

            default:
                cout << "\nInvalid Choice\n";
        }
    }

    return 0;
}

void runVertexColoring(const string& filename)
{
    ifstream fin(filename);

    if(!fin)
    {
        cout << "\nCannot open file.\n";
        return;
    }

    int V, E;

    fin >> V >> E;

    vector<vector<int>> adj(V);

    for(int i = 0; i < V; i++)
    {
        int u;
        int degree;

        fin >> u >> degree;

        if(u < 0 || u >= V)
        {
            cout << "\nInvalid vertex id.\n";
            return;
        }

        if(degree < 0)
        {
            cout << "\nInvalid degree.\n";
            return;
        }

        adj[u].resize(degree);

        for(int j = 0; j < degree; j++)
        {
            fin >> adj[u][j];

            if(adj[u][j] < 0 || adj[u][j] >= V)
            {
                cout << "\nInvalid neighbour id.\n";
                return;
            }

            if(adj[u][j] == u)
            {
                cout << "\nSelf loop detected.\n";
                return;
            }
        }
    }

    fin.close();

    CSRGraph csr =
        convertToCSR(adj, V, E);

    VertexColoring coloring(csr);

    auto start =
        high_resolution_clock::now();

    vector<int> colors =
        coloring.greedyWelshPowell();

    auto stop =
        high_resolution_clock::now();

    auto duration =
        duration_cast<microseconds>(
            stop - start);

    bool valid =
        coloring.verifyColoring(colors);

    int colorsUsed =
        coloring.countColorsUsed(colors);

    cout << "\n========== RESULT ==========\n";
    cout << "Algorithm : Vertex Coloring\n";

    if(V <= 100)
    {
        cout << "\nVertex Colors\n";

        for(int i = 0; i < V; i++)
        {
            cout << "Vertex "
                 << i
                 << " -> Color "
                 << colors[i]
                 << "\n";
        }
    }

    cout << "\nColors Used : "
         << colorsUsed
         << "\n";

    cout << "Valid Coloring : "
         << (valid ? "Yes" : "No")
         << "\n";

    cout << "Execution Time : "
         << duration.count()
         << " us\n";
}

void runPageRank(const string& filename)
{
    ifstream fin(filename);

    if(!fin)
    {
        cout << "\nCannot open file.\n";
        return;
    }

    int V, E;

    fin >> V >> E;

    vector<vector<int>> adj(V);

    for(int i = 0; i < V; i++)
    {
        int u;
        int degree;

        fin >> u >> degree;

        if(u < 0 || u >= V)
        {
            cout << "\nInvalid vertex id.\n";
            return;
        }

        adj[u].resize(degree);

        for(int j = 0; j < degree; j++)
        {
            fin >> adj[u][j];

            if(adj[u][j] < 0 || adj[u][j] >= V)
            {
                cout << "\nInvalid neighbour id.\n";
                return;
            }
        }
    }

    double dampingFactor;
    double tolerance;
    int maxIterations;

    fin >> dampingFactor;
    fin >> tolerance;
    fin >> maxIterations;

    fin.close();

    CSRGraph csr =
        convertToCSR(adj, V, E);

    PageRank pageRank(
        csr,
        dampingFactor,
        tolerance,
        maxIterations
    );

    auto start =
        high_resolution_clock::now();

    vector<double> ranks =
        pageRank.compute();

    auto stop =
        high_resolution_clock::now();

    auto duration =
        duration_cast<microseconds>(
            stop - start);

    double rankSum = 0.0;

    cout << fixed
         << setprecision(6);

    cout << "\n========== RESULT ==========\n";
    cout << "Algorithm : PageRank\n";

    if(V <= 100)
    {
        cout << "\nPageRank Values\n";

        for(int i = 0; i < V; i++)
        {
            cout << "Vertex "
                 << i
                 << " -> "
                 << ranks[i]
                 << "\n";

            rankSum += ranks[i];
        }
    }
    else
    {
        for(double rank : ranks)
        {
            rankSum += rank;
        }
    }

    cout << "\nRank Sum : "
         << rankSum
         << "\n";

    cout << "Iterations : "
         << pageRank.getIterationsUsed()
         << "\n";

    cout << "Converged : "
         << (pageRank.hasConverged()
             ? "Yes"
             : "No")
         << "\n";

    cout << "Execution Time : "
         << duration.count()
         << " us\n";
}