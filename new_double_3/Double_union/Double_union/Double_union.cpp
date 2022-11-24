#include "SinCosFunc.h"





int main()
{
	double sup = -M_PI / 2.0 + M_PI / 17.0, pi2 = M_PI/2.0;
	Floating_Point<11, 52> a(sup), b(sup);

	double a1 = sin(sup), b1 = cos(sup);
	while (sup < pi2)
	{
		a = sup;
		b = sup;

		a = MY_SIN(a);
		b = MY_COS(b);

		a1 = sin(sup);
		b1 = cos(sup);

		cout << "Mysin: " << a.D.f << "  Real sin: " << a1 << endl;
		cout << "Mycos: " << b.D.f << "  Real cos: " << b1 << endl << "x = " << sup << endl << endl;
		sup += M_PI / 17.0;
	}



	Floating_Point<11, 52> x(-M_PI / 2.0 + M_PI / 17.0), y(-M_PI / 2.0 + M_PI / 17.0);

	x = MY_SIN(x);
	y = MY_COS(y);

	double x1 = sin(-M_PI / 2.0 + M_PI / 17.0), y1 = cos(-M_PI / 2.0 + M_PI / 17.0);

	cout << "Difference -|  sin:  " << x1 - x.D.f << "        cos:  " << y1 - y.D.f;
}
