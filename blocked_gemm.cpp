#include "gemm.h"

using namespace std;

void blockedGEMM(
    const vector<vector<int>>& A,
    const vector<vector<int>>& B,
    vector<vector<int>>& C,
    int BS)
{
    int M=A.size();
    int K=A[0].size();
    int N=B[0].size();

    for(int i=0;i<M;i++)
        for(int j=0;j<N;j++)
            C[i][j]=0;

    for(int ii=0;ii<M;ii+=BS)
    {
        for(int jj=0;jj<N;jj+=BS)
        {
            for(int kk=0;kk<K;kk+=BS)
            {
                for(int i=ii;i<min(ii+BS,M);i++)
                {
                    for(int j=jj;j<min(jj+BS,N);j++)
                    {
                        for(int k=kk;k<min(kk+BS,K);k++)
                        {
                            C[i][j]+=A[i][k]*B[k][j];
                        }
                    }
                }
            }
        }
    }
}