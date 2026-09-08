#include "../include/pagerank.h"

#include <cmath>
#include <numeric>

using namespace std;

PageRank::PageRank(const CSRGraph& g,
                   double damping,
                   double tol,
                   int maxIter)
{
    graph = g;
    dampingFactor = damping;
    tolerance = tol;
    maxIterations = maxIter;

    iterationsUsed = 0;
    converged = false;
}

vector<double> PageRank::compute()
{
    int N = graph.V;

    vector<double> rank(N, 1.0 / N);
    vector<double> newRank(N, 0.0);

    vector<int> outDegree(N);

    for(int u = 0; u < N; u++)
    {
        outDegree[u] =
            graph.row_ptr[u + 1] -
            graph.row_ptr[u];
    }

    for(int iter = 1; iter <= maxIterations; iter++)
    {
        fill(newRank.begin(),
             newRank.end(),
             (1.0 - dampingFactor) / N);

        double danglingContribution = 0.0;

        for(int u = 0; u < N; u++)
        {
            if(outDegree[u] == 0)
            {
                danglingContribution += rank[u];
            }
        }

        danglingContribution =
            dampingFactor *
            danglingContribution / N;

        for(int v = 0; v < N; v++)
        {
            newRank[v] += danglingContribution;
        }

        for(int u = 0; u < N; u++)
        {
            if(outDegree[u] == 0)
                continue;

            double contribution =
                dampingFactor *
                rank[u] /
                outDegree[u];

            int start = graph.row_ptr[u];
            int end   = graph.row_ptr[u + 1];

            for(int i = start; i < end; i++)
            {
                int v = graph.col_idx[i];

                newRank[v] += contribution;
            }
        }

        double totalChange = 0.0;

        for(int i = 0; i < N; i++)
        {
            totalChange +=
                fabs(newRank[i] - rank[i]);
        }

        rank = newRank;

        iterationsUsed = iter;

        if(totalChange <= tolerance)
        {
            converged = true;
            break;
        }
    }

    return rank;
}

int PageRank::getIterationsUsed() const
{
    return iterationsUsed;
}

bool PageRank::hasConverged() const
{
    return converged;
}