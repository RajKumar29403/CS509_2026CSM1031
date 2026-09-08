#ifndef CSR_CONVERTER_H
#define CSR_CONVERTER_H

#include "csr_graph.h"
#include <vector>

using namespace std;

CSRGraph convertToCSR(const vector<vector<int>>& adj,
                      int V,
                      int E);

#endif