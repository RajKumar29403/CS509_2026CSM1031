#include "../include/mst.h"
#include "../../Assignment 2/include/graph.h"
#include "../../Assignment 2/include/csr.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

bool readMSTInput(const string &filename, Graph &graph)
{
    ifstream fin(filename);
    if (!fin)
    {
        cout << "Unable to open file: " << filename << endl;
        return false;
    }

    int V, E;
    if (!(fin >> V >> E))
    {
        cout << "Invalid MST input file." << endl;
        return false;
    }

    if (V <= 0 || E < 0)
    {
        cout << "Invalid number of vertices or edges." << endl;
        return false;
    }

    graph.V = V;
    graph.E = E;

    graph.adjList.clear();
    graph.adjList.resize(V);


    for (int i = 0; i < V; i++)
    {
        int vertex;
        int degree;

        if (!(fin >> vertex >> degree))
        {
            cout << "Invalid adjacency list." << endl;
            return false;
        }

        if (vertex < 0 || vertex >= V)
        {
            cout << "Invalid vertex: " << vertex << endl;
            return false;
        }

        if (degree < 0)
        {
            cout << "Invalid degree for vertex "
                 << vertex << endl;
            return false;
        }


        for (int j = 0; j < degree; j++)
        {
            int neighbour;
            int weight;

            if (!(fin >> neighbour >> weight))
            {
                cout << "Invalid edge data for vertex "
                     << vertex << endl;
                return false;
            }

            if (neighbour < 0 || neighbour >= V)
            {
                cout << "Invalid neighbour: "
                     << neighbour << endl;
                return false;
            }

            Edge edge;

            edge.dest = neighbour;
            edge.weight = weight;

            graph.adjList[vertex].push_back(edge);
        }
    }

    fin.close();

    return true;
}

void printMSTResult(
    const string &algorithm,
    const MSTResult &result,
    double executionTime)
{
    cout << "\n=====================================\n";
    cout << "Algorithm: " << algorithm << "'s MST\n";
    cout << "=====================================\n";

    cout << "\nMST edges:\n";

    for (const MSTEdge &edge : result.edges)
    {
        cout << edge.u << " "
             << edge.v << " "
             << edge.weight << endl;
    }

    cout << "\nTotal MST weight: "
         << result.totalWeight << endl;

    cout << fixed << setprecision(6);

    cout << "Execution time: "
         << executionTime
         << " ms\n";
}

int assignment3()
{
    int choice;

    cout << "\n=====================================\n";
    cout << "          Assignment 3 - MST\n";
    cout << "=====================================\n";

    cout << "1. Kruskal's Algorithm\n";
    cout << "2. Prim's Algorithm\n";
    cout << "3. Run Both Algorithms\n";
    cout << "=====================================\n";

    cout << "Enter your choice: ";
    cin >> choice;


    if (choice < 1 || choice > 3)
    {
        cout << "\nInvalid Choice.\n";
        return 0;
    }


    string filename;

    cout << "Enter input file: ";
    cin >> ws;
    getline(cin, filename);
    
    Graph graph;

    if (!readMSTInput(filename, graph))
    {
        return 0;
    }

    CSR csr;

    convertToCSR(graph, csr);

    MSTResult kruskalResult;
    MSTResult primResult;

    double kruskalTime = 0.0;
    double primTime = 0.0;

    if (choice == 1 || choice == 3)
    {
        auto start = high_resolution_clock::now();

        kruskalResult = kruskalMST(graph, csr);

        auto stop = high_resolution_clock::now();

        kruskalTime =
            duration<double, milli>(stop - start).count();


        if (kruskalResult.edges.size() !=
            static_cast<size_t>(graph.V - 1))
        {
            cout << "\nGraph is not connected."
                 << endl;

            return 0;
        }


        printMSTResult(
            "Kruskal",
            kruskalResult,
            kruskalTime
        );
    }

    if (choice == 2 || choice == 3)
    {
        auto start = high_resolution_clock::now();

        primResult = primMST(graph, csr);

        auto stop = high_resolution_clock::now();

        primTime =
            duration<double, milli>(stop - start).count();


        if (primResult.edges.size() !=
            static_cast<size_t>(graph.V - 1))
        {
            cout << "\nGraph is not connected."
                 << endl;

            return 0;
        }


        printMSTResult(
            "Prim",
            primResult,
            primTime
        );
    }

    if (choice == 3)
    {
        cout << "\n=====================================\n";
        cout << "           MST Comparison\n";
        cout << "=====================================\n";

        cout << "Kruskal total weight: "
             << kruskalResult.totalWeight
             << endl;

        cout << "Prim total weight:    "
             << primResult.totalWeight
             << endl;


        if (kruskalResult.totalWeight ==
            primResult.totalWeight)
        {
            cout << "\nTotal weights equal: Yes\n";
            cout << "Status: PASS\n";
        }
        else
        {
            cout << "\nTotal weights equal: No\n";
            cout << "Status: FAIL\n";
        }
        cout << fixed << setprecision(6);
        cout << "\nKruskal execution time: "
             << kruskalTime
             << " ms\n";

        cout << "Prim execution time:    "
             << primTime
             << " ms\n";
    }
    return 0;
}