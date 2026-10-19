#include <iostream>
#include <string>

int	main(void)
{
	std::string	str = "HI THIS IS BRAIN";
	std::string	*stringPTR = &str;
	std::string	&stringREF = str;

	std::cout << "address of str       : " << &str << std::endl;
	std::cout << "address in stringPTR : " << stringPTR << std::endl;
	std::cout << "address of stringREF : " << &stringREF << std::endl;

	std::cout << "value of str         : " << str << std::endl;
	std::cout << "value at stringPTR   : " << *stringPTR << std::endl;
	std::cout << "value of stringREF   : " << stringREF << std::endl;
	return (0);
}
