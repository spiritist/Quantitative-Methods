#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include "nr/nrutil.h"
#include "nr/nr.h"
double l=0.98, k=40,g=9.8, m=1;
void derivs0 (double t, double *y, double *dy)
{
    double Wf,Wl;
    Wl=k/m;
    Wf=g/l;
    dy[2]=y[4]*y[4]*(1+y[1])+Wf*(cos(y[3])-1)-Wl*y[1];
    dy[1]=y[2];
    dy[4]=-(Wf*sin(y[3])+2*y[2]*y[4])/(1+y[1]);
    dy[3]=y[4];
}
int main()
{
    double eps=1e-9, t0=0, t1, h,t,U,T;
    double y[5];
    int i, n=157, nok , nbad;
    FILE *f_out1,*f_out2, *f_out3, *f_out4;
    f_out1=fopen("LenghsCh.txt","w");
    f_out2=fopen("VerticalSh.txt","w");
    f_out3=fopen("Energy.txt","w");
    f_out4=fopen("PotEnergy.txt","w");
    y[1]=0.1; /// Z
    y[2]=0.2; /// dZ
    y[3]=M_PI/18;
    y[4]=0;
    h=6.28/n;
    while(t1<=6.28*6)//for(i=1; i<=n; i++)
        {
            t1=t0+h;
            odeint(y,4,t0,t1,eps,h,0.,&nok,&nbad,derivs0,rkqs);
           // if(t0>=0)
                fprintf(f_out1,"%le %le\n",t0, y[1]);
                fprintf(f_out2,"%le %le\n",t0, y[3]);
                U=-m*g*l*(1+y[1])*cos(y[3])+k/2*l*l*(m*g/(k*l)+y[1])*(m*g/(k*l)+y[1]);
                T=m/(2)*l*l*(y[2]*y[2]+(1+y[1])*(1+y[1])*y[4]*y[4]);
                fprintf(f_out3,"%le %le\n",t0, T+U);
                fprintf(f_out4,"%le %le\n",t0, U);
            t0=t1;
        }

        fclose(f_out1);
        fclose(f_out2);
}
