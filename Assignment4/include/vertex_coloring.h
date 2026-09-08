#ifndef VERTEX_COLORING_H
#define VERTEX_COLORING_H

#include <vector>
#include <string>

using namespace std;

/*
CSR Graph Structure
row_ptr : size = V + 1
col_idx : size = number of edges stored
*/
struct CSRGraph
{
    int V;
    int E;

    vector<int> row_ptr;
    vector<int> col_idx;
};

class VertexColoring
{
private:
    CSRGraph graph;

    bool isValidColor(int vertex,
                      int color,
                      const vector<int>& colors);

public:
    VertexColoring(const CSRGraph& g);

    vector<int> greedyWelshPowell();

    bool verifyColoring(const vector<int>& colors);

    int countColorsUsed(const vector<int>& colors);
};

#endif