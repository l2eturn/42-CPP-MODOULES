#include "ClapTrap.hpp"

int	main(void)
{
	ClapTrap	clap("Clappy");

	std::cout << std::endl << "--- normal actions ---" << std::endl;
	clap.attack("a target dummy");
	clap.takeDamage(3);
	clap.beRepaired(2);

	std::cout << std::endl << "--- run out of energy ---" << std::endl;
	for (int i = 0; i < 9; i ++)
		clap.attack("a wall");
	clap.beRepaired(1);

	std::cout << std::endl << "--- copy ---" << std::endl;
	ClapTrap	copy(clap);
	ClapTrap	other("Other");
	other = clap;

	std::cout << std::endl << "--- take lethal damage ---" << std::endl;
	ClapTrap	weak("Weak");
	weak.takeDamage(100);
	weak.takeDamage(1);
	weak.attack("anyone");
	weak.beRepaired(5);

	std::cout << std::endl << "--- end of main ---" << std::endl;
	return (0);
}
