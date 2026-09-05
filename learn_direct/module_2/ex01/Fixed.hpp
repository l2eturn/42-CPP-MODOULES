#ifndef FIXED_HPP
# define FIXED_HPP

# include <iostream>

/*
** ex01 - เพิ่ม constructor แปลงชนิด + operator<<
**
** ===== คณิตศาสตร์ของ fixed-point (bits = 8, ตัวคูณ = 2^8 = 256) =====
**   int -> fixed   : raw = value << 8          (คูณ 256 แบบไม่เสียความแม่น)
**   float -> fixed : raw = roundf(value * 256) (ต้อง round ไม่ใช่ตัดทิ้ง!)
**   fixed -> int   : value = raw >> 8          (ตัดเศษทศนิยมทิ้ง)
**   fixed -> float : value = raw / 256.0f
**
** ทำไม roundf ไม่ใช่ (int)? เพราะ cast จะตัดทิ้งเข้าหา 0
** 42.42 * 256 = 10859.52 -> ตัดได้ 10859, round ได้ 10860
** 10860/256 = 42.421875 -> พิมพ์ออกเป็น 42.4219 ตรงกับ subject
** ถ้าตัดทิ้งจะได้ 42.4180 ซึ่งผิดจากที่โจทย์คาด
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

	private:
		int					_value;
		static const int	_fractionalBits = 8;
};

/*
** operator<< ต้องเป็น "free function" ไม่ใช่ member!
** เพราะตัวถูกดำเนินการซ้าย (left operand) คือ std::ostream ไม่ใช่ Fixed
** ถ้าเขียนเป็น member ของ Fixed จะต้องเขียน  f << std::cout  ซึ่งกลับหัว
**
** คืน std::ostream & เพื่อให้ chain ได้: cout << a << b << endl
*/
std::ostream	&operator<<(std::ostream &os, const Fixed &value);

#endif
