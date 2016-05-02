#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "nr/nr.h"
#include "nr/nrutil.h"
void Mat_mpl (double **a, double **b, double **c, int N)
{
    int i,j,k;

    for (i=1; i<=N; i++)
        {
            for (j=1; j<=N; j++)
                for (k=1; k<=N; k++)
                    c[i][j]+=a[i][k]*b[k][j];
        }
}
void print(double **a,int N)
{

    int i,k;
    for(i=1; i<=N; i++)
        {
            for(k=1; k<=N; k++)
                printf("%4.1lf ",a[i][k]);
            printf("\n");
        }
    return;
}
void copyMat(double **a,double **c,int N)
{
    int i,k;
    for (i=1; i<=N; i++)
        for (k=1; k<=N; k++)
            c[k][i]=a[k][i];
}
void init_V(double *a,int N, double min, double max)
{
    int i;
    for(i=1; i<=N; i++)
        a[i]=rand()*(max-min)/RAND_MAX+min;
}
int main()
{
    double **K,*M,**Mn,**L,**C,*X,**B,*Kn,*Xz,*Vz,**invL,*W,**A,*Y,t;
    double d;
    int *indx;
    int k,i,j,rot,N=11;
    /////////
    indx=vector(1,N);
    K=matrix(0,N+1,0,N+1);
    Mn=matrix(0,N+1,0,N+1);
    L=matrix(0,N+1,0,N+1);
    C=matrix(0,N+1,0,N+1);
    invL=matrix(0,N+1,0,N+1);
    W=vector(0,N+1);
    A=matrix(0,N+1,0,N+1);
    B=matrix(0,N+1,0,N+1);
    Xz=vector(0,N+1);
    M=vector(0,N+1);
    Y=vector(0,N+1);
    Vz=vector(0,N+1);
    X=vector(0,N+1);
    Kn=vector(0,N+1);
    ///////
    FILE *f_out[4];
    f_out[1]=fopen("string1.txt","w");
    f_out[2]=fopen("string2.txt","w");
    f_out[3]=fopen("string3.txt","w");
    ///////
    init_V(M,N,0,3);
    init_V(Kn,N,0,3);
    init_V(Xz,N,0,3);
    init_V(Vz,N,0,3);
    for(i=1; i<=N; i++)
        for(j=1; j<=N; j++)
            {
                L[i][j]=0;
                Mn[i][j]=0;
                K[i][j]=0;
                A[i][j]=0;
                B[i][j]=0;
              //  W[i][j]=0;
                invL[i][j]=0;
                C[i][j]=0;
            }
    for(i=1; i<=N; i++)
        {
            L[i][i]=sqrt(M[i]);
            invL[i][i]=1/L[i][i];
        }
    for(i=1; i<=N-1; i++)
        {
            K[i][i]=Kn[i]+Kn[i+1];
            K[i][i+1]=-Kn[i+1];
            K[i+1][i]=K[i][i+1];
        }
    K[N][N]=Kn[N];
    Mat_mpl(invL,K,C,N);
    Mat_mpl(C,invL,C,N);
    jacobi(C,N,Y,B,&rot);
    Mat_mpl(invL,B,A,N);
    copyMat(A,B,N);
    for(i=1; i<=N; i++)
        W[i]=sqrt(Y[i]);
        ///////////
    double *alpha;
    alpha=dvector(1, N);
    double *beta;
    beta=dvector(1, N);
    for (i = 1; i <= N; i++)
    {
        alpha[i] = Xz[i];
        beta[i] = Vz[i];
    }
     ludcmp(B, N, indx, &d);
    lubksb(B, N, indx, alpha);
    lubksb(B, N, indx, beta);
      for (i = 1; i <= N; i++)
    {
        beta[i] = beta[i]/W[i];
    }

    for (i=1;i<=3;i++)
    {
        scanf("%d",&k);
        for (t = 0; t < 100; t += 0.01)
        {
            X[k]=0;
            for(j=1; j<=N; j++)
                X[k]+=alpha[j]*A[k][j]*cos(W[j]*t)+beta[j]*A[k][j]*sin(W[j]*t);
                fprintf(f_out[i], "%lf %lf\n", t, X[k]);
        }
    }
    return 0;
}
