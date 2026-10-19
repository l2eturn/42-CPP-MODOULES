#include "Harl.hpp"

int	main(int ac, char **av)
{
	Harl	harl;

	if (ac != 2)
	{
		std::cerr << "Usage: " << av[0] << " <level>" << std::endl;
		return (1);
	}
	harl.filter(av[1]);
	return (0);
}
