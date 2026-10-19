#include "DiamondTrap.hpp"

int	main(void)
{
	std::cout << "--- construction: ClapTrap only once ---" << std::endl;
	DiamondTrap	diamond("Shiny");

	std::cout << std::endl << "--- who am I ---" << std::endl;
	diamond.whoAmI();

	std::cout << std::endl << "--- attack comes from ScavTrap ---" << std::endl;
	diamond.attack("a monster");

	std::cout << std::endl << "--- special abilities from both parents ---" << std::endl;
	diamond.guardGate();
	diamond.highFivesGuys();

	std::cout << std::endl << "--- stats: HP 100 (Frag), EP 50 (Scav), AD 30 (Frag) ---" << std::endl;
	diamond.takeDamage(99);
	diamond.beRepaired(1);
	for (int i = 0; i < 48; i ++)
		diamond.attack("x");
	diamond.attack("out of energy");

	std::cout << std::endl << "--- copy ---" << std::endl;
	DiamondTrap	copy(diamond);
	copy.whoAmI();

	std::cout << std::endl << "--- destruction ---" << std::endl;
	return (0);
}
