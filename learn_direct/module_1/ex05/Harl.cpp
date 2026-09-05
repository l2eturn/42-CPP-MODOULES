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

/*
** ตาราง 2 อัน (levels + functions) ที่ index ตรงกัน = lookup table
** หา index ของ level ที่ตรง แล้วเรียกฟังก์ชันที่ index เดียวกัน
**
** ข้อดีเทียบกับ if/else: เพิ่ม level ใหม่ = แก้แค่ 2 array ไม่ต้องแตะ logic
** และ logic การเลือกมีอยู่ที่เดียว
*/
void	Harl::complain(std::string level)
{
	const std::string	levels[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	void				(Harl::*functions[4])(void) = {
		&Harl::debug, &Harl::info, &Harl::warning, &Harl::error
	};

	for (int i = 0; i < 4; ++i)
	{
		if (levels[i] == level)
		{
			(this->*functions[i])();
			return ;
		}
	}
	std::cout << "[ Probably complaining about insignificant problems ]"
			  << std::endl;
}
