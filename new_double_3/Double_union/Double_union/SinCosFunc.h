#include "Floating_Point.h"


double LuT[18] =
{
	sin(3 * M_PI / 8.0),
	sin(1 * M_PI / 4.0),
	sin(1 * M_PI / 8.0),
	0.0,
	0.0,
	sin(1 * M_PI / 8.0),
	sin(1 * M_PI / 4.0),
	sin(3 * M_PI / 8.0),
	cos(3 * M_PI / 8.0),
	cos(1 * M_PI / 4.0),
	cos(1 * M_PI / 8.0),
	1.0,
	1.0,
	cos(1 * M_PI / 8.0),
	cos(1 * M_PI / 4.0),
	cos(3 * M_PI / 8.0),
	10.0/M_PI,
	M_PI/2.0


};

double xLuT[8] =
{
	(-3)* M_PI / 8.0,
	(-1)* M_PI / 4.0,
	(-1)* M_PI / 8.0,
	0.0,
	0.0,
	1 * M_PI / 8.0,
	1 * M_PI / 4.0,
	3 * M_PI / 8.0,
};



template<int e, int m>
void PAYNE_HANEK(Floating_Point<e, m>& x)
{

}

template<int e,int m>
void redo_sin_cos(Floating_Point<e,m> &for_sin, Floating_Point<e,m> &for_cos, Floating_Point<e,m> x)
{
	
	Floating_Point<e, m> last_sin, last_cos, next_sin, next_cos;

	last_sin = x;
	last_cos = 1.0;
	for_sin = last_sin;
	for_cos = last_cos;
	
	for (int i = 1; i < 4; i++)
	{
		next_sin = x * x / (2.0 * i) / (2.0 * i + 1) * (-1.0);
		for_sin = MY_FMA(last_sin, next_sin, for_sin);
		last_sin = last_sin * next_sin;

		next_cos= x * x / (2.0 * i) / (2.0 * i - 1) * (-1.0);
		for_cos= MY_FMA(last_cos, next_cos, for_cos);
		last_cos = last_cos * next_cos;
	}
	

}

template<int e, int m>
Floating_Point<e, m> MY_SIN(Floating_Point<e,m> &x)
{
	int i = int(x.D.f * LuT[17] + 4);
	Floating_Point<e, m> msin, mcos,Sign(xLuT[i]),y;
	y = x - xLuT[i];
	redo_sin_cos(msin,mcos,y);
	return msin * LuT[i + 8] - mcos * LuT[i] * ~int((Sign.D.sign * (-2)));
}
template<int e, int m>
Floating_Point<e, m> MY_COS(Floating_Point<e, m>& x)
{
	int i = int(x.D.f * LuT[17] + 4);
	Floating_Point<e, m> msin, mcos, Sign(xLuT[i]),y;
	y = x - xLuT[i];
	redo_sin_cos(msin, mcos, y);
	return mcos * LuT[i+8] + msin * LuT[i] * ~int((Sign.D.sign * (-2)));
}

