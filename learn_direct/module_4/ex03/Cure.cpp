#include <iostream>
#include "Cure.hpp"

Cure::Cure(void) : AMateria("cure")
{
}

Cure::Cure(Cure const &other) : AMateria(other)
{
}

Cure	&Cure::operator=(Cure const &other)
{
	AMateria::operator=(other);
	return (*this);
}

Cure::~Cure(void)
{
}

/*
** clone: new Cure(*this) -> ใช้ copy constructor สร้างตัวใหม่ที่เหมือนกัน
** ผู้เรียกเป็นเจ้าของ pointer ที่ได้ -> ต้อง delete เอง
*/
AMateria	*Cure::clone(void) const
{
	return (new Cure(*this));
}

void	Cure::use(ICharacter &target)
{
	std::cout << "* heals " << target.getName() << "'s wounds *"
			  << std::endl;
}
