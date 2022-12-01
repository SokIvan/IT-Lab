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





const unsigned int DIV_2_ON_PI[]
{
	2734261102 >> 1,
	1313084713 >> 1,
	4230436817 >> 1,
	4113882560 >> 1,
	3680671129 >> 1,
	1011060801 >> 1,
	4266746795 >> 1,
	3736847713 >> 1,
	3072618042 >> 1,
	1112396512 >> 1,
	105459434 >> 1,
	164729372 >> 1,
	4263373596 >> 1,
	2972297022 >> 1,
	3900847605 >> 1,
	784024708 >> 1,
	3919343654 >> 1,
	3026157121 >> 1,
	965858873 >> 1,
	2203269620 >> 1,
	2625920907 >> 1,
	3187222587 >> 1,
	536385535 >> 1,
	3724908559 >> 1,
	4012839307 >> 1,
	1510632735 >> 1,
	1832287951 >> 1,
	667617719 >> 1,
	1330003814 >> 1,
	2657085997 >> 1,
	1965537991 >> 1,
	235 >> 1
};




bool check_bit(const unsigned int digit,int number)
{
	return !((digit>>number)%2==0);
}



template<int e, int m>
void PAYNE_HANEK(Floating_Point<e, m>& x, int &znak)
{
	unsigned int M[4] = {0,0,0,0}, p = 50, j = (x.D.ex - m - 1), i = j % 32, jk = j,J=0,umn = 2<<(i-1);
	int i2 = 0;
	Floating_Point<e, m> PI4X = 0,k, X = x / pow(2, int((-1)*x.D.ex + m - 1));
	while (jk < (x.D.ex + m + 1 + p))
	{
		for (; i < 32 && jk < (x.D.ex + m + 1 + p); i++,jk++,i2++)
		{
			M[J] += umn*check_bit(DIV_2_ON_PI[jk/32],32-i);
			PI4X = PI4X + check_bit(DIV_2_ON_PI[jk / 32], 32 - i)*pow(2, int((-1)*i2));
			umn >>= 1;
		}
		umn = 2 << 30;
		J++;
		i = 0;
	}
	
	PI4X = PI4X * X * pow(2,(-2.0)*m-p);
	cout << pow(2, int((-1) * x.D.ex - 1023 + m - 1)) << " ";
	znak = FLOOR(PI4X)%4;
	x = (PI4X - FLOOR(PI4X))*M_PI/4;
}

















template<int e,int m>
void redo_sin_cos(Floating_Point<e,m> &for_sin, Floating_Point<e,m> &for_cos, Floating_Point<e,m> x,int znak)
{
	
	Floating_Point<e, m> last_sin, last_cos, next_sin, next_cos;


	last_sin = x*(-1.0)*(znak==3||znak==4)+x*(znak==1||znak==2);
	last_cos = 1.0 * (znak==1||znak==4) + (-1.0)*(znak==2||znak==3);
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
	int znak;
	PAYNE_HANEK(x, znak);
	int i = int(x.D.f * LuT[17] + 4);
	Floating_Point<e, m> msin, mcos,Sign(xLuT[i]),y;
	y = x - xLuT[i];
	redo_sin_cos(msin,mcos,y,znak);
	return msin * LuT[i + 8] - mcos * LuT[i] * ~int((Sign.D.sign * (-2)));
}
template<int e, int m>
Floating_Point<e, m> MY_COS(Floating_Point<e, m>& x)
{
	int znak;
	PAYNE_HANEK(x, znak);
	int i = int(x.D.f * LuT[17] + 4);
	Floating_Point<e, m> msin, mcos, Sign(xLuT[i]),y;
	y = x - xLuT[i];
	redo_sin_cos(msin, mcos, y,znak);
	return mcos * LuT[i+8] + msin * LuT[i] * ~int((Sign.D.sign * (-2)));
}
