#include "AMateria.hpp"

AMateria::AMateria(void) : _type("")
{
}

AMateria::AMateria(std::string const &type) : _type(type)
{
}

AMateria::AMateria(const AMateria &other) : _type(other._type)
{
}

// copying the type doesn't make sense (an Ice stays an Ice)
AMateria	&AMateria::operator=(const AMateria &other)
{
	(void)other;
	return (*this);
}

AMateria::~AMateria(void)
{
}

std::string const	&AMateria::getType() const
{
	return (_type);
}

void	AMateria::use(ICharacter &target)
{
	std::cout << "* uses some materia on " << target.getName() << " *" << std::endl;
}
