#include <iostream>
#include "Animal.hpp"

Animal::Animal(void) : _type("Animal")
{
	std::cout << "Animal default constructor" << std::endl;
}

Animal::Animal(const Animal &other) : _type(other._type)
{
	std::cout << "Animal copy constructor" << std::endl;
}

Animal	&Animal::operator=(const Animal &other)
{
	std::cout << "Animal copy assignment operator" << std::endl;
	if (this != &other)
		_type = other._type;
	return (*this);
}

Animal::~Animal(void)
{
	std::cout << "Animal destructor" << std::endl;
}

void	Animal::makeSound(void) const
{
	std::cout << "* animal noises *" << std::endl;
}

const std::string	&Animal::getType(void) const
{
	return (_type);
}
