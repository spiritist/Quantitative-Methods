#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "nr/nr.h"
#include "nr/nrutil.h"
double m=1,k=1.38;
void Maxwell(double T,double v_min, double v_max)
{
    double v,f;
    FILE *f_out1;
    f_out1=fopen("Maxwell.txt","w");
    for (v=v_min; v<=v_max; v+=10)
        {
            f=sqrt(m/(2*M_PI*T*k))*exp(-m*v*v/(2*T*k));
            fprintf(f_out1,"%lf %lf\n", v, f);
        }
    fclose(f_out1);
}
double E(double v)
{
    return m*v*v/2;
}
void Creutz(double *Ed, double *v, int N)
{
    int i=1,k,j;
    double dv,dE,Vn, b=sqrt(*Ed),a=-b, E_dem=*Ed;
    for(j=1; j<=1000000000; j++)
        {
            dv=rand()*(b-a)/RAND_MAX+a;
            Vn=v[i];
            v[i]=v[i]+dv;
            dE=E(v[i])-E(Vn);
            if(dE<=0)
                E_dem=E_dem+fabs(dE);
            if(dE>0)
                if(E_dem>dE)
                    E_dem=E_dem-dE;
                else
                    v[i]=Vn;
            if (E_dem<=0.)
                printf("\n %lf \n", E_dem);
                if(i==N-1) i=1;
                i++;
        }
    if(i==0)
        dv=rand()*(b-a)/RAND_MAX+a;
    *Ed=E_dem;
}
main()
{
    int N=1000000,i,j,Nv=0,Nz=0;
    double T=3000,*v,E_dem,v_min=500,v_max=0,dv_p;
    FILE *f_out2;
    v=vector(0,N+1);
    f_out2=fopen("dem.txt","w");
    E_dem=k*T/2;
    for (i=0; i<=N; i++)
        v[i]=sqrt(E_dem*2/m);
    Creutz(&E_dem,v,N);
    printf("\n %lf ",E_dem);
    v[0]=sqrt(E_dem*2/m);
    for (i=0; i<=N; i++)
        {
            if(v[i]<v_min) v_min=v[i];
            if(v[i]>v_max) v_max=v[i];
        }
    printf("\n %lf %lf\n", v_min,v_max);
    Maxwell(T,v_min,v_max);
    dv_p=(v_max-v_min)/100;
    for (i=0; i<N/10000; i++)
        {
            Nv=0;
            for(j=1; j<N; j++)
                {
                    if(v[j]>=(v_min+(i-1)*dv_p) && v[j]<(v_min+i*dv_p))
                        Nv++;
                }
            fprintf(f_out2,"%lf %lf\n",v_min+(i-1/2)*dv_p, (double)Nv/(N*dv_p));
        }
    free_vector(v,0,N);
    return 0;
}

