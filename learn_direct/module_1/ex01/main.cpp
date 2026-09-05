#include <iostream>
#include "Zombie.hpp"

int	main(void)
{
	const int	count = 5;
	Zombie		*horde = zombieHorde(count, "Horde");

	if (!horde)
		return (1);
	for (int i = 0; i < count; ++i)
		horde[i].announce();

	delete [] horde;

	std::cout << std::endl << "--- edge case: N = 0 ---" << std::endl;
	Zombie	*empty = zombieHorde(0, "Nobody");
	std::cout << "zombieHorde(0, ...) -> "
			  << (empty ? "pointer" : "NULL") << std::endl;
	delete [] empty;
	return (0);
}
