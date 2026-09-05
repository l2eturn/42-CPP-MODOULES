#include <iostream>
#include "Ice.hpp"

Ice::Ice(void) : AMateria("ice")
{
}

Ice::Ice(Ice const &other) : AMateria(other)
{
}

Ice	&Ice::operator=(Ice const &other)
{
	AMateria::operator=(other);
	return (*this);
}

Ice::~Ice(void)
{
}

/*
** clone: new Ice(*this) -> ใช้ copy constructor สร้างตัวใหม่ที่เหมือนกัน
** ผู้เรียกเป็นเจ้าของ pointer ที่ได้ -> ต้อง delete เอง
*/
AMateria	*Ice::clone(void) const
{
	return (new Ice(*this));
}

void	Ice::use(ICharacter &target)
{
	std::cout << "* shoots an ice bolt at " << target.getName() << " *"
			  << std::endl;
}
