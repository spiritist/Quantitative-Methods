
#include <math.h>
#define EPS 1.0e-6
#define JMAX 100

double qsimp(double (*func)(double), double a, double b)
{
    double trapzd(double (*func)(double), double a, double b, int n);
	void nrerror(char error_text[]);
	int j;
	double s,st,ost=0.0,os=0.0;

	for (j=1;j<=JMAX;j++) {
		st=trapzd(func,a,b,j);
		s=(4.0*st-ost)/3.0; //printf(" %lf ",s);
		if (j > 2)
			if (fabs(s-os) < EPS*fabs(os) ||
				(s == 0.0 && os == 0.0)) { return s;}
		//printf("s=%e\tos=%e\tst=%e\tost=%e\n",s,os,st,ost);
		os=s;
		ost=st;
	}
	nrerror("Too many steps in routine qsimp");
	return 0;
}
#undef EPS
#undef JMAX
