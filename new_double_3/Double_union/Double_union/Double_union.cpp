#include <iostream>

using namespace std;


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


template<int e,int m>
class DOUBLE
{
private:
    Dbl D;
public:
    long long int get_mask()
    {
        long long int mask = ((1 << (m + 12)) - 1);
        mask = mask << (64 - (m + 12));
        return mask;
    }

    DOUBLE()
    {
        D.f = 0.0;
    }
    DOUBLE(const double& a)
    {
        D.f = a;
        D.man &= get_mask();
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
        res.D.man &= get_mask();
        res.Check_exp();
        return res;
    }
    DOUBLE operator-(const DOUBLE& a)
    {
        DOUBLE res(*this);
        res.D.f -= a.D.f;
        res.D.man &= get_mask();
        res.Check_exp();
        return res;
    }
    DOUBLE operator*(const DOUBLE& a)
    {
        DOUBLE res(*this);
        res.D.f *= a.D.f;
        res.D.man &= get_mask();
        res.Check_exp();
        return res;
    }
    DOUBLE operator/(const DOUBLE& a)
    {
        DOUBLE res(*this);
        res.D.f /= a.D.f;
        res.D.man &= get_mask();
        res.Check_exp();
        return res;
    }



    void Check_exp()
    {
        int difmin = 1023 - ((1 << (e-1)) - 1), difmax = 1023 - (difmin - 1023)+1;


        if ((D.exp) < difmin)
        {
            D.f = INFINITY * (0.5-D.sign);
        }
        else if ((D.exp)>difmax)
        {
            D.f = NULL * (0.5 - D.sign);
        }

    }




    void get_double()
    {
        cout << "Double: " << D.f << endl;
        cout << "sign: " << D.sign << endl;
        cout << "exp: " << D.exp << endl;
        cout << "mantissa: " << D.man << endl;
    }

};






int main()
{


}
