/****************************************************************************
** Filename:    - complex.h
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - implementations of complex (numbers) class
** Date:        - 9/1/2018
** Version:     - 6
*****************************************************************************/
#include <iostream> /* ostream istream */

namespace ilrd
{

const static double EPSILON = 0.000001;

inline bool IsDoubleEqual(double arg1, double arg2)
{
    double result = arg1 - arg2;
    ( result < 0 ) ? ( result *= -1 ) : (true); /* abs */

    return (result <= EPSILON); /* result if more precise than epsilon */
}

class Complex;

/*== GLOBAL OPERATIONS ==*/
/*============== comparison operators ============*/
inline bool operator==(const Complex& c1_, const Complex& c2_);
inline bool operator!=(const Complex& c1_, const Complex& c2_);

/*============== arithmetic operators ============*/
inline const Complex operator+(const Complex& c1_, const Complex& c2_);
inline const Complex operator-(const Complex& c1_, const Complex& c2_);
inline const Complex operator*(const Complex& c1_, const Complex& c2_);
inline const Complex operator/(const Complex& c1_, const Complex& c2_);

/*================ in/out streams ================*/
inline std::ostream& operator<<(std::ostream& os_, const Complex& c_);
inline std::istream& operator>>(std::istream& is_, Complex& c_);

class Complex
{
public:
  /*====== Constructor ======*/
  inline Complex(double re_ = 0, double im_ = 0); // not explicit on porpose

  /*====== Compound assignment operators ======*/
  inline Complex& operator+=(const Complex& c_);
  inline Complex& operator-=(const Complex& c_);
  inline Complex& operator*=(const Complex& c_);
  inline Complex& operator/=(const Complex& c_);

   /*===== getters / setters ======*/
   inline double GetRe() const;
   inline double GetIm() const;

   inline void SetRe(double re_);
   inline void SetIm(double im_);

private:
      double m_re;
      double m_im;

}; // End of Complex Class


/*== class Complex methods ==*/
/*============================  Constructor  ============================*/
inline Complex::Complex(double re_, double im_): // not explicit on porpose
m_re(re_), m_im(im_)
{}

/*============================  operator+=  ============================*/
inline Complex& Complex::operator+=(const Complex& c_)
{
    m_re += c_.m_re;
    m_im += c_.m_im;

    return *this;
}

/*============================  operator-=  ============================*/
inline Complex& Complex::operator-=(const Complex& c_)
{
    m_re -= c_.m_re;
    m_im -= c_.m_im;

    return *this;
}
/*============================  operator*=  ============================*/
inline Complex& Complex::operator*=(const Complex& c_)
{
    /* this->m_re will be changed, need to save
       current m_re before for m_im calculation */
    double real = m_re;

    m_re = (m_re) * (c_.m_re) - (m_im) * (c_.m_im);
    m_im = (real) * (c_.m_im) + (m_im) * (c_.m_re);

    return *this;
}

/*============================  operator/=  ============================*/
inline Complex& Complex::operator/=(const Complex& c_)
{
    /* this->m_re will be changed, need to save
       current m_re before for m_im calculation */
    double real = m_re;
    double denominator = c_.m_re * c_.m_re + c_.m_im * c_.m_im;

    m_re = ((m_re) * (c_.m_re) + (m_im) * (c_.m_im)) / denominator;
    m_im = ((m_im) * (c_.m_re) - (real) * (c_.m_im)) / denominator;

    return *this;
}

/*==========================  get real number  =========================*/
inline double Complex::GetRe() const
{
    return m_re;
}

/*==========================  get imaginary number  ====================*/
inline double Complex::GetIm() const
{
    return m_im;
}

/*==========================  set real number  =========================*/
inline void Complex::SetRe(double re_)
{
    m_re = re_;
}

/*==========================  set imaginary number  ====================*/
inline void Complex::SetIm(double im_)
{
    m_im = im_;
}



/*== GLOBAL OPERATIONS ==*/
/*==============================  operator==  ==============================*/
inline bool operator==(const Complex& c1_, const Complex& c2_)
{
    return     IsDoubleEqual(c1_.GetRe(), c2_.GetRe())
            && IsDoubleEqual(c1_.GetIm(), c2_.GetIm());
}

/*==============================  operator!=  ==============================*/
inline bool operator!=(const Complex& c1_, const Complex& c2_)
{
    return !(c1_ == c2_);
}

/*==============================  operator+  ==============================*/
inline const Complex operator+(const Complex& c1_, const Complex& c2_)
{
    Complex local(c1_);
    local += c2_;

    return local;
}

/*==============================  operator-  ==============================*/
inline const Complex operator-(const Complex& c1_, const Complex& c2_)
{
    Complex local(c1_);
    local -= c2_;

    return local;
}

/*==============================  operator*  ==============================*/
inline const Complex operator*(const Complex& c1_, const Complex& c2_)
{
    Complex local(c1_);
    local *= c2_;

    return local;
}

/*==============================  operator/  ==============================*/
inline const Complex operator/(const Complex& c1_, const Complex& c2_)
{
    Complex local(c1_);
    local /= c2_;

    return local;
}

/*==============================  operator<<  ==============================*/
inline std::ostream& operator<<(std::ostream& os_, const Complex& c_)
{
    const char *sign = (c_.GetIm() >= 0) ? ("+") : ("\0");
    os_ << c_.GetRe() << sign << c_.GetIm() << "i";

    return os_;
}

/*==============================  operator>>  ==============================*/
inline std::istream& operator>>(std::istream& is_, Complex& c_)
{
    double real = 0;
    double imag = 0;

    char i;
    is_ >> real >> imag >> i;

    c_.SetRe(real);
    c_.SetIm(imag);

    return is_;
}


}  // namespace ilrd
