#include <iostream>
#include "AAnimal.hpp"

/*
** abstract class ยังมี constructor ได้ปกติ!
** มันถูกเรียกตอนสร้างคลาสลูก (เพื่อ init ส่วนของแม่)
** แค่ "เรียกสร้างเองโดยตรง" ไม่ได้เท่านั้น
*/
AAnimal::AAnimal(void) : _type("AAnimal")
{
	std::cout << "AAnimal default constructor" << std::endl;
}

AAnimal::AAnimal(const AAnimal &other) : _type(other._type)
{
	std::cout << "AAnimal copy constructor" << std::endl;
}

AAnimal	&AAnimal::operator=(const AAnimal &other)
{
	std::cout << "AAnimal copy assignment operator" << std::endl;
	if (this != &other)
		_type = other._type;
	return (*this);
}

AAnimal::~AAnimal(void)
{
	std::cout << "AAnimal destructor" << std::endl;
}

const std::string	&AAnimal::getType(void) const
{
	return (_type);
}
