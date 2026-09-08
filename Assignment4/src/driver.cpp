#include "../include/vertex_coloring.h"
#include "../include/pagerank.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

/*
    Replace this declaration with
    your Assignment 2 CSR converter.
*/
CSRGraph convertToCSR(
    const vector<vector<int>>& adj,
    int V,
    int E);

void runVertexColoring(const string& filename);
void runPageRank(const string& filename);

int main()
{
    int choice;

    cout << "==============================\n";
    cout << "Assignment 4\n";
    cout << "1. Vertex Coloring\n";
    cout << "2. PageRank\n";
    cout << "0. Exit\n";
    cout << "==============================\n";

    cin >> choice;

    if(choice == 0)
        return 0;

    string filename;

    cout << "Enter input file path : ";
    cin >> filename;

    switch(choice)
    {
        case 1:
            runVertexColoring(filename);
            break;

        case 2:
            runPageRank(filename);
            break;

        default:
            cout << "Invalid Choice\n";
    }

    return 0;
}