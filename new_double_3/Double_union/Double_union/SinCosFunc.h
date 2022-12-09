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












unsigned int f(unsigned int x)
{
	x = x & 0x0000ffff;
	return x;
}

unsigned int c(unsigned int x)
{
	x = (x & 0xffff0000) >> 32;
	return x;
}




template<int e, int m>
void PAYNE_HANEK(Floating_Point<e, m>& x, int &znak)
{
	
	unsigned int M[4] = { 0,0,0,0 }, XMas[2] = {0,0}, p = 50, j = (x.D.ex - m - 1), i = j % 32, jk = j, J = 0, umn = 2 << (i - 1);
	int i2 = 0;
	Floating_Point<e, m> PI4X = 0,k, X = x / pow(2, int(x.D.ex - m - 1));
	while (jk < (x.D.ex + m + 1 + p))
	{
		for (; i < 32 && jk < (x.D.ex + m + 1 + p); i++,jk++,i2++)
		{
			M[J] += umn*check_bit(DIV_2_ON_PI[jk/32],32-i);
			
			umn >>= 1;
		}
		umn = 2 << 30;
		J++;
		i = 0;
	}
	umn = 2 << 30;
	for (i = 0; i < 32; i++)
	{
		XMas[0] += umn * check_bit(X.D.man, 32 - i);
		umn >>= 1;
	}
	umn = 2 << 30;
	for (i = 0; i < 32; i++)
	{
		XMas[1] += umn * check_bit(X.D.man<<32, 32 - i);
		umn >>= 1;
	}
	
	



	Floating_Point<e, m> xM;


//	X= x1 * 2^32   + x2

	unsigned int x1 = XMas[0];
	unsigned int x2 = XMas[1];
	unsigned int k1 = x1 * M[1];
	unsigned int k2 = (M[1] * x1 + M[0] * x2);
	unsigned int k3 = (M[2] * x1 + M[1] * x2);
	unsigned int k4 = (M[3] * x1 + M[2] * x2);
	unsigned int k5 = M[3] * x2;

	cout << pow(2, int((-1)*x.D.ex + m + 1)) << endl;
	cout << "k1= " << k1 << endl << "k2= " << k2 << endl << "k3= " << k3 << endl << "k4= " << k4 << endl << "k5= " << k5 << endl;

	//f
	//c


	xM.D.f = f(k5) + (f(f(k4) + c(k5))) << 32 + (f(f(k3) + c(k4) + c(f(k4) + c(k5)))) << 64 + (f(f(k2) + c(k3) + c(f(k4) + c(f(k3) + c(k4) + c(f(k4) + c(k5)))))) << 96 + (f(f(k1) + c(k2) + c(f(k4) + c(f(k2) + c(k3) + c(f(k4) + c(f(k3) + c(k4) + c(f(k4) + c(k5)))))))) << 128 + (f(c(k1)+c(f(k1) + c(k2) + c(f(k4) + c(f(k2) + c(k3) + c(f(k4) + c(f(k3) + c(k4) + c(f(k4) + c(k5)))))))))<<160;
	znak = int((xM.D.f))%4;
	xM = xM * M_PI / 4.0;
	x = xM;



	








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

		next_cos = x * x / (2.0 * i) / (2.0 * i - 1) * (-1.0);
		for_cos = MY_FMA(last_cos, next_cos, for_cos);
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













template<int e, int m>
class ERFi
{


public:
	template<int M = m>
	typename std::enable_if<M <= 5, Floating_Point<e, m>>::type
		Erf(Floating_Point<e, m> x)
	{
		double a1 = 0.278393;
		double a2 = 0.230389;
		double a3 = 0.000972;
		double a4 = 0.078108;

		Floating_Point<e, m> erf = 1 - 1 / pow(1 + 0.278393 * x.D.f + 0.230389 * x.D.f + 0.000972 * x.D.f + 0.078108 * x.D.f, 4);
		return erf;
	}
	template<int M = m>
	typename std::enable_if<(M <= 10 && M > 5), Floating_Point<e, m>>::type
		Erf(Floating_Point<e, m> x)
	{
		double p = 0.47047;
		double a1 = 0.3480242;
		double a2 = -0.0958798;
		double a3 = 0.7478556;

		Floating_Point t = 1 / (1 + p * x.D.f);

		x = x.exp_function(10);
		Floating_Point ex = x.D.f;
		ex *= ex;
		ex = 1 / ex; // e^(-x^2)

		Floating_Point<e, m> erf = 1 - (1 + a1 * t + a2 * t * t + a3 * t * t * t) * ex;
		return erf;
	}
	template<int M = m>
	typename std::enable_if<(M > 10), Floating_Point<e, m>>::type
		Erf(Floating_Point<e, m> x)
	{
		double p = 0.3275911;
		double a1 = 0.254829592;
		double a2 = -0.284496736;
		double a3 = 1.421413741;
		double a4 = -1.453152027;
		double a5 = 1.061405429;

		Floating_Point<e,m> t = 1 / (1 + p * x.D.f);

		x = x.exp_function(10);
		Floating_Point<e,m> ex = x.D.f;
		ex = ex* ex;
		ex = 1 / ex.D.f; // e^(-x^2)
		double tt = t.D.f;
		Floating_Point<e, m> erf = ex*(1 + a1 * tt + a2 * tt * tt + a3 * tt * tt * tt + a4 * pow(tt, 4) + a5 * pow(tt, 5)) * (-1) + 1;
		return erf;
	}
};

template<int e,int m>
Floating_Point<e, m> Erf_func(Floating_Point<e,m>& x)
{
	ERFi<e, m> xret;
	xret = xret.Erf(x);
	return xret;
}


