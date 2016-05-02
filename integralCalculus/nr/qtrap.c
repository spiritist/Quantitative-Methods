#include <math.h>
#define EPS 1.0e-6
#define JMAX 60

double qtrap(double (*func)(double), double a, double b)
{
	double trapzd(double (*func)(double), double a, double b, int n);
	void nrerror(char error_text[]);
	int j,use;
	float s,olds=0.0;

	for (j=1;j<=JMAX;j++) {
		s=trapzd(func,a,b,j);
		if (j > 2)
			if (fabs(s-olds) < EPS*fabs(olds) ||
				(s == 0.0 && olds == 0.0)){ return s;}
		olds=s;
	}
	nrerror("Too many steps in routine qtrap");
	return 0.0;
}
#undef EPS
#undef JMAX
