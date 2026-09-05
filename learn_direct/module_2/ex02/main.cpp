#include <iostream>
#include "Fixed.hpp"

int	main(void)
{
	Fixed			a;
	Fixed const		b(Fixed(5.05f) * Fixed(2));

	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << Fixed::max(a, b) << std::endl;

	std::cout << "--- comparison ---" << std::endl;
	std::cout << "a < b  : " << (a < b) << std::endl;
	std::cout << "a == a : " << (a == a) << std::endl;
	std::cout << "a != b : " << (a != b) << std::endl;

	std::cout << "--- arithmetic ---" << std::endl;
	std::cout << "10 + 3   = " << (Fixed(10) + Fixed(3)) << std::endl;
	std::cout << "10 - 3   = " << (Fixed(10) - Fixed(3)) << std::endl;
	std::cout << "10 * 3   = " << (Fixed(10) * Fixed(3)) << std::endl;
	std::cout << "10 / 3   = " << (Fixed(10) / Fixed(3)) << std::endl;
	std::cout << "1.5 * 2  = " << (Fixed(1.5f) * Fixed(2)) << std::endl;

	std::cout << "--- min / max (const overload) ---" << std::endl;
	Fixed const	x(3);
	Fixed const	y(7);
	std::cout << "min = " << Fixed::min(x, y) << std::endl;
	std::cout << "max = " << Fixed::max(x, y) << std::endl;

	std::cout << "--- epsilon ---" << std::endl;
	Fixed	eps;
	++eps;
	std::cout << "smallest step = " << eps
			  << " (raw " << eps.getRawBits() << ")" << std::endl;
	return (0);
}
