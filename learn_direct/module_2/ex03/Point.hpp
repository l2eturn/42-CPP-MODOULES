#ifndef POINT_HPP
# define POINT_HPP

# include "Fixed.hpp"

/*
** ex03 - BSP (จุดอยู่ในสามเหลี่ยมไหม)
**
** ===== กับดักใหญ่ของ exercise นี้: attribute เป็น const =====
** โจทย์บังคับว่า x, y ต้องเป็น "Fixed const"
** -> const member ตั้งค่าได้ครั้งเดียวใน initialization list เท่านั้น
** -> เขียน operator= แบบปกติ (_x = other._x) *ไม่ได้* คอมไพล์ไม่ผ่าน
**
** ทางออก: เขียน operator= ให้มีตามที่โจทย์ขอ แต่ให้มันไม่ทำอะไร
** (Point เป็น value type ที่ immutable ตามดีไซน์ -- assign ทับไม่ได้ตั้งใจแล้ว)
** ถ้าอยากให้ assign ได้จริง ต้องเอา const ออก ซึ่งขัดโจทย์
*/
class Point
{
	public:
		Point(void);
		Point(const float x, const float y);
		Point(const Point &other);
		Point	&operator=(const Point &other);
		~Point(void);

		const Fixed	&getX(void) const;
		const Fixed	&getY(void) const;

	private:
		Fixed const	_x;
		Fixed const	_y;
};

bool	bsp(Point const a, Point const b, Point const c, Point const point);

#endif
