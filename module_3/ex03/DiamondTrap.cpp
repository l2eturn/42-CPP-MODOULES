#include "DiamondTrap.hpp"

// ClapTrap is a virtual base, so DiamondTrap has to construct it itself (only once)
DiamondTrap::DiamondTrap(void)
	: ClapTrap("default_clap_name"), ScavTrap(), FragTrap(), _name("default")
{
	this->_hitPoints = 100;		// FragTrap
	this->_energyPoints = 50;	// ScavTrap
	this->_attackDamage = 30;	// FragTrap
	std::cout << "DiamondTrap default constructor called" << std::endl;
}

DiamondTrap::DiamondTrap(std::string name)
	: ClapTrap(name + "_clap_name"), ScavTrap(name), FragTrap(name), _name(name)
{
	this->_hitPoints = 100;		// FragTrap
	this->_energyPoints = 50;	// ScavTrap
	this->_attackDamage = 30;	// FragTrap
	std::cout << "DiamondTrap " << _name << " is constructed" << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap &other)
	: ClapTrap(other), ScavTrap(other), FragTrap(other), _name(other._name)
{
	std::cout << "DiamondTrap copy constructor called" << std::endl;
}

DiamondTrap	&DiamondTrap::operator=(const DiamondTrap &other)
{
	std::cout << "DiamondTrap copy assignment operator called" << std::endl;
	if (this != &other)
	{
		ClapTrap::operator=(other);
		this->_name = other._name;
	}
	return (*this);
}

DiamondTrap::~DiamondTrap(void)
{
	std::cout << "DiamondTrap " << _name << " is destroyed" << std::endl;
}

void	DiamondTrap::whoAmI()
{
	std::cout << "I am " << _name << ", my ClapTrap name is " << ClapTrap::_name << std::endl;
}
