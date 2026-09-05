#include <iostream>
#include "ClapTrap.hpp"

ClapTrap::ClapTrap(void) :
	_name("default"), _hitPoints(10), _energyPoints(10), _attackDamage(0)
{
	std::cout << "ClapTrap default constructor called" << std::endl;
}

ClapTrap::ClapTrap(const std::string &name) :
	_name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0)
{
	std::cout << "ClapTrap " << _name << " constructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &other) :
	_name(other._name),
	_hitPoints(other._hitPoints),
	_energyPoints(other._energyPoints),
	_attackDamage(other._attackDamage)
{
	std::cout << "ClapTrap " << _name << " copy constructor called"
			  << std::endl;
}

ClapTrap	&ClapTrap::operator=(const ClapTrap &other)
{
	std::cout << "ClapTrap " << other._name
			  << " copy assignment operator called" << std::endl;
	if (this != &other)
	{
		_name = other._name;
		_hitPoints = other._hitPoints;
		_energyPoints = other._energyPoints;
		_attackDamage = other._attackDamage;
	}
	return (*this);
}

ClapTrap::~ClapTrap(void)
{
	std::cout << "ClapTrap " << _name << " destructor called" << std::endl;
}

/*
** "ClapTrap can't do anything if it has no hit points or energy points left"
** -> เช็คทั้ง 2 เงื่อนไขก่อนทำงานทุกครั้ง
*/
void	ClapTrap::attack(const std::string &target)
{
	if (_hitPoints == 0)
	{
		std::cout << "ClapTrap " << _name
				  << " is dead and can't attack" << std::endl;
		return ;
	}
	if (_energyPoints == 0)
	{
		std::cout << "ClapTrap " << _name
				  << " has no energy left to attack" << std::endl;
		return ;
	}
	--_energyPoints;
	std::cout << "ClapTrap " << _name << " attacks " << target
			  << ", causing " << _attackDamage << " points of damage!"
			  << std::endl;
}

/*
** ระวัง underflow ของ unsigned:
** ถ้า _hitPoints = 3 แล้วโดน 10 -> 3 - 10 จะได้เลขมหาศาล ไม่ใช่ 0
** -> ต้อง clamp ที่ 0
*/
void	ClapTrap::takeDamage(unsigned int amount)
{
	if (_hitPoints == 0)
	{
		std::cout << "ClapTrap " << _name << " is already dead" << std::endl;
		return ;
	}
	if (amount >= _hitPoints)
		_hitPoints = 0;
	else
		_hitPoints -= amount;
	std::cout << "ClapTrap " << _name << " takes " << amount
			  << " points of damage! (" << _hitPoints << " hit points left)"
			  << std::endl;
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	if (_hitPoints == 0)
	{
		std::cout << "ClapTrap " << _name
				  << " is dead and can't be repaired" << std::endl;
		return ;
	}
	if (_energyPoints == 0)
	{
		std::cout << "ClapTrap " << _name
				  << " has no energy left to repair itself" << std::endl;
		return ;
	}
	--_energyPoints;
	_hitPoints += amount;
	std::cout << "ClapTrap " << _name << " repairs itself for " << amount
			  << " hit points! (" << _hitPoints << " hit points, "
			  << _energyPoints << " energy left)" << std::endl;
}
