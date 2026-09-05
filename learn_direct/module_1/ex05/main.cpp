#include <iostream>
#include "Harl.hpp"

int	main(void)
{
	Harl	harl;

	harl.complain("DEBUG");
	harl.complain("INFO");
	harl.complain("WARNING");
	harl.complain("ERROR");
	std::cout << "--- level ที่ไม่รู้จัก ---" << std::endl;
	harl.complain("COFFEE");
	harl.complain("debug");
	return (0);
}
