#include <iostream>
#include "Cat.hpp"

/*
** ตั้ง _type ใน body (หรือใน init list ก็ได้ แต่ Animal() รันก่อนแล้วตั้งเป็น "Animal")
** -> เขียนทับเป็น "Cat"
*/
Cat::Cat(void)
{
	_type = "Cat";
	std::cout << "Cat constructor" << std::endl;
}

Cat::Cat(const Cat &other) : Animal(other)
{
	std::cout << "Cat copy constructor" << std::endl;
}

Cat	&Cat::operator=(const Cat &other)
{
	std::cout << "Cat copy assignment operator" << std::endl;
	if (this != &other)
		Animal::operator=(other);
	return (*this);
}

Cat::~Cat(void)
{
	std::cout << "Cat destructor" << std::endl;
}

void	Cat::makeSound(void) const
{
	std::cout << "Meow! Meow!" << std::endl;
}
