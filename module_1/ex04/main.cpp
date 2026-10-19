#include <iostream>
#include "Replacer.hpp"

int	main(int ac, char **av)
{
	if (ac != 4)
	{
		std::cerr << "Usage: " << av[0] << " <filename> <s1> <s2>" << std::endl;
		return (1);
	}

	std::string	s1 = av[2];
	if (s1.empty())
	{
		std::cerr << "Error: s1 cannot be empty" << std::endl;
		return (1);
	}

	Replacer	replacer(av[1], s1, av[3]);
	if (!replacer.run())
		return (1);
	return (0);
}
