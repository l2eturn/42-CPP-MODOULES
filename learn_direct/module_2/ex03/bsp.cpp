#include "Point.hpp"

/*
** ===== วิธีคิด: CROSS PRODUCT (2D) =====
** cross(AB, AP) = (Bx-Ax)*(Py-Ay) - (By-Ay)*(Px-Ax)
**
** เครื่องหมายของมันบอก "P อยู่ข้างไหนของเส้น AB":
**   > 0  -> ซ้ายมือ
**   < 0  -> ขวามือ
**   = 0  -> อยู่บนเส้นพอดี
**
** ถ้า P อยู่ "ข้างเดียวกัน" ของทั้งสามด้าน (AB, BC, CA)
** = P อยู่ในสามเหลี่ยม
**
** เครื่องหมายจะเป็นบวกทั้งสามหรือลบทั้งสาม ขึ้นกับว่า A,B,C
** เรียงตามเข็มหรือทวนเข็ม -> เลยต้องเช็คทั้ง 2 กรณี
**
** โจทย์บอก: อยู่บนขอบหรือเป็นจุดยอด -> return false
** -> ถ้า cross ตัวไหน = 0 ตอบ false ทันที
*/
static Fixed	cross(Point const &a, Point const &b, Point const &p)
{
	return ((b.getX() - a.getX()) * (p.getY() - a.getY())
		- (b.getY() - a.getY()) * (p.getX() - a.getX()));
}

bool	bsp(Point const a, Point const b, Point const c, Point const point)
{
	Fixed const	zero(0);
	Fixed const	d1 = cross(a, b, point);
	Fixed const	d2 = cross(b, c, point);
	Fixed const	d3 = cross(c, a, point);

	if (d1 == zero || d2 == zero || d3 == zero)
		return (false);

	bool	allNegative = (d1 < zero) && (d2 < zero) && (d3 < zero);
	bool	allPositive = (d1 > zero) && (d2 > zero) && (d3 > zero);

	return (allNegative || allPositive);
}
