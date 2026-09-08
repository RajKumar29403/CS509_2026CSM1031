#include<bits/stdc++.h>
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

int assignment1()
{
    int choice;
    cout << "\nSelect Test Case:\n";
    cout << "1. 2x2\n";
    cout << "2. 50x50\n";
    cout << "3. 100x100\n";
    cout << "4. 200x200\n";
    cout << "5. 500x500\n";
    cout << "Enter choice: ";
    cin >> choice;
    string filename;

switch(choice)
{
    case 1:
        filename = "gemm_test_01.txt";
        break;
    case 2:
        filename = "gemm_test_50x50.txt";
        break;
    case 3:
        filename = "gemm_test_100x100.txt";
        break;
    case 4:
        filename = "gemm_test_200x200.txt";
        break;
    case 5:
        filename = "gemm_test_500x500.txt";
        break;
    default:
        cout << "Invalid choice\n";
        return 1;
}

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