//
// pch.h
//

#pragma once

#include "gtest/gtest.h"

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
class DOUBLE
{
private:

public:

    Dbl D;

    unsigned long long int get_mask()
    {
        unsigned long long int one = 1;
        unsigned long long int mask = (((one << (m + 11)) - 1) << 1) + 1;
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
        if (isinf(res.D.f) && isinf(a.D.f) && res.D.sign == a.D.sign) throw  invalid_argument("Attempted to substract Infinity and Infinity\n");
        res.D.f -= a.D.f;
        res.CHECK_EXP_AND_MAN();
        return res;
    }
    DOUBLE operator*(const DOUBLE& a)
    {
        DOUBLE res(*this);
        if (isinf(res.D.f) && a.D.f == 0.0 || isinf(a.D.f) && res.D.f == 0.0) throw  invalid_argument("Attempted to multiplicate Zero and Infinity\n");
        res.D.f *= a.D.f;
        res.CHECK_EXP_AND_MAN();
        return res;
    }
    DOUBLE operator/(const DOUBLE& a)
    {
        DOUBLE res(*this);
        if (a.D.f == 0.0) throw  invalid_argument("Attempted to divide by Zero\n");
        res.D.f /= a.D.f;
        res.CHECK_EXP_AND_MAN();
        return res;
    }

    bool Check_expMAX()
    {
        return ((1024 + ((1 << (e - 1)) - 1)) >= D.ex);
    }
    bool Check_expMIN()
    {
        return ((1023 - ((1 << (e - 1)) - 1)) <= D.ex);
    }

    void special_infinity_and_null_check()
    {
        D.man &= (get_mask() * Check_expMAX());
        D.ex |= ((1 << 11) - 1) * (unsigned long long int)!(Check_expMAX());

        D.man &= (get_mask() * Check_expMIN());
        D.ex &= ((1 << 11) - 1) * (unsigned long long int)(Check_expMIN());
    }

    void CHECK_EXP_AND_MAN()
    {
        special_infinity_and_null_check();

    }


    void get_double()
    {
        cout << "Double: " << D.f << endl;
        cout << "sign: " << D.sign << endl;
        cout << "exp: " << D.ex << endl;
        cout << "mantissa: " << D.man << endl;
    }

};







