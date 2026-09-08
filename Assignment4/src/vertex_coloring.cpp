#include "../include/vertex_coloring.h"

#include <algorithm>
#include <set>

using namespace std;

VertexColoring::VertexColoring(const CSRGraph& g)
{
    graph = g;
}

vector<int> VertexColoring::greedyWelshPowell()
{
    vector<pair<int,int>> degreeVertex;

    for(int v = 0; v < graph.V; v++)
    {
        int degree =
            graph.row_ptr[v + 1] -
            graph.row_ptr[v];

        degreeVertex.push_back({degree, v});
    }

    sort(
        degreeVertex.begin(),
        degreeVertex.end(),
        [](const pair<int,int>& a,
           const pair<int,int>& b)
        {
            if(a.first == b.first)
                return a.second < b.second;

            return a.first > b.first;
        }
    );

    vector<int> colors(graph.V, -1);

    for(auto &p : degreeVertex)
    {
        int vertex = p.second;

        set<int> usedColors;

        int start = graph.row_ptr[vertex];
        int end   = graph.row_ptr[vertex + 1];

        for(int i = start; i < end; i++)
        {
            int neighbour = graph.col_idx[i];

            if(colors[neighbour] != -1)
            {
                usedColors.insert(colors[neighbour]);
            }
        }

        int color = 0;

        while(usedColors.count(color))
        {
            color++;
        }

        colors[vertex] = color;
    }

    return colors;
}

bool VertexColoring::verifyColoring(
    const vector<int>& colors)
{
    for(int u = 0; u < graph.V; u++)
    {
        int start = graph.row_ptr[u];
        int end   = graph.row_ptr[u + 1];

        for(int i = start; i < end; i++)
        {
            int v = graph.col_idx[i];

            if(colors[u] == colors[v])
            {
                return false;
            }
        }
    }

    return true;
}

int VertexColoring::countColorsUsed(
    const vector<int>& colors)
{
    int maxColor = -1;

    for(int color : colors)
    {
        maxColor = max(maxColor, color);
    }

    return maxColor + 1;
}