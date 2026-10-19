#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int	main(void)
{
	std::cout << "--- construction chain: ClapTrap -> FragTrap ---" << std::endl;
	FragTrap	frag("Fraggy");

	std::cout << std::endl << "--- FragTrap actions ---" << std::endl;
	frag.attack("a skag");
	frag.takeDamage(40);
	frag.beRepaired(15);
	frag.highFivesGuys();

	std::cout << std::endl << "--- ScavTrap ---" << std::endl;
	ScavTrap	scav("Serena");
	scav.attack("a skag");
	scav.guardGate();

	std::cout << std::endl << "--- copy assignment ---" << std::endl;
	FragTrap	other("Other");
	other = frag;
	other.highFivesGuys();

	std::cout << std::endl << "--- destruction (reverse order) ---" << std::endl;
	return (0);
}
