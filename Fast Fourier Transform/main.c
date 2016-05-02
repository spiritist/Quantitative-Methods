#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include "nr/nrutil.h"
#include "nr/nr.h"
int N=256, NN=2*256;
double F(double x)
{
    int i,M=25;
    double y,a=2,m=2;
    y=sin(2*M_PI*x);
    for (i=1; i<=M; i++)
        {
            y+=a*sin(2*M_PI*16*m*x);
            a*=-1.2;
            m*=1.4;
        }
    return y;
}
int main()
{
    int i,k;
    double t,*data;
    data=vector(0,NN);
    FILE *f_out1, *f_out2,*f_out3;
    f_out1=fopen("Original.txt","w");
    f_out2=fopen("spoiled.txt","w");
    f_out3=fopen("corrected.txt","w");
    for(t=0; t<=6.28; t+=0.05)
        {
            fprintf(f_out1,"%le %le\n",t, sin(2*M_PI*t));
            fprintf(f_out2,"%le %le\n",t, F(t));
        }
    for (i=1; i<=NN; i+=2)
        {
           // data[i]=F(0.03125*i-0.03125);
            data[i]=F(0.0078125*(i));
            data[i+1]=0.0;
          //  printf(" %lf ", data[i]);
        }
        dfour1(data,N,1);
        for (i=1; i<=NN; i++)
        {
          if(i!=9 && i!=10 && i!=NN-7 && i!=NN-6)
              data[i]=0;
        }
        dfour1(data,N,-1);
        printf("\n");
        for(i=1; i<=NN; i+=2)
        {
            fprintf(f_out3,"%le %le\n",0.0078125*(i), data[i]/N);
        }
        for (i=1; i<NN; i+=2)
            printf(" %lf ", data[i]/N);
    return 0;
}
