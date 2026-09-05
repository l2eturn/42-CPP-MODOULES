#include <cmath>
#include <iostream>
#include "Fixed.hpp"

const int	Fixed::_fractionalBits;

Fixed::Fixed(void) : _value(0)
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &other) : _value(other._value)
{
	std::cout << "Copy constructor called" << std::endl;
}

Fixed::Fixed(const int value) : _value(value << _fractionalBits)
{
	std::cout << "Int constructor called" << std::endl;
}

Fixed::Fixed(const float value) :
	_value(static_cast<int>(roundf(value * (1 << _fractionalBits))))
{
	std::cout << "Float constructor called" << std::endl;
}

Fixed	&Fixed::operator=(const Fixed &other)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other)
		_value = other._value;
	return (*this);
}

Fixed::~Fixed(void)
{
	std::cout << "Destructor called" << std::endl;
}

int	Fixed::getRawBits(void) const
{
	return (_value);
}

void	Fixed::setRawBits(int const raw)
{
	_value = raw;
}

float	Fixed::toFloat(void) const
{
	return (static_cast<float>(_value) / (1 << _fractionalBits));
}

/*
** >> กับเลขลบ: -1 >> 8 = -1 (ปัดลงเข้าหา -infinity ไม่ใช่เข้าหา 0)
** ต่างจากพฤติกรรมของ (int) cast จาก float -- รู้ไว้เวลาเจอ edge case
*/
int	Fixed::toInt(void) const
{
	return (_value >> _fractionalBits);
}

std::ostream	&operator<<(std::ostream &os, const Fixed &value)
{
	os << value.toFloat();
	return (os);
}
