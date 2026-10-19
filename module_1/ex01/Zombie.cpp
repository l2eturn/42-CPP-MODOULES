#include "Zombie.hpp"

Zombie::Zombie(void) : _name("")
{
}

Zombie::Zombie(std::string name) : _name(name)
{
	std::cout << _name << ": is born" << std::endl;
}

Zombie::~Zombie(void)
{
	std::cout << _name << ": is destroyed" << std::endl;
}

void	Zombie::setName(std::string name)
{
	this->_name = name;
}

void	Zombie::announce()
{
	std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
