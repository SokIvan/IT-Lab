#define _USE_MATH_DEFINES

#include <iostream>
#include <climits>
#include <float.h>
#include <exception>
#include <cmath>



using std::cout;
using std::endl;

using std::isinf;

using std::invalid_argument;



union Dbl
{
    double f;
    struct
    {
        uint64_t man : 52;
        uint64_t ex : 11;
        uint64_t sign : 1;
    };
};


template<int e, int m>
class Floating_Point
{
private:

public:

    Dbl D;

    unsigned long long int get_mask() noexcept
    {
        unsigned long long int one = 1;
        unsigned long long int mask = (((one << (m + 11)) - 1) << 1) + 1;
        mask = mask << (52 - m);

        return mask;
    }

    Floating_Point() noexcept
    {
        D.f = 0.0;
    }
    Floating_Point(const double& a)  noexcept
    {
        D.f = a;
        CHECK_EXP_AND_MAN();
    }
    Floating_Point(const Floating_Point& a) noexcept
    {
        D.f = a.D.f;
    }

    Floating_Point& operator=(const Floating_Point& a) noexcept
    {
        D.f = a.D.f;
        return *this;
    }
    Floating_Point operator+(const Floating_Point& a)
    {
        Floating_Point res(*this);
        res.D.f += a.D.f;
        res.CHECK_EXP_AND_MAN();
        return res;
    }
    Floating_Point operator-(const Floating_Point& a)
    {
        Floating_Point res(*this);
        res.D.f -= a.D.f;
        res.CHECK_EXP_AND_MAN();
        return res;
    }
    Floating_Point operator*(const Floating_Point& a)
    {
        Floating_Point res(*this);
        res.D.f *= a.D.f;
        res.CHECK_EXP_AND_MAN();
        return res;
    }
    Floating_Point operator/(const Floating_Point& a)
    {
        Floating_Point res(*this);
        res.D.f /= a.D.f;
        res.CHECK_EXP_AND_MAN();
        return res;
    }

    bool Check_expMAX() noexcept
    {
        return ((1024 + ((1 << (e - 1)) - 1)) >= D.ex);
    }
    bool Check_expMIN() noexcept
    {
        return ((1023 - ((1 << (e - 1)) - 1)) <= D.ex);
    }

    void special_infinity_and_null_check() noexcept
    {
        D.man &= (get_mask() * Check_expMAX());
        D.ex |= ((1 << 11) - 1) * (unsigned long long int)!(Check_expMAX());

        D.man &= (get_mask() * Check_expMIN());
        D.ex &= ((1 << 11) - 1) * (unsigned long long int)(Check_expMIN());
    }

    void CHECK_EXP_AND_MAN() noexcept
    {
        special_infinity_and_null_check();

    }




    Floating_Point exp_function(size_t n) // n - ammount of elements in Mcloren
    {
        Floating_Point a(*this);
        a = a * log2(exp(1.0));
        int ipart = ROUND(a+0.5);
        Floating_Point fpart = (a.D.f - ipart)* log(2.0);//x*ln2
        Floating_Point last = 1.0,next;
        a = last;

        for (size_t i = 1; i < n; i++)
        {
            next = fpart/i;
            a = MY_FMA(last, next, a);
            last = last*next;
        }

        a = a * exp2(ipart);

        return a;
    }




    void get_double() noexcept
    {
        cout << "Double: " << D.f << endl;
        cout << "sign: " << D.sign << endl;
        cout << "exp: " << D.ex << endl;
        cout << "mantissa: " << D.man << endl;
    }




    Floating_Point Log2(Floating_Point& a)
    {
        Floating_Point q(a);
        double n1 = log2(1.5); 
        double n2 = log(2); 
        q.D.f = q.D.f / (2 << (q.D.ex - 1023 - 1));
        q.D.f = q.D.f / 1.5;
        q.D.f = q.D.f - 1.0;                                       
        Floating_Point mclrn = q.D.f;
        Floating_Point blog = q.D.f;
        Floating_Point alog;
        for (size_t i = 2; i < 10; i++)
        {
            alog = q.D.f / double(i) * (-1.0) * (i-1);
            mclrn = MY_FMA(blog, alog, mclrn);
            blog = blog * alog;
        }


        a =  (mclrn) / n2  + n1+ (a.D.ex - 1023); 

        return a;
    }

    Floating_Point Log(Floating_Point& a, Floating_Point& q)
    {
        a = Log2(a) / Log2(q);
        return a;     
    }

    Floating_Point Log10(Floating_Point& a)
    {
        Floating_Point ten = 10.0;
        a = Log2(a) / Log2(ten);
        return a;
    }

    Floating_Point LogE(Floating_Point& a)
    {
        Floating_Point expanenta = exp(1);
        a = Log2(a) / Log2(expanenta);
        return a;
    }

};

template<int e, int m>
int ROUND(Floating_Point<e, m> &a)
{
    return round(a.D.f);
}
template<int e, int m>
int CEIL(Floating_Point<e, m> &a)
{
    return ROUND(a+0.5);
}
template<int e, int m>
int FLOOR(Floating_Point<e, m> &a)
{
    return a.D.f;
}
template<int e,int m>
Floating_Point<e, m> ABSOLUTE(Floating_Point<e, m> a)
{
    a.D.sign = 0;
    return a.D.f;
}
template<int e, int m>
Floating_Point<e, m> MY_FMA(Floating_Point<e, m> a, Floating_Point<e, m> b, Floating_Point<e, m>& c)
{
    return a * b + c;
}


