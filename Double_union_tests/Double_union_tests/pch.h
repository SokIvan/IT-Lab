//
// pch.h
//

#pragma once

#include "gtest/gtest.h"

#include <iostream>
#include <climits>
using std::cout;
using std::endl;


union Dbl
{
    double f;
    struct
    {
        uint64_t man : 52;
        uint64_t exp : 11;
        uint64_t sign : 1;
    };
};


template<int e, int m>
class DOUBLE
{
private:

public:

    Dbl D;

    unsigned long long int get_mask()
    {
        unsigned long long int mask = (((1 << (m + 11)) - 1) << 1) + 1;
        mask = mask << (52 - m);

        return mask;
    }

    DOUBLE()
    {
        D.f = 0.0;
    }
    DOUBLE(const double& a)
    {
        D.f = a;
        CHECK_EXP_AND_MAN();
    }
    DOUBLE(const DOUBLE& a)
    {
        D.f = a.D.f;
    }

    DOUBLE& operator=(const DOUBLE& a)
    {
        D.f = a.D.f;
        return *this;
    }
    DOUBLE operator+(const DOUBLE& a)
    {
        DOUBLE res(*this);
        res.D.f += a.D.f;
        res.CHECK_EXP_AND_MAN();
        return res;
    }
    DOUBLE operator-(const DOUBLE& a)
    {
        DOUBLE res(*this);
        res.D.f -= a.D.f;
        res.CHECK_EXP_AND_MAN();
        return res;
    }
    DOUBLE operator*(const DOUBLE& a)
    {
        DOUBLE res(*this);
        res.D.f *= a.D.f;
        res.CHECK_EXP_AND_MAN();
        return res;
    }
    DOUBLE operator/(const DOUBLE& a)
    {
        DOUBLE res(*this);
        res.D.f /= a.D.f;
        res.CHECK_EXP_AND_MAN();
        return res;
    }


    /*
        void Check_exp()
        {
            int difmin = 1023 - ((1 << (e-1)) - 1), difmax = 1024 + ((1 << (e - 1)) - 1);


            if ((D.exp) < difmin)
            {
                D.f = NULL * (0.5-D.sign);
            }
            else if ((D.exp)>difmax)
            {
                D.f = INFINITY * (0.5 - D.sign);
            }

        }
    */
    bool Check_expMAX()
    {
        return ((1024 + ((1 << (e - 1)) - 1)) >= D.exp);
    }
    bool Check_expMIN()
    {
        return ((1023 - ((1 << (e - 1)) - 1)) <= D.exp);
    }
    double EXP_CHECK()
    {
        return Check_expMAX() * Check_expMIN() * D.f + !(Check_expMIN()) * NULL;
    }
    void special_infinity_check()
    {
        D.man |= (ULLONG_MAX << 12) * !(Check_expMAX());
        D.exp |= ((1 << 11) - 1) * !(Check_expMAX());
    }



    void CHECK_EXP_AND_MAN()
    {
        special_infinity_check();
        D.f = EXP_CHECK();
        D.man &= get_mask();
    }


    void get_double()
    {
        cout << "Double: " << D.f << endl;
        cout << "sign: " << D.sign << endl;
        cout << "exp: " << D.exp << endl;
        cout << "mantissa: " << D.man << endl;
    }

};
