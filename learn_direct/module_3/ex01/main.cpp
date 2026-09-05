#include <iostream>
#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int	main(void)
{
	std::cout << "=== สร้าง ClapTrap ธรรมดา ===" << std::endl;
	{
		ClapTrap	basic("Basic");
		basic.attack("a target");
	}

	std::cout << std::endl << "=== สร้าง ScavTrap (ดูลำดับ ctor) ==="
			  << std::endl;
	{
		ScavTrap	scav("Serena");

		scav.attack("a bandit");
		scav.takeDamage(30);
		scav.beRepaired(10);
		scav.guardGate();
		std::cout << "hp=" << scav.getHitPoints()
				  << " energy=" << scav.getEnergyPoints()
				  << " dmg=" << scav.getAttackDamage() << std::endl;
		std::cout << "--- ออก scope: ดูลำดับ dtor (กลับทาง) ---" << std::endl;
	}

	std::cout << std::endl << "=== กับดัก: เรียกผ่าน reference ของแม่ ==="
			  << std::endl;
	{
		ScavTrap	scav("Shadowed");
		ClapTrap	&asBase = scav;

		std::cout << "scav.attack()   -> ";
		scav.attack("X");
		std::cout << "asBase.attack() -> ";
		asBase.attack("X");
		std::cout << "^ ได้ข้อความของ ClapTrap เพราะ attack ไม่ใช่ virtual"
				  << std::endl;
	}
	return (0);
}
