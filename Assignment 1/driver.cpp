#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

#include "gemm.h"

using namespace std;
using namespace chrono;

void printMatrix(const vector<vector<int>>& C)
{
    for(auto row : C)
    {
        for(auto x : row)
            cout << x << " ";

        cout << endl;
    }
}

int main()
{
    string filename;

    cout<<"Enter input file name : ";
    cin>>filename;

    ifstream fin(filename);

    if(!fin)
    {
        cout<<"Cannot open file.\n";
        return 0;
    }

    int M,K,N;

    fin>>M>>K>>N;

    vector<vector<int>> A(M,vector<int>(K));
    vector<vector<int>> B(K,vector<int>(N));

    for(int i=0;i<M;i++)
        for(int j=0;j<K;j++)
            fin>>A[i][j];

    for(int i=0;i<K;i++)
        for(int j=0;j<N;j++)
            fin>>B[i][j];

    fin.close();

    vector<vector<int>> C1(M,vector<int>(N));
    vector<vector<int>> C2(M,vector<int>(N));

    //-------------------------
    // Simple GEMM
    //-------------------------

    auto start=high_resolution_clock::now();

    simpleGEMM(A,B,C1);

    auto stop=high_resolution_clock::now();

    auto duration=duration_cast<microseconds>(stop-start);

    cout<<"\n===== Simple GEMM =====\n";

    printMatrix(C1);

    cout<<"Execution Time : "
        <<duration.count()
        <<" microseconds\n";

    //-------------------------
    // Blocking GEMM
    //-------------------------

    int blockSize=32;

    start=high_resolution_clock::now();

    blockedGEMM(A,B,C2,blockSize);

    stop=high_resolution_clock::now();

    duration=duration_cast<microseconds>(stop-start);

    cout<<"\n===== Blocking GEMM =====\n";

    printMatrix(C2);

    cout<<"Execution Time : "
        <<duration.count()
        <<" microseconds\n";

    return 0;
}