#include <stdlib.h>
#include <iostream>

using namespace std;

#include <stdio.h>

void show(double D)
{
	double d = -D, i = 1.0,res = 0.0,r;
	int poridok = -1,j = 0;
	int mantissa[53];
	int sign = 1;
	if (D >= 0)
	{
		sign = 0;
		d = -d;
	}
	while (d/i >= 1.0)
	{
		i *= 2;
		poridok += 1;
	}

	while (j <= 52)
	{
		r = pow(2, poridok - j);
		if (r + res > d)
		{
			mantissa[j] = 0;
		}
		else
		{
			res += r;
			mantissa[j] = 1;
		}
		j++;
	}
	




	int i1, k;

	int por[11];
	int f = 1023 + poridok;

	for (k = 0, i1 = 1024; i1 >= 1; i1 /= 2,k++)
	{
		if (f - i1 >= 0)
		{
			por[k] = 1;
			f -= i1;
		}
		else
			por[k] = 0;
	}








	cout << "Double: " << D << endl << "Signum: " << sign << endl << "Excpon: ";
	for (j = 0; j < 11; j++) cout << por[j]; 
	cout << endl << "Mantis: ";
	for (j = 1; j <= 52; j++) cout << mantissa[j];
	cout << endl << "res: " << res;

}

double redo(double D, int k_bit_m,int l_poridok)
{
	double d = -D, i = 1.0, res = 0.0, r;
	int poridok = -1, j = 0;
	int mantissa[53];
	int por[11];
	int sign = 1;
	if (D >= 0)
	{
		sign = 0;
		d = -d;
	}
	while (d / i >= 1.0)
	{
		i *= 2;
		poridok += 1;
	}
	while (j <= k_bit_m)
	{
		r = pow(2, poridok - j);
		if (r + res > d)
		{
			mantissa[j] = 0;
		}
		else
		{
			res += r;
			mantissa[j] = 1;
		}
		j++;
	}
	r = pow(2, l_poridok);
	while (res > r)
	{
		cout << "							overflow from: " << res;
		res = -r +(res-r);
		cout << " in " << res << endl;
	}
	if (D < 0) return -res;
	return res;

}

int main()
{
	int i = 0,k = 5;
	double d = 37.5185;
	show(d);
	while (i <= 52)
	{
		cout <<"From " << d << " to " << redo(d, i, k) << " on " << i << " step " << endl;
		i++;
	}

}
