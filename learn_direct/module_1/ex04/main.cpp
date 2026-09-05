#include <iostream>
#include "Replacer.hpp"

int	main(int argc, char **argv)
{
	if (argc != 4)
	{
		std::cerr << "Usage: " << argv[0] << " <filename> <s1> <s2>"
				  << std::endl;
		return (1);
	}

	Replacer	replacer(argv[2], argv[3]);

	return (replacer.run(argv[1]) ? 0 : 1);
}
