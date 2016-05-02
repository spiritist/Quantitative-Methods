
#define FUNC(x) ((*func)(x))

#define float double

float trapzd(float (*func)(float), float a, float b, int n)
{
	float x,tnm,sum,del;
	static float s;
	int it,j,count=0;

	if (n == 1) {
		return (s=0.5*(b-a)*(FUNC(a)+FUNC(b)));
	} else {
		for (it=1,j=1;j<n-1;j++) it <<= 1;
		tnm=it;
		del=(b-a)/tnm;
		x=a+0.5*del;
		for (sum=0.0,j=1;j<=it;j++,x+=del){sum += FUNC(x);}
		printf(" %d ",it);
		s=0.5*(s+(b-a)*sum/tnm);
		return s;
	}
}
#undef FUNC
