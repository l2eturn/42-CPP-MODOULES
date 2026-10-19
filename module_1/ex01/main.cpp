#include <iostream>
#include "Zombie.hpp"

int	main(void)
{
	int		n = 5;
	Zombie	*horde = zombieHorde(n, "Foo");

	std::cout << "--- horde of " << n << " ---" << std::endl;
	for (int i = 0; i < n; i ++)
		horde[i].announce();
	delete [] horde;

	std::cout << std::endl << "--- N <= 0 ---" << std::endl;
	if (zombieHorde(0, "Nobody") == NULL)
		std::cout << "zombieHorde(0) returned NULL" << std::endl;
	return (0);
}
