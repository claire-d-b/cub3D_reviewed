#include "fixed.hpp"
#include <iostream>
#include <cmath>

int const Fixed::_f = 8;

Fixed::Fixed( void ) : _n(0)
{
    /*
    **  std::cout << "Default constructor called" << std::endl;
    */
}

Fixed::Fixed( const Fixed& rhs ) : _n(rhs._n)
{
    /*
    **  std::cout << "Copy constructor called" << std::endl;
    */
}

const Fixed & Fixed::operator=( Fixed const & rhs)
{
    /*
    **  std::cout << "Assignation operator called" << std::endl;
    */
    new (this) Fixed(rhs);
    return *this;
    return rhs;
}

Fixed::~Fixed()
{
    /*
    **  std::cout << "Destructor called" << std::endl;
    */
}

Fixed::Fixed( const int n) : _n(n)
{
    /*
    **  std::cout << "Int constructor called" << std::endl;
    */
    _n = _n * pow_rebuild(2, _f);
}

Fixed::Fixed( const float n) : _n(n)
{
    /*
    **  std::cout << "Float constructor called" << std::endl;
    */
    _n = roundf(_n * pow_rebuild(2, _f) + (n - _n) * pow_rebuild(2, _f));
}


float Fixed::pow_rebuild(float nb, float pow) const
{
    float res(1);

    for (int i = 0; i < pow; i++)
        res = res * nb;
    if (pow < 0)
    {
        for (int i = 0; i < -pow; i++)
            res = res * 1 / nb;
    }
    return res;
}

float Fixed::toFloat(void) const
{
    float res(0);

    res = _n / pow_rebuild(2, _f);
    return res;
}

int Fixed::toInt(void) const
{
 return _n / pow_rebuild(2, _f);
}

std::ostream & operator<<(std::ostream & o, Fixed const & rhs)
{
    o << rhs.toFloat();
    return o;
}

int Fixed::operator<(Fixed const & rhs)
{
    if (_n < rhs._n)
        return 1;
    return 0;
}

int Fixed::operator>(Fixed const & rhs)
{
    if (_n > rhs._n)
        return 1;
    return 0;
}

int Fixed::operator<=(Fixed const & rhs)
{
    if (_n <= rhs._n)
        return 1;
    return 0;
}

int Fixed::operator>=(Fixed const & rhs)
{
    if (_n >= rhs._n)
        return 1;
    return 0;
}

int Fixed::operator==(Fixed const & rhs)
{
    if (_n == rhs._n)
        return 1;
    return 0;
}

int Fixed::operator!=(Fixed const & rhs)
{
    if (_n != rhs._n)
        return 1;
    return 0;
}

Fixed Fixed::operator+(Fixed const & rhs)
{
    return Fixed(toFloat() + rhs.toFloat());
}

Fixed Fixed::operator-(Fixed const & rhs)
{
    return Fixed(toFloat() - rhs.toFloat());
}

Fixed Fixed::operator*(Fixed const & rhs)
{
    return Fixed(toFloat() * rhs.toFloat());
}

Fixed Fixed::operator/(Fixed const & rhs)
{
    return Fixed(toFloat() / rhs.toFloat());
}

Fixed& Fixed::operator++( void )
{
    ++_n;
    return *this;
}

Fixed Fixed::operator++(int)
{
    Fixed tmp = *this;
    _n++;
    return tmp;
}

Fixed & Fixed::operator--( void )
{
    --_n;
    return *this;
}

Fixed Fixed::operator--(int)
{
    Fixed tmp = *this;
    _n--;
    return tmp;
}

const Fixed & Fixed::min(Fixed const & a, Fixed const & b)
{
    if (a._n < b._n)
        return a;
    return b;
}

const Fixed & Fixed::max(Fixed const & a, Fixed const & b)
{
    if (a._n > b._n)
         return a;
    return b;
}

Fixed & Fixed::min(Fixed & a, Fixed & b)
{
    if (a._n < b._n)
         return a;
    return b;
}

Fixed & Fixed::max(Fixed & a, Fixed & b)
{
    if (a._n > b._n)
         return a;
    return b;
}


int Fixed::getRawBits(void) const 
{
    return (_n);
}

void Fixed::setRawBits(int const raw)
{
    _n = raw;
}

Fixed fxabs(Fixed const & rhs)
{
    Fixed a(rhs);

    if (a < Fixed(0))
        return a * Fixed(-1);
    return rhs;
}