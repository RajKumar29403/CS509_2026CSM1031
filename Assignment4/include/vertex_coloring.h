#ifndef VERTEX_COLORING_H
#define VERTEX_COLORING_H

#include "csr_graph.h"

#include <vector>

using namespace std;

class VertexColoring
{
private:
    CSRGraph graph;

public:
    VertexColoring(const CSRGraph& g);

    vector<int> greedyWelshPowell();

    bool verifyColoring(const vector<int>& colors);

    int countColorsUsed(const vector<int>& colors);
};

#endif