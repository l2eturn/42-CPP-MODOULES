#include "Character.hpp"

Character::Character(void) : _name("nobody")
{
	for (int i = 0; i < 4; i ++)
		_inventory[i] = NULL;
}

Character::Character(std::string const &name) : _name(name)
{
	for (int i = 0; i < 4; i ++)
		_inventory[i] = NULL;
}

// deep copy: clone every materia instead of sharing pointers
Character::Character(const Character &other) : _name(other._name)
{
	for (int i = 0; i < 4; i ++)
	{
		if (other._inventory[i])
			_inventory[i] = other._inventory[i]->clone();
		else
			_inventory[i] = NULL;
	}
}

Character	&Character::operator=(const Character &other)
{
	if (this != &other)
	{
		this->_name = other._name;
		clearInventory();
		for (int i = 0; i < 4; i ++)
		{
			if (other._inventory[i])
				_inventory[i] = other._inventory[i]->clone();
		}
	}
	return (*this);
}

Character::~Character(void)
{
	clearInventory();
}

void	Character::clearInventory()
{
	for (int i = 0; i < 4; i ++)
	{
		delete _inventory[i];
		_inventory[i] = NULL;
	}
}

std::string const	&Character::getName() const
{
	return (_name);
}

void	Character::equip(AMateria *m)
{
	if (m == NULL)
		return ;
	for (int i = 0; i < 4; i ++)
	{
		if (_inventory[i] == m)
			return ;
	}
	for (int i = 0; i < 4; i ++)
	{
		if (_inventory[i] == NULL)
		{
			_inventory[i] = m;
			return ;
		}
	}
}

// does NOT delete: the caller must keep the address and delete it
void	Character::unequip(int idx)
{
	if (idx < 0 || idx >= 4)
		return ;
	_inventory[idx] = NULL;
}

void	Character::use(int idx, ICharacter &target)
{
	if (idx < 0 || idx >= 4 || _inventory[idx] == NULL)
		return ;
	_inventory[idx]->use(target);
}

AMateria	*Character::getMateria(int idx) const
{
	if (idx < 0 || idx >= 4)
		return (NULL);
	return (_inventory[idx]);
}
