#include <iostream>
#include "Dog.hpp"

/*
** ตั้ง _type ใน body (หรือใน init list ก็ได้ แต่ Animal() รันก่อนแล้วตั้งเป็น "Animal")
** -> เขียนทับเป็น "Dog"
*/
Dog::Dog(void)
{
	_type = "Dog";
	std::cout << "Dog constructor" << std::endl;
}

Dog::Dog(const Dog &other) : Animal(other)
{
	std::cout << "Dog copy constructor" << std::endl;
}

Dog	&Dog::operator=(const Dog &other)
{
	std::cout << "Dog copy assignment operator" << std::endl;
	if (this != &other)
		Animal::operator=(other);
	return (*this);
}

Dog::~Dog(void)
{
	std::cout << "Dog destructor" << std::endl;
}

void	Dog::makeSound(void) const
{
	std::cout << "Woof! Woof!" << std::endl;
}
