#include <iostream>
#include "DiamondTrap.hpp"

/*
** ลำดับใน initialization list ต้องเรียงตามลำดับที่ compiler สร้างจริง:
**   virtual base ก่อน (ClapTrap) -> base ตามลำดับประกาศ (ScavTrap, FragTrap)
**   -> member ของตัวเอง (_name)
** ถ้าเรียงผิด -Wall จะเตือน -Wreorder (และ -Werror จะทำให้ build fail)
**
** ค่าที่โจทย์กำหนดสำหรับ DiamondTrap:
**   hit points   จาก FragTrap  = 100
**   energy points จาก ScavTrap = 50
**   attack damage จาก FragTrap = 30
** ตั้งใน body เพราะ FragTrap ctor จะเขียนทับ energy เป็น 100 ไปแล้ว
** (ScavTrap ctor รันก่อน แล้ว FragTrap ctor รันทับ -> ต้องแก้ทีหลังสุด)
*/
DiamondTrap::DiamondTrap(void) :
	ClapTrap("default_clap_name"), ScavTrap(), FragTrap(), _name("default")
{
	_hitPoints = 100;
	_energyPoints = 50;
	_attackDamage = 30;
	std::cout << "DiamondTrap default constructor called" << std::endl;
}

DiamondTrap::DiamondTrap(const std::string &name) :
	ClapTrap(name + "_clap_name"), ScavTrap(name), FragTrap(name), _name(name)
{
	_hitPoints = 100;
	_energyPoints = 50;
	_attackDamage = 30;
	std::cout << "DiamondTrap " << _name << " constructor called" << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap &other) :
	ClapTrap(other), ScavTrap(other), FragTrap(other), _name(other._name)
{
	std::cout << "DiamondTrap " << _name << " copy constructor called"
			  << std::endl;
}

DiamondTrap	&DiamondTrap::operator=(const DiamondTrap &other)
{
	std::cout << "DiamondTrap copy assignment operator called" << std::endl;
	if (this != &other)
	{
		ClapTrap::operator=(other);
		_name = other._name;
	}
	return (*this);
}

DiamondTrap::~DiamondTrap(void)
{
	std::cout << "DiamondTrap " << _name << " destructor called" << std::endl;
}

/*
** _name           -> ของ DiamondTrap (ชื่อจริง)
** ClapTrap::_name -> ของแม่ (ชื่อ + "_clap_name")
** ต้องเขียน ClapTrap:: ให้ชัด ไม่งั้นจะได้ตัวที่ shadow อยู่
*/
void	DiamondTrap::whoAmI(void)
{
	std::cout << "I am DiamondTrap \"" << _name
			  << "\" and my ClapTrap name is \"" << ClapTrap::_name << "\""
			  << std::endl;
}
