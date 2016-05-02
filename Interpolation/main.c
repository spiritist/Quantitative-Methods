#include <stdio.h>
#include <stdlib.h>
#include "nr.h"
#include "nr/nrutil.h"
double F_n (double x)
{
    return 1/(1+x*x*25);
}
void intpol20(FILE *out2)
{
    int i;
    double b=0,db,a;
    double x[22],y[22];//
    for (i=0; i<21; i++)
        {
            x[i+1]=-1+0.1*i;
            y[i+1]=F_n(x[i+1]);
        }
    for (a=-1.0; a<=1; a+=0.02)
        {
            polint(x, y, 21, a, &b, &db);
            fprintf(out2,"%le %le\n",a,b);
        }
}
void intpol5(FILE *out3)
{
    int i;
    double b=0,db,a;
    double x[7],y[7];
    for (i=0; i<6; i++)
        {
            x[i+1]=-1+0.4*i;
            y[i+1]=F_n(x[i+1]);
        }
    for (a=-1.0; a<=1; a+=0.02)
        {
            polint(x, y, 6, a, &b, &db);
            fprintf(out3,"%le %le\n",a,b);
        }

}
void splaine(FILE *out5)
{
    int i;
    double b=0,a;
    double x[22],y[22],dy[22];//
    for (i=0; i<8; i++)
        {
            x[i+1]=20+20*i;
            //y[i+1]=F_n(x[i+1]);

        }
        y[1]=2.27; y[2]=2.24; y[3]=2.14; y[4]=2.09; y[5]=2.06; y[6]=2.03; y[7]=1.96; y[8]=1.89;
    spline(x,y,8,0,0,dy);
    for (a=0; a<=200; a+=1)
        {
            splint(x,y,dy,8,a,&b);
            fprintf(out5,"%le %le\n",a,b);
        }
}
void partint(FILE *out4)
{
    int i,j;
    double b=0,db,a;
    double x[5],y[5];//
    for (i=0; i<=18; i+=3)
        {
            for(j=i; j<=i+3; j++)
                {
                    x[j+1-i]=-1+0.1*j;
                    y[j+1-i]=F_n(x[j+1-i]);
                }
            for(a=i*0.1-1;a<(i+3)*0.1-1;a+=0.01)
            {
                polint(x, y, 4, a, &b, &db);
                fprintf(out4,"%le %le\n",a,b);
            }
        }

}
int main()
{
    double b=0,db;
    FILE *f_out1,*f_out2,*f_out3,*f_out4,*f_out5;
    f_out1=fopen("function.txt","w");
    f_out2=fopen("interpolationST20.txt","w");
    f_out3=fopen("interpolationST5.txt","w");
    f_out4=fopen("partinterpolation.txt","w");
    f_out5=fopen("splaine.txt","w");
    /////////////////////
    for(b=-1.0; b<=1; b+=0.02)
        fprintf(f_out1,"%le %le\n",b,F_n(b));
    fclose(f_out1);
    b=0;
    ////////////////////
    intpol20(f_out2);
    fclose(f_out2);
    intpol5(f_out3);
    fclose(f_out3);
    splaine(f_out5);
    fclose(f_out5);
    partint(f_out4);
    fclose(f_out4);
    return 0;
}
