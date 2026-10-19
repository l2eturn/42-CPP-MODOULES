#include <iostream>
#include "Point.hpp"

static void	test(const char *label, Point const &p, bool expected)
{
	Point const	a(0.0f, 0.0f);
	Point const	b(10.0f, 0.0f);
	Point const	c(0.0f, 10.0f);
	bool		result = bsp(a, b, c, p);

	std::cout << label << " (" << p.getX() << ", " << p.getY() << ") -> "
			  << (result ? "inside" : "outside")
			  << (result == expected ? "  [OK]" : "  [KO]") << std::endl;
}

int	main(void)
{
	std::cout << "triangle: (0,0) (10,0) (0,10)" << std::endl;
	test("inside      ", Point(1.0f, 1.0f), true);
	test("inside      ", Point(3.3f, 4.4f), true);
	test("outside     ", Point(10.0f, 10.0f), false);
	test("outside     ", Point(-1.0f, 2.0f), false);
	test("vertex      ", Point(0.0f, 0.0f), false);
	test("on edge     ", Point(5.0f, 0.0f), false);
	test("on hypotenuse", Point(5.0f, 5.0f), false);
	return (0);
}
