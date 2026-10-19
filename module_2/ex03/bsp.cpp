#include "Point.hpp"

// cross product of (b - a) x (p - a)
// > 0 : p is on the left of a->b, < 0 : right, == 0 : on the line
static Fixed	cross(Point const &a, Point const &b, Point const &p)
{
	return ((b.getX() - a.getX()) * (p.getY() - a.getY())
		- (b.getY() - a.getY()) * (p.getX() - a.getX()));
}

bool	bsp(Point const a, Point const b, Point const c, Point const point)
{
	Fixed	d1 = cross(a, b, point);
	Fixed	d2 = cross(b, c, point);
	Fixed	d3 = cross(c, a, point);
	Fixed	zero(0);

	if (d1 == zero || d2 == zero || d3 == zero)
		return (false);
	bool	allPositive = (d1 > zero && d2 > zero && d3 > zero);
	bool	allNegative = (d1 < zero && d2 < zero && d3 < zero);
	return (allPositive || allNegative);
}
