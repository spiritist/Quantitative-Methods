#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "nr/nrutil.h"
#include "nr/nr.h"
int count=0;
double func(double x)
{
    count++;
	return exp(-x*x)*2/sqrt(M_PI);
}

int main()
{
    double a=0, b=5,i,s;
    FILE *f_out1, *f_out2, *f_out3,*f_out4;
    f_out1=fopen("trap_figure.txt","w");
    f_out2=fopen("simp_figure.txt","w");
    f_out3=fopen("romb_figure.txt","w");
    f_out4=fopen("an_figure.txt","w");
    for (i=a;i<=b;i+=0.1)
    {
        fprintf(f_out1,"%le %le\n",i,qtrap(func,a,i));
        fprintf(f_out2,"%le %le\n",i,qsimp(func,a,i));
        fprintf(f_out3,"%le %le\n",i,qromb(func,a,i));
    }
    count=0;
    s=qtrap(func,a,1);
    printf("number of using F(X) in qtap: %d\n ",count);
    count=0;
    s=qsimp(func,a,1);
    printf("number of using F(X) in qsimp: %d\n ",count);
    count=0;
    s=qromb(func,a,1);
    printf("number of using F(X) in qromb: %d\n ",count);
    return 0;
}
