#include <iostream>
#include <stdlib.h>

using namespace std;










template<int a,int b>
class Short_double
{
private:
                        ///////////////// mas = ['{0 0000000} {0000 b ... }']
public:    
    unsigned char* mas; ///////////////// 1ый бит будет знак, следующие 11 будут порядком, следующие b мантисса.
    Short_double()      ///////////////// Если в мантиссе нужно больше битов, то добавляется еще один чар или 8 бит.
    {                   ///////////////// По умолчанию все елементы нули.
        
        int size = 3, a1 = b - 4;
        while (a1 > 8)
        {
            size++;
            a1 -= 8;
        }
        mas = new unsigned char[size];

        for (int i = 0; i < size; i++) mas[i] = 0;

    }

    void ret_two_double(double &d1, double &d2,Short_double<a,b> c2)
    {
        int* mant_self, * mant_c2;

        mant_self = new int[b];
        mant_c2 = new int[b];

        int exp = int(mas[0]) << 4, exp2 = int(c2.mas[0]) << 4, f = mas[1], f2 = c2.mas[1], i, j, k;
        for (i = 0, j = 128, k = 8; i < 4; i++, j /= 2, k /= 2)
        {
            if (f - j >= 0)
            {
                f -= j;
                exp += k;
            }
            if (f2 - j >= 0)
            {
                f2 -= j;
                exp2 += k;
            }
        }
        k = 0;
        i = 4;
        exp -= 1023;
        exp2 -= 1023;
        int b1 = 1;
        while (3 - b1 > 0)
        {
            for (; i < 8 && k < b; i++, j /= 2, k++)
            {
                if (f - j >= 0)
                {
                    f -= j;
                    mant_self[k] = 1;
                }
                else
                {
                    mant_self[k] = 0;
                }
                if (f2 - j >= 0)
                {
                    f2 -= j;
                    mant_c2[k] = 1;
                }
                else
                {
                    mant_c2[k] = 0;
                }
            }
            b1++; i = 0; j = 128; f = mas[b1]; f2 = c2.mas[b1];
        }

        double a1 = 0.0, a2 = 0.0;

        for (i = 0; i < b; i++)
        {
            a1 += mant_self[i] * pow(2, exp - i);
            a2 += mant_c2[i] * pow(2, exp2 - i);

        }
       // cout << endl << "a1 =" << a1 << endl;          /////////////////
      //  cout <<endl << "a2 ="<<a2 << endl;          /////////////////

        delete[]mant_self;
        delete[]mant_c2;
    

        d1 = a1;
        d2 = a2;
    
    }

    Short_double( double D)
    {
        int size = 3, i1 = b - 4;

        while (i1 > 8) {size++;i1 -= 8;}
        
        mas = new unsigned char[size];




        
        int sign = 0, exp = 1; double d = D, r = 1.0;

        if (d < 0.0) {sign = 1;d = -d;}

        if (d >= 1.0) { while (r < d) r = pow(2, exp++); exp -= 2; }
        else {while (r > d) r = pow(2, exp--);exp++;}
        


        int f = 1023 + exp, * por = new int[11];

        for (int k = 0, i1 = 1024; i1 >= 1; i1 /= 2, k++)
        {
            if (f - i1 >= 0){por[k] = 1;f -= i1;}
            else por[k] = 0;
        }

        int *mantissa = new int[b]; double res = 0.0; i1 = 0;
        
        while (i1 <= b)
        {
            r = pow(2, exp - i1);
            if (r + res > d) mantissa[i1] = 0;
            else {res += r;mantissa[i1] = 1;}
            i1++;
        }

        int k1, k2;

        for (i1 = 0; i1 < size; i1++) mas[i1] = 0;

        mas[0] = 128 * sign;

        for (k1 = 0,k2 = 64;k1!=6;k2/=2,k1++) mas[0] += k2*por[k1];
        for (k1=7, k2 = 128; k1 < 11; k1++, k2 /= 2) mas[1] += k2 * por[k1];
        for (k1 = 0, k2; k1 < 4; k1++, k2 /= 2) mas[1] += k2 * mantissa[k1];

        f = 4; i1 = 2;

        while (size - i1 > 0)
        {
            for (k1 = 1, k2 = 128; k1 <= 8 && f+k1-1 < b; k1++, k2 /= 2) mas[i1] += k2 * mantissa[f+k1 - 1];

            f += 8;
            i1++;
        }






    }

    void show_inside()
    {
        int* mant_self;

        mant_self = new int[b];


        int exp = int(mas[0]) << 4, f = mas[1], i, j, k;
        for (i = 0, j = 128, k = 8; i < 4; i++, j /= 2, k /= 2)
        {
            if (f - j >= 0)
            {
                f -= j;
                exp += k;
            }

        }
        k = 0;
        exp -= 1023;

        int b1 = 2;
        while (b - b1 > 0)
        {
            for (; i < 8 && k < b; i++, j /= 2, k++)
            {
                if (f - j >= 0)
                {
                    f -= j;
                    mant_self[k] = 1;
                }
                else
                {
                    mant_self[k] = 0;
                }
            }
            i = 0; j = 128; f = mas[b1++];
        }
        cout <<endl<< "exp: " << exp << endl << "mant: ";
        for (i = 0; i < b; i++) cout << mant_self[i];
        delete[]mant_self;
    }


    void show()
    {
        int size = 3, a1 = b - 4;
        while (a1 > 8)
        {
            size++;
            a1 -= 8;
        }

        for (int i = 0; i < size; i++)
        {
            cout <<endl<< int(mas[i]) << endl;
        }
    }

    void show_double()
    {
        Short_double<a, b> c2;
        double d1, d2;
        ret_two_double(d1, d2, c2);
        cout << endl << d1 << endl;
    }

    double convert_to_double()
    {

    }

    Short_double<a, b> operator=(double c) 
    {
        Short_double c1(c);
        return c1;
    }
    Short_double<a, b> operator+(Short_double<a, b> c2) 
    {
        double d1, d2;
        ret_two_double(d1,d2,c2);       
        Short_double<a, b> summ(d1+d2);
        return summ;
    }
    Short_double<a, b> operator+=(Short_double<a, b> c2) 
    {
        double d1, d2;
        ret_two_double(d1, d2, c2);

        Short_double<a, b> summ_equal(d1 + d2);
        *this = summ_equal;
        return* this;
    }
    Short_double<a, b> operator-(Short_double<a, b> c2) 
    {
        double d1, d2;
        ret_two_double(d1, d2, c2);
        Short_double<a, b> dif(d1-d2);
        return dif;
    }
    Short_double<a, b> operator-=(Short_double<a, b> c2)
    {
        double d1, d2;
        ret_two_double(d1, d2, c2);
        Short_double<a, b> dif(d1 - d2);
        *this = dif;
        return *this;
    }
    Short_double<a, b> operator*(Short_double<a, b> c2) 
    {
        double d1, d2;
        ret_two_double(d1, d2, c2);
        Short_double<a, b> dif(d1 * d2);
        return dif;
    }
    Short_double<a, b> operator*=(Short_double<a, b> c2) 
    {
        double d1, d2;
        ret_two_double(d1, d2, c2);
        Short_double<a, b> dif(d1 * d2);
        *this = dif;
        return *this;
    }
    Short_double<a, b> operator/(Short_double<a, b> c2) 
    {
        double d1, d2;
        ret_two_double(d1, d2, c2);
        Short_double<a, b> dif(d1 / d2);
        return dif;
    }
    Short_double<a, b> operator/=(Short_double<a, b> c2) 
    {
        double d1, d2;
        ret_two_double(d1, d2, c2);
        Short_double<a, b> dif(d1 / d2);
        *this = dif;
        return *this;
    }
};

























int main()
{
    Short_double<4, 7> c(5.0),a(5.0),b(2.35),try_me(0.0);

    c.show_inside();

  //  try_me = c;
  //  try_me.show_inside();
   // c.show_double();


  //  c = a + b;
 //   c.show_inside();
  //  c.show_double();
    
 //   c += a;
//  c.show_inside();
 // c.show_double();

      c *= b;
      c.show();
}
