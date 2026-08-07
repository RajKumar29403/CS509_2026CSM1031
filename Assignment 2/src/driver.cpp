#include "../include/graph.h"
#include "../include/csr.h"
#include "../include/bellman_ford.h"
#include "../include/floyd_warshall.h"

#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

const int INF = 1000000000;

int main()
{
    int choice;

    cout << "==============================\n";
    cout << "1. Bellman-Ford\n";
    cout << "2. Floyd-Warshall\n";
    cout << "==============================\n";

    cout << "Enter your choice : ";
    cin >> choice;

    string filename;

    cout << "Enter input file : ";
    cin >> filename;

    if(choice == 1)
    {
        Graph graph;
        CSR csr;

        int source;

        if(!readAdjacencyList(filename, graph, source))
            return 0;

        // CSR conversion is preprocessing
        convertToCSR(graph, csr);

        vector<int> distance;

        auto start = high_resolution_clock::now();

        bool ok = bellmanFord(graph, csr, source, distance);

        auto stop = high_resolution_clock::now();

        auto duration =
        duration_cast<microseconds>(stop - start);

        cout << "\nAlgorithm : Bellman-Ford\n";
        cout << "Source : " << source << endl;

        if(!ok)
        {
            cout << "Negative cycle : true\n";
        }
        else
        {
            cout << "\nVertex\tDistance\n";

            for(int i=0;i<graph.V;i++)
            {
                cout << i << "\t";

                if(distance[i] == INF)
                    cout << "INF";
                else
                    cout << distance[i];

                cout << endl;
            }

            cout << "\nNegative cycle : none\n";
        }

        cout << "\nExecution Time : "
             << duration.count()
             << " microseconds\n";
    }

    else if(choice == 2)
    {
        vector<vector<int>> matrix;

        if(!readAdjacencyMatrix(filename, matrix))
            return 0;

        auto start = high_resolution_clock::now();

        bool ok = floydWarshall(matrix);

        auto stop = high_resolution_clock::now();

        auto duration =
        duration_cast<microseconds>(stop - start);

        cout << "\nAlgorithm : Floyd-Warshall\n";

        if(!ok)
        {
            cout << "Negative cycle : true\n";
        }
        else
        {
            cout << "\nDistance Matrix\n\n";

            for(int i=0;i<matrix.size();i++)
            {
                for(int j=0;j<matrix.size();j++)
                {
                    if(matrix[i][j] == INF)
                        cout << "INF ";
                    else
                        cout << matrix[i][j] << " ";
                }

                cout << endl;
            }

            cout << "\nNegative cycle : none\n";
        }

        cout << "\nExecution Time : "
             << duration.count()
             << " microseconds\n";
    }

    else
    {
        cout << "Invalid Choice\n";
    }

    return 0;
}