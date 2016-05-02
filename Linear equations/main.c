#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "nr/nr.h"
#include "nr/nrutil.h"
//int N=3,M=4;
void init(double **c,int N, int M)
{
    double a=0,b=1;
    int i,k;
    for(i=1; i<=N; i++)
        for(k=1; k<=M; k++)
            c[i][k]=((rand()*(b-a)/RAND_MAX + a));
}
void print(double **a,int N, int M)
{
    int i,k;
    for(i=1; i<=N; i++)
        {
            for(k=1; k<=M; k++)
                printf("%4.1lf ",a[i][k]);
            printf("\n");
        }
    printf("\n");
    return;
}
void copyMat(double **a,double **c,int N)
{
    int i,k;
    for (i=1; i<=N; i++)
        for (k=1; k<=N; k++)
            c[k][i]=a[k][i];
}
void check(double **c, double *x, double *y,int N)
{
    int i,k;
    double b=0;
    printf("\nresult of using vector x :");
    for (i=1; i<=N; i++)
        {
            for (k=1; k<=N; k++)
                b+=(c[i][k]*x[k]);
            printf("% lf ",b);
            b=0;
        }
    printf("\nreal values of vector y : ");
    for (i=1; i<=N; i++)
        printf("% lf",y[i]);
}
int main()
{
    double **a,**c,**b;
    double *indx,*x,*y,d;
    int i,k,j,N,M;

    printf("write the number of strings\n" );
    scanf("%d",&N);
    printf("write the number of columns\n" );
    scanf("%d",&M);
    a=matrix(0,N+1,0,M+1);
    x=vector(0,N);
    y=vector(0,N);
    c=matrix(0,N+1,0,M+1);
    b=matrix(0,N+1,0,M+1);
    indx=ivector(0,N+1);

    init(a,N,M);
    printf("\nmatrix\n");
    print(a,N,M);
    copyMat(a,c,N);

    ludcmp(c,N,indx,&d);
    for (i=1; i<=N; i++)
        {
            x[i]=a[i][M];
            y[i]=x[i];
        }
    lubksb(c,N,indx,x);
    for (i=1; i<=N; i++)
        printf("sollution value %d: %lf \n",i, x[i]);
    copyMat(a,c,N);
    check(c,x,y,N);
    //inverse the matrix
    ludcmp(c,N,indx,&d);
    copyMat(a,b,N);
    for(k=1; k<=N; k++)
        {
            for(i=1; i<=N; i++) y[i]=0.0;
            y[k]=1.0;
            lubksb(c,N,indx,y);
            for(i=1; i<=N; i++) a[i][k]=y[i];
        }
    printf("\n\ninvert matrix\n");
    print(a,N,N);
    copyMat(b,c,N);
    for (i=1; i<=N; i++)
        for (k=1; k<=N; k++)
            b[i][k]=0;
    //print(c,N,N);
    //check
    for (i=1; i<=N; i++)
        {
            for (j=1; j<=N; j++)
                for (k=1; k<=N; k++)
                    b[i][j]+=(a[i][k]*c[k][j]);
        }
    printf("\nresult of using invert matrix on original\n");
    print(b,N,N);
    free_matrix(a,0,N,0,M);
    free_matrix(c,0,N,0,M);
    free_matrix(b,0,N,0,M);
    free_vector(x,0,N);
    return 0;
}

