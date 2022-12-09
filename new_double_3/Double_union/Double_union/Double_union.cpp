#include "SinCosFunc.h"





int main()
{
	double x = 112342.25;
	Floating_Point<11, 53> CO(x), SI(x);
	CO = MY_COS(CO);
	SI = MY_COS(SI);
	cout << "Mycos: " << CO.D.f << "   Realcos: " << cos(x) << endl;
	cout << "Mycsin: " << SI.D.f << "   Realsin: " << sin(x) << endl;





}
