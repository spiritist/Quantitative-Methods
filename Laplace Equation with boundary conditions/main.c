#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int N=100;
double i=0.2;
void grid(double **p)
{
    int x,y,x1,x2,z=0;
    double eps=1e-7,d=0;
    x1=(int)N/2*(1-i);
    x2=(int)N/2*(1+i);
    while(fabs(p[1][1]-d)>eps)
        {
            for(x=1; x<N-1; x++)
                for(y=1; y<N-1; y++)
                    if(x>=x2 || x<=x1 || y>=x2 || y<=x1)
                        {
                            if(x==1 && y==1) d=p[x][y];
                            p[x][y]=(p[x+1][y]+p[x-1][y]+p[x][y+1]+p[x][y-1])/4;
                        }
                        z++;
        }
        printf("\n %d \n",z);
}
void print(double **a)
{
    int i,k;
    for(i=0; i<N; i++)
        {
            for(k=0; k<N; k++)
                printf("%-4.0lf ",a[i][k]);
            printf("\n");
        }
    printf("\n");
    return;
}

int main()
{
    double **p;
    double f2=100, f1=500;
    int x,y,x1,x2;
    FILE *f_out1;
    f_out1=fopen("potential.txt","w");
    ////////////////
    p=(double **)malloc(sizeof(double *)*(N+1));
    for(x=0; x<N+1; x++)
        p[x]=(double *)malloc(sizeof(double)*(N+2));
    for (x=0; x<N; x++)
        for(y=0; y<N; y++)
            p[x][y]=0;
    /////////////
    for (x=0; x<N; x++)
        {
            p[0][x]=f1;
            p[x][0]=f1;
            p[N-1][x]=f1;
            p[x][N-1]=f1;
        }
    x1=(int)N/2*(1-i);
    x2=(int)N/2*(1+i);
    for(x=1; x<N-1; x++)
        for(y=1; y<N-1; y++)
            {
                if((x<x2 && x>x1)&&(y<x2 &&y>x1))
                    p[x][y]=f2;
                else
                    p[x][y]=(f2+f1)/2;
            }
    grid(p);
  //  print(p);
    for (x=0; x<N; x++)
        for(y=0; y<N; y++)
            fprintf(f_out1,"%d %d %lf\n",x,y,p[x][y]);
 //   print(p);
    return 0;
}
