#include <iostream>
#include "AMateria.hpp"

AMateria::AMateria(void) : _type("")
{
}

AMateria::AMateria(std::string const &type) : _type(type)
{
}

AMateria::AMateria(AMateria const &other) : _type(other._type)
{
}

/*
** ตั้งใจไม่ copy _type ตามที่โจทย์กำกับไว้
** (void)other กันไม่ให้ -Wunused-parameter ทำ build ตก
*/
AMateria	&AMateria::operator=(AMateria const &other)
{
	(void)other;
	return (*this);
}

AMateria::~AMateria(void)
{
}

std::string const	&AMateria::getType(void) const
{
	return (_type);
}

void	AMateria::use(ICharacter &target)
{
	(void)target;
}
