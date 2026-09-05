#include <iostream>
#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"

int	main(void)
{
	std::cout << "=== ScavTrap ===" << std::endl;
	{
		ScavTrap	scav("Serena");

		scav.attack("a skag");
		scav.guardGate();
		std::cout << "stats: " << scav.getHitPoints() << "/"
				  << scav.getEnergyPoints() << "/"
				  << scav.getAttackDamage() << " (คาด 100/49/20)" << std::endl;
	}

	std::cout << std::endl << "=== FragTrap ===" << std::endl;
	{
		FragTrap	frag("Frenzy");

		frag.attack("a psycho");
		frag.highFivesGuys();
		std::cout << "stats: " << frag.getHitPoints() << "/"
				  << frag.getEnergyPoints() << "/"
				  << frag.getAttackDamage() << " (คาด 100/99/30)" << std::endl;
	}

	std::cout << std::endl
			  << "=== พี่น้องคนละสาย: FragTrap ไม่รู้จัก guardGate ==="
			  << std::endl;
	std::cout << "ทั้งคู่สืบทอดจาก ClapTrap แต่ไม่ได้สืบทอดจากกัน" << std::endl;
	return (0);
}
