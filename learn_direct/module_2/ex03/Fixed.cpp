#include <cmath>
#include <iostream>
#include "Fixed.hpp"

const int	Fixed::_fractionalBits;

Fixed::Fixed(void) : _value(0)
{
}

Fixed::Fixed(const Fixed &other) : _value(other._value)
{
}

Fixed::Fixed(const int value) : _value(value << _fractionalBits)
{
}

Fixed::Fixed(const float value) :
	_value(static_cast<int>(roundf(value * (1 << _fractionalBits))))
{
}

Fixed	&Fixed::operator=(const Fixed &other)
{
	if (this != &other)
		_value = other._value;
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
	_value = raw;
}

float	Fixed::toFloat(void) const
{
	return (static_cast<float>(_value) / (1 << _fractionalBits));
}

int	Fixed::toInt(void) const
{
	return (_value >> _fractionalBits);
}

/*
** เทียบกันที่ raw ตรงๆ ได้เลย เพราะ scale เท่ากันทั้งคู่ (2^8)
** แม่นกว่าและเร็วกว่าการแปลงเป็น float ก่อนเทียบ
*/
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

/*
** + และ - : บวก/ลบ raw ตรงๆ ได้ เพราะ scale เดียวกัน -> ไม่เสียความแม่นเลย
** ใช้ setRawBits เพราะ constructor Fixed(int) จะไป shift ซ้ำ
*/
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

/*
** * และ / ทำที่ raw ตรงๆ ไม่ได้ ต้องปรับ scale:
**   (a*256) * (b*256) = a*b*256^2  -> ต้อง >> 8 อีกที
**   (a*256) / (b*256) = a/b        -> ต้อง << 8 อีกที
**
** ทำไมใช้ toFloat() แทน?  เพราะ raw*raw ล้น int ง่ายมาก
** เช่น 1000 * 1000 -> raw 256000 * 256000 = 6.5e10 ล้น 32-bit int แน่นอน
** ผ่าน float ปลอดภัยกว่าในสเกลของโจทย์นี้ (แลกกับความแม่นเล็กน้อย)
** ทางแก้แบบไม่เสียความแม่น = ใช้ long long ตัวกลาง แต่ long long เป็น C++11
*/
Fixed	Fixed::operator*(const Fixed &other) const
{
	return (Fixed(toFloat() * other.toFloat()));
}

Fixed	Fixed::operator/(const Fixed &other) const
{
	return (Fixed(toFloat() / other.toFloat()));
}

Fixed	&Fixed::operator++(void)
{
	++_value;
	return (*this);
}

/*
** post-increment: เก็บสำเนาค่าเก่า -> เพิ่มค่าจริง -> คืนสำเนา
** นี่คือเหตุผลที่ post-increment "แพงกว่า" pre-increment (มี copy เพิ่ม 1 ครั้ง)
** -> เวลา loop ควรเขียน ++i ไม่ใช่ i++ ถ้าไม่ได้ใช้ค่าเก่า
*/
Fixed	Fixed::operator++(int)
{
	Fixed	before(*this);

	++_value;
	return (before);
}

Fixed	&Fixed::operator--(void)
{
	--_value;
	return (*this);
}

Fixed	Fixed::operator--(int)
{
	Fixed	before(*this);

	--_value;
	return (before);
}

/*
** min/max 2 เวอร์ชัน (const / non-const) คือ OVERLOADING บน constness
** non-const คืน non-const reference -> แก้ผลลัพธ์ได้: Fixed::max(a,b) = 5;
** const     คืน const reference     -> ใช้กับ Fixed const ได้
** ถ้ามีแค่เวอร์ชัน non-const, Fixed const b จะส่งเข้าไม่ได้เลย
*/
Fixed	&Fixed::min(Fixed &a, Fixed &b)
{
	return (a < b ? a : b);
}

const Fixed	&Fixed::min(const Fixed &a, const Fixed &b)
{
	return (a < b ? a : b);
}

Fixed	&Fixed::max(Fixed &a, Fixed &b)
{
	return (a > b ? a : b);
}

const Fixed	&Fixed::max(const Fixed &a, const Fixed &b)
{
	return (a > b ? a : b);
}

std::ostream	&operator<<(std::ostream &os, const Fixed &value)
{
	os << value.toFloat();
	return (os);
}
