#include "Floating_Point.h"





int main()
{

	float var1 = 32.423;
	float var2 = 4.23;

	Floating_Point<11, 52> a(var1);
	Floating_Point<11, 52> q(var2);
	a = a.Log(a, q);

	cout << " Log(x1,x2) :" << endl << endl;
	cout << "My log: " << a.D.f << endl << endl;
	cout << "Real log: " << logf(var1) / logf(var2) << endl << endl << endl;



	Floating_Point<11, 52> v1(123.231);

	float f1 = logf(123.231);
	Floating_Point<11, 52> ch1(f1);

	v1 = v1.Log2(v1);

	cout << " Log2 :" << endl << endl;
	cout << "My log: " << v1.D.f << endl << endl;
	cout << "Real log: " << log2f(123.231) << endl << endl << endl;
	if ((v1.D.man == ch1.D.man) && (v1.D.ex == ch1.D.ex) && (v1.D.ex == ch1.D.ex)) cout << "They equal" << endl;
	else cout << "They not equal" << endl;


	Floating_Point<11, 52> v2(123.231);

	float f2 = logf(123.231);
	Floating_Point<11, 52> ch2(f2);

	v2 = v2.Log10(v2);

	cout << " Log10 :" << endl << endl;
	cout << "My log: " << v2.D.f << endl << endl;
	cout << "Real log: " << log10f(123.231) << endl << endl << endl;
	if ((v2.D.man == ch2.D.man) && (v2.D.ex == ch2.D.ex) && (v2.D.ex == ch2.D.ex)) cout << "They equal" << endl;
	else cout << "They not equal" << endl;


	Floating_Point<11, 52> v3(123.231);

	float f3 = logf(123.231);
	Floating_Point<11, 52> ch3(f3);

	v3 = v3.LogE(v3);

	cout << " LogE :" << endl << endl;
	cout << "My log: " << v3.D.f << endl << endl;
	cout << "Real log: " << logf(123.231) << endl << endl << endl;
	if ((v3.D.man == ch3.D.man) && (v3.D.ex == ch3.D.ex) && (v3.D.ex == ch3.D.ex)) cout << "They equal" << endl;
	else cout << "They not equal" << endl;



	double dl = 3.2345;
	Floating_Point<11, 52> v4(dl);

	double f4 = exp(dl);
	Floating_Point<11, 52> ch4(f4);

	v4 = v4.exp_function(100000);

	cout << " exp :" << endl << endl;
	cout << "My exp: " << v4.D.f << endl << endl;
	cout << "Real exp: " << ch4.D.f << endl << endl << endl;
	if (v4.D.f==ch4.D.f) cout << "They equal" << endl;
	else cout << "They not equal" << endl;
}
