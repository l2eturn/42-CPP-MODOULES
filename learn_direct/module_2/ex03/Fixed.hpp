#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>

/*
** ex02 - OPERATOR OVERLOADING เต็มรูปแบบ
**
** ===== ทำไม comparison/arithmetic เป็น const member =====
** operator< ไม่แก้ตัวเอง -> const  (ถ้าไม่ใส่ const, Fixed const b จะเทียบไม่ได้)
** operator+ คืน Fixed *by value* เพราะผลลัพธ์เป็นตัวใหม่ ไม่ใช่ตัวเดิม
**   -> คืน reference ไปที่ local variable = dangling reference (ห้ามเด็ดขาด)
**
** ===== pre vs post increment =====
**   Fixed &operator++(void);    // ++a : เพิ่มแล้วคืน "ตัวเดิม" -> reference
**   Fixed operator++(int);      // a++ : คืน "ค่าเก่า" -> ต้อง copy = by value
**
** พารามิเตอร์ int ปลอมๆ ใน operator++(int) ไม่ได้ใช้เลย
** มันมีไว้ให้ compiler แยกแยะ pre กับ post ออกจากกัน (dummy parameter)
** -> ตั้งชื่อมันไม่ได้ ไม่งั้น -Wunused-parameter จะฟ้อง (ปล่อยไม่มีชื่อไว้)
**
** epsilon = raw 1 = 1/256 = 0.00390625 คือค่าที่เล็กสุดที่บวกได้แล้วค่าเปลี่ยน
*/
class Fixed
{
	public:
		Fixed(void);
		Fixed(const Fixed &other);
		Fixed(const int value);
		Fixed(const float value);
		Fixed	&operator=(const Fixed &other);
		~Fixed(void);

		int		getRawBits(void) const;
		void	setRawBits(int const raw);
		float	toFloat(void) const;
		int		toInt(void) const;

		bool	operator>(const Fixed &other) const;
		bool	operator<(const Fixed &other) const;
		bool	operator>=(const Fixed &other) const;
		bool	operator<=(const Fixed &other) const;
		bool	operator==(const Fixed &other) const;
		bool	operator!=(const Fixed &other) const;

		Fixed	operator+(const Fixed &other) const;
		Fixed	operator-(const Fixed &other) const;
		Fixed	operator*(const Fixed &other) const;
		Fixed	operator/(const Fixed &other) const;

		Fixed	&operator++(void);
		Fixed	operator++(int);
		Fixed	&operator--(void);
		Fixed	operator--(int);

		static Fixed		&min(Fixed &a, Fixed &b);
		static const Fixed	&min(const Fixed &a, const Fixed &b);
		static Fixed		&max(Fixed &a, Fixed &b);
		static const Fixed	&max(const Fixed &a, const Fixed &b);

	private:
		int					_value;
		static const int	_fractionalBits = 8;
};

std::ostream	&operator<<(std::ostream &os, const Fixed &value);

#endif
