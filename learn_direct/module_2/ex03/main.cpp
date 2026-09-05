#include <iostream>
#include "Point.hpp"

static void	check(const char *label, Point const &a, Point const &b,
		Point const &c, Point const &p, bool expected)
{
	bool	result = bsp(a, b, c, p);

	std::cout << (result == expected ? "[ OK ] " : "[FAIL] ")
			  << label << " -> " << (result ? "inside" : "outside")
			  << " (คาดว่า " << (expected ? "inside" : "outside") << ")"
			  << std::endl;
}

int	main(void)
{
	Point const	a(0.0f, 0.0f);
	Point const	b(10.0f, 0.0f);
	Point const	c(0.0f, 10.0f);

	check("จุดกลางสามเหลี่ยม (2,2)", a, b, c, Point(2.0f, 2.0f), true);
	check("จุดข้างนอกไกลๆ (20,20)", a, b, c, Point(20.0f, 20.0f), false);
	check("จุดยอด A (0,0)", a, b, c, Point(0.0f, 0.0f), false);
	check("จุดยอด B (10,0)", a, b, c, Point(10.0f, 0.0f), false);
	check("บนขอบ AB (5,0)", a, b, c, Point(5.0f, 0.0f), false);
	check("บนขอบ BC (5,5)", a, b, c, Point(5.0f, 5.0f), false);
	check("นอกแบบเฉียดๆ (5,5.5)", a, b, c, Point(5.0f, 5.5f), false);
	check("ในแบบเฉียดๆ (5,4.5)", a, b, c, Point(5.0f, 4.5f), true);
	check("ลบ (-1,-1)", a, b, c, Point(-1.0f, -1.0f), false);

	std::cout << "--- สามเหลี่ยมเรียงกลับทาง (clockwise) ---" << std::endl;
	check("จุดกลาง (2,2)", a, c, b, Point(2.0f, 2.0f), true);
	check("ข้างนอก (20,20)", a, c, b, Point(20.0f, 20.0f), false);
	return (0);
}
