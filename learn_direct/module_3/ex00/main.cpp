#include <iostream>
#include "ClapTrap.hpp"

int	main(void)
{
	ClapTrap	robot("CL4P-TP");

	robot.attack("the training dummy");
	robot.takeDamage(4);
	robot.beRepaired(2);

	std::cout << std::endl << "--- ใช้พลังงานให้หมด (เหลือ 8) ---" << std::endl;
	for (int i = 0; i < 9; ++i)
		robot.attack("the wall");

	std::cout << std::endl << "--- ตายแล้วทำอะไรไม่ได้ ---" << std::endl;
	ClapTrap	weak("Weakling");
	weak.takeDamage(100);
	weak.attack("someone");
	weak.beRepaired(50);

	std::cout << std::endl << "--- copy / assign ---" << std::endl;
	ClapTrap	copy(robot);
	ClapTrap	assigned;
	assigned = robot;

	std::cout << std::endl << "--- destructor เรียงกลับทางที่สร้าง ---"
			  << std::endl;
	return (0);
}
