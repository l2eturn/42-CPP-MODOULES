#include <iostream>
#include "WrongCat.hpp"

WrongCat::WrongCat(void)
{
	_type = "WrongCat";
	std::cout << "WrongCat constructor" << std::endl;
}

WrongCat::WrongCat(const WrongCat &other) : WrongAnimal(other)
{
	std::cout << "WrongCat copy constructor" << std::endl;
}

WrongCat	&WrongCat::operator=(const WrongCat &other)
{
	std::cout << "WrongCat copy assignment operator" << std::endl;
	if (this != &other)
		WrongAnimal::operator=(other);
	return (*this);
}

WrongCat::~WrongCat(void)
{
	std::cout << "WrongCat destructor" << std::endl;
}

void	WrongCat::makeSound(void) const
{
	std::cout << "Meow! (แต่คุณจะไม่ได้เห็นบรรทัดนี้ผ่าน WrongAnimal*)"
			  << std::endl;
}
