#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include <vector>
#include "graph.h"
#include "csr.h"

using namespace std;

bool bellmanFord(Graph &graph,
                 CSR &csr,
                 int source,
                 vector<int> &distance);

#endif