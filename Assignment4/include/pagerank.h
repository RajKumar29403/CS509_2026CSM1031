#ifndef PAGERANK_H
#define PAGERANK_H

#include "csr_graph.h"

#include <vector>

using namespace std;

class PageRank
{
private:
    CSRGraph graph;

    double dampingFactor;
    double tolerance;
    int maxIterations;

    int iterationsUsed;
    bool converged;

public:
    PageRank(const CSRGraph& g,
             double damping,
             double tol,
             int maxIter);

    vector<double> compute();

    int getIterationsUsed() const;

    bool hasConverged() const;
};

#endif