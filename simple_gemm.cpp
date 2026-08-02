#include "gemm.h"

using namespace std;

void simpleGEMM(
    const vector<vector<int>>& A,
    const vector<vector<int>>& B,
    vector<vector<int>>& C)
{
    int M = A.size();
    int K = A[0].size();
    int N = B[0].size();

    for(int i=0;i<M;i++)
    {
        for(int j=0;j<N;j++)
        {
            C[i][j]=0;

            for(int k=0;k<K;k++)
            {
                C[i][j]+=A[i][k]*B[k][j];
            }
        }
    }
}