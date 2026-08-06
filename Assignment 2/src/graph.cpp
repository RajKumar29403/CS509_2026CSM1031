#include "../include/graph.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

bool readAdjacencyList(string filename, Graph &graph, int &source)
{
    ifstream fin(filename);

    if (!fin)
    {
        cout << "Unable to open file\n";
        return false;
    }

    fin >> graph.V >> graph.E;

    graph.adjList.resize(graph.V);

    string line;
    getline(fin, line);      // remove newline after E

    for (int i = 0; i < graph.V; i++)
    {
        getline(fin, line);

        stringstream ss(line);

        int vertex, degree;
        ss >> vertex >> degree;

        for (int j = 0; j < degree; j++)
        {
            int neighbour, weight;

            ss >> neighbour >> weight;

            Edge e;
            e.dest = neighbour;
            e.weight = weight;

            graph.adjList[vertex].push_back(e);
        }
    }

    string temp;
    fin >> temp >> source;

    fin.close();

    return true;
}

bool readAdjacencyMatrix(string filename, vector<vector<int>> &matrix)
{
    ifstream fin(filename);

    if (!fin)
    {
        cout << "Unable to open file\n";
        return false;
    }

    int V;
    fin >> V;

    matrix.resize(V, vector<int>(V));

    const int INF = 1000000000;

    string value;

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            fin >> value;

            if (value == "INF")
                matrix[i][j] = INF;
            else
                matrix[i][j] = stoi(value);
        }
    }

    fin.close();

    return true;
}