#include "SinCosFunc.h"





int main()
{
	double x = 423519356.523875687146;
	Floating_Point<11, 53> CO(x), SI(x);
	CO = MY_COS(CO);
	SI = MY_COS(SI);
	cout << "Mycos: " << CO.D.f << "   Realcos: " << cos(x) << endl;
	cout << "Mycsin: " << SI.D.f << "   Realsin: " << sin(x) << endl;
}
