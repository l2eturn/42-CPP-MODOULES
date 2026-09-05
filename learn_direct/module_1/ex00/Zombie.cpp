#include <iostream>
#include "Zombie.hpp"

Zombie::Zombie(std::string name) : _name(name)
{
	std::cout << _name << ": is born" << std::endl;
}

/*
** destructor พิมพ์ชื่อ = เครื่องมือ debug ที่ดีที่สุดของโมดูลนี้
** มันบอกเราชัดๆ ว่า object ตายเมื่อไหร่ -- ซึ่งคือหัวใจของ stack vs heap
*/
Zombie::~Zombie(void)
{
	std::cout << _name << ": is destroyed" << std::endl;
}

void	Zombie::announce(void)
{
	std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
