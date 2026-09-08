#ifndef MST_H
#define MST_H

#include "../../Assignment 2/include/csr.h"
#include "../../Assignment 2/include/graph.h"

#include <vector>

using namespace std;

struct MSTEdge
{
    int u;
    int v;
    int weight;
};

struct MSTResult
{
    vector<MSTEdge> edges;
    long long totalWeight;
};

MSTResult kruskalMST(const Graph &graph, const CSR &csr);

MSTResult primMST(const Graph &graph, const CSR &csr);

#endif