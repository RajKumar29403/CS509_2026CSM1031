#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void generateMatrix(string filename, int V)
{
    ofstream fout(filename);

    if (!fout)
    {
        cout << "Cannot create " << filename << endl;
        return;
    }

    srand(time(NULL) + V);

    fout << V << endl;

    vector<vector<string>> matrix(V, vector<string>(V, "INF"));

    // Diagonal = 0
    for (int i = 0; i < V; i++)
        matrix[i][i] = "0";

    // Generate only forward edges (u < v)
    for (int i = 0; i < V; i++)
    {
        for (int j = i + 1; j < V; j++)
        {
            int chance = rand() % 100;

            // Around 35% of possible forward edges
            if (chance < 35)
            {
                int weight = rand() % 20 + 1;

                // Around 8% negative edges
                if (rand() % 12 == 0)
                    weight = -(rand() % 5);

                matrix[i][j] = to_string(weight);
            }
        }
    }

    // Write matrix
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            fout << matrix[i][j];

            if (j != V - 1)
                fout << " ";
        }

        fout << endl;
    }

    fout.close();

    cout << filename << " generated successfully.\n";
}

int main()
{
    generateMatrix("input/floyd_warshall/fw_10.txt",10);

    generateMatrix("input/floyd_warshall/fw_100.txt",100);

    generateMatrix("input/floyd_warshall/fw_500.txt",500);

    generateMatrix("input/floyd_warshall/fw_1000.txt",1000);

    generateMatrix("input/floyd_warshall/fw_2000.txt",2000);

    cout << "\nAll Floyd-Warshall input files generated successfully.\n";

    return 0;
}