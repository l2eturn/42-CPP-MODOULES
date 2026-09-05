#include <iostream>
#include "Harl.hpp"

Harl::Harl(void)
{
}

Harl::~Harl(void)
{
}

void	Harl::debug(void)
{
	std::cout << "[ DEBUG ]" << std::endl
			  << "I love having extra bacon for my "
			  << "7XL-double-cheese-triple-pickle-special-ketchup burger. "
			  << "I really do!" << std::endl;
}

void	Harl::info(void)
{
	std::cout << "[ INFO ]" << std::endl
			  << "I cannot believe adding extra bacon costs more money. "
			  << "You didn't put enough bacon in my burger! "
			  << "If you did, I wouldn't be asking for more!" << std::endl;
}

void	Harl::warning(void)
{
	std::cout << "[ WARNING ]" << std::endl
			  << "I think I deserve to have some extra bacon for free. "
			  << "I've been coming for years, whereas you started working "
			  << "here just last month." << std::endl;
}

void	Harl::error(void)
{
	std::cout << "[ ERROR ]" << std::endl
			  << "This is unacceptable! I want to speak to the manager now."
			  << std::endl;
}

Harl::Level	Harl::parseLevel(const std::string &level)
{
	const std::string	names[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};

	for (int i = 0; i < 4; ++i)
	{
		if (names[i] == level)
			return (static_cast<Level>(i));
	}
	return (UNKNOWN);
}

void	Harl::complain(std::string level)
{
	switch (parseLevel(level))
	{
		case DEBUG:
			debug();
			// fall through -- ตั้งใจ ไม่ใส่ break
		case INFO:
			info();
			// fall through
		case WARNING:
			warning();
			// fall through
		case ERROR:
			error();
			break ;
		default:
			std::cout << "[ Probably complaining about insignificant problems ]"
					  << std::endl;
			break ;
	}
}
