#ifndef PAGERANK_H
#define PAGERANK_H

#include <vector>

using namespace std;

struct CSRGraph
{
    int V;
    int E;

    vector<int> row_ptr;
    vector<int> col_idx;
};

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