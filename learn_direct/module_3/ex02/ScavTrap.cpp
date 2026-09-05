#include <iostream>
#include "ScavTrap.hpp"

/*
** : ClapTrap(name)  <-- เรียก constructor ของแม่ใน initialization list
** ถ้าไม่เขียน compiler จะเรียก ClapTrap() (default) ให้แทน
** ซึ่งจะได้ชื่อ "default" ไม่ใช่ชื่อที่เราส่งมา
**
** ตั้งค่า stat ใน body ได้ เพราะ ClapTrap ctor ตั้งค่า default (10/10/0) ไปแล้ว
** เราแค่ "เขียนทับ" ให้เป็น 100/50/20 ตามที่โจทย์กำหนด
*/
ScavTrap::ScavTrap(void) : ClapTrap()
{
	_hitPoints = 100;
	_energyPoints = 50;
	_attackDamage = 20;
	std::cout << "ScavTrap default constructor called" << std::endl;
}

ScavTrap::ScavTrap(const std::string &name) : ClapTrap(name)
{
	_hitPoints = 100;
	_energyPoints = 50;
	_attackDamage = 20;
	std::cout << "ScavTrap " << _name << " constructor called" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &other) : ClapTrap(other)
{
	std::cout << "ScavTrap " << _name << " copy constructor called"
			  << std::endl;
}

/*
** ต้องเรียก ClapTrap::operator=(other) เพื่อ copy ส่วนของแม่ด้วย
** ถ้าลืม -> member ของแม่ (_name, _hitPoints, ...) จะไม่ถูก copy
*/
ScavTrap	&ScavTrap::operator=(const ScavTrap &other)
{
	std::cout << "ScavTrap copy assignment operator called" << std::endl;
	if (this != &other)
		ClapTrap::operator=(other);
	return (*this);
}

ScavTrap::~ScavTrap(void)
{
	std::cout << "ScavTrap " << _name << " destructor called" << std::endl;
}

void	ScavTrap::attack(const std::string &target)
{
	if (_hitPoints == 0)
	{
		std::cout << "ScavTrap " << _name << " is dead and can't attack"
				  << std::endl;
		return ;
	}
	if (_energyPoints == 0)
	{
		std::cout << "ScavTrap " << _name << " has no energy left to attack"
				  << std::endl;
		return ;
	}
	--_energyPoints;
	std::cout << "ScavTrap " << _name << " attacks " << target
			  << ", causing " << _attackDamage << " points of damage!"
			  << std::endl;
}

void	ScavTrap::guardGate(void)
{
	std::cout << "ScavTrap " << _name << " is now in Gate keeper mode"
			  << std::endl;
}
