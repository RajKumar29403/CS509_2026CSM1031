#include "../include/floyd_warshall.h"

using namespace std;

bool floydWarshall(vector<vector<int>> &dist)
{
    int V = dist.size();

    const int INF = 1000000000;

    for (int k = 0; k < V; k++)
    {
        for (int i = 0; i < V; i++)
        {
            if (dist[i][k] == INF)
                continue;

            for (int j = 0; j < V; j++)
            {
                if (dist[k][j] == INF)
                    continue;

                if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Check negative cycle
    for (int i = 0; i < V; i++)
    {
        if (dist[i][i] < 0)
            return false;
    }

    return true;
}