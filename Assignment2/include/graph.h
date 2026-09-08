#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

using namespace std;

struct Edge
{
    int dest;
    int weight;
};

struct Graph
{
    int V;      
    int E;      
    vector<vector<Edge>> adjList;
};

bool readAdjacencyList(const string &filename, Graph &graph, int &source);

bool readAdjacencyMatrix(const string &filename,
                         vector<vector<int>> &matrix);

#endif