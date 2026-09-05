#include <iostream>
#include "Fixed.hpp"

/*
** static const member ที่มี initializer ใน class
** ยังต้อง "นิยาม" นอก class (ไม่ใส่ค่าซ้ำ) ถ้ามีการเอา address หรือ bind reference
** ใส่ไว้เลยจะปลอดภัยกว่า
*/
const int	Fixed::_fractionalBits;

Fixed::Fixed(void) : _value(0)
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &other) : _value(other._value)
{
	std::cout << "Copy constructor called" << std::endl;
}

/*
** operator= ต้อง:
**   - เช็ค self-assignment (a = a) ก่อน
**   - คืน *this เป็น reference เพื่อให้ chain ได้ (a = b = c)
*/
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
	std::cout << "getRawBits member function called" << std::endl;
	return (_value);
}

void	Fixed::setRawBits(int const raw)
{
	_value = raw;
}
