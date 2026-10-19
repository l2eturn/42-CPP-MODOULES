#include "Fixed.hpp"

Fixed::Fixed(void) : _value(0)
{
}

Fixed::Fixed(const int n) : _value(n << _fractionalBits)
{
}

Fixed::Fixed(const float f) : _value(roundf(f * (1 << _fractionalBits)))
{
}

Fixed::Fixed(const Fixed &other) : _value(other._value)
{
}

Fixed	&Fixed::operator=(const Fixed &other)
{
	if (this != &other)
		this->_value = other._value;
	return (*this);
}

Fixed::~Fixed(void)
{
}

int	Fixed::getRawBits(void) const
{
	return (_value);
}

void	Fixed::setRawBits(int const raw)
{
	this->_value = raw;
}

float	Fixed::toFloat(void) const
{
	return (static_cast<float>(_value) / (1 << _fractionalBits));
}

int	Fixed::toInt(void) const
{
	return (_value >> _fractionalBits);
}

// ---------- comparison

bool	Fixed::operator>(const Fixed &other) const
{
	return (_value > other._value);
}

bool	Fixed::operator<(const Fixed &other) const
{
	return (_value < other._value);
}

bool	Fixed::operator>=(const Fixed &other) const
{
	return (_value >= other._value);
}

bool	Fixed::operator<=(const Fixed &other) const
{
	return (_value <= other._value);
}

bool	Fixed::operator==(const Fixed &other) const
{
	return (_value == other._value);
}

bool	Fixed::operator!=(const Fixed &other) const
{
	return (_value != other._value);
}

// ---------- arithmetic

Fixed	Fixed::operator+(const Fixed &other) const
{
	Fixed	result;

	result.setRawBits(_value + other._value);
	return (result);
}

Fixed	Fixed::operator-(const Fixed &other) const
{
	Fixed	result;

	result.setRawBits(_value - other._value);
	return (result);
}

Fixed	Fixed::operator*(const Fixed &other) const
{
	Fixed	result;
	long	raw = static_cast<long>(_value) * other._value;

	result.setRawBits(static_cast<int>(raw >> _fractionalBits));
	return (result);
}

Fixed	Fixed::operator/(const Fixed &other) const
{
	Fixed	result;
	long	raw = (static_cast<long>(_value) << _fractionalBits) / other._value;

	result.setRawBits(static_cast<int>(raw));
	return (result);
}

// ---------- increment / decrement

Fixed	&Fixed::operator++(void)
{
	this->_value ++;
	return (*this);
}

Fixed	Fixed::operator++(int)
{
	Fixed	old(*this);

	this->_value ++;
	return (old);
}

Fixed	&Fixed::operator--(void)
{
	this->_value --;
	return (*this);
}

Fixed	Fixed::operator--(int)
{
	Fixed	old(*this);

	this->_value --;
	return (old);
}

// ---------- min / max

Fixed	&Fixed::min(Fixed &a, Fixed &b)
{
	if (a < b)
		return (a);
	return (b);
}

const Fixed	&Fixed::min(const Fixed &a, const Fixed &b)
{
	if (a < b)
		return (a);
	return (b);
}

Fixed	&Fixed::max(Fixed &a, Fixed &b)
{
	if (a > b)
		return (a);
	return (b);
}

const Fixed	&Fixed::max(const Fixed &a, const Fixed &b)
{
	if (a > b)
		return (a);
	return (b);
}

std::ostream	&operator<<(std::ostream &os, const Fixed &fixed)
{
	os << fixed.toFloat();
	return (os);
}
