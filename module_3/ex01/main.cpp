#include "ScavTrap.hpp"

int	main(void)
{
	std::cout << "--- construction chain: ClapTrap -> ScavTrap ---" << std::endl;
	ScavTrap	scav("Serena");

	std::cout << std::endl << "--- actions ---" << std::endl;
	scav.attack("a bandit");
	scav.takeDamage(30);
	scav.beRepaired(10);
	scav.guardGate();

	std::cout << std::endl << "--- ClapTrap still works ---" << std::endl;
	ClapTrap	clap("Clappy");
	clap.attack("a bandit");

	std::cout << std::endl << "--- copy ---" << std::endl;
	ScavTrap	copy(scav);
	copy.attack("a copy target");

	std::cout << std::endl << "--- delete through ClapTrap pointer ---" << std::endl;
	ClapTrap	*ptr = new ScavTrap("Heap");
	ptr->attack("someone");
	delete ptr;

	std::cout << std::endl << "--- destruction chain: ScavTrap -> ClapTrap ---" << std::endl;
	return (0);
}
