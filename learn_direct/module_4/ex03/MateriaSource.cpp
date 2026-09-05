#include <iostream>
#include "MateriaSource.hpp"

const int	MateriaSource::_capacity;

MateriaSource::MateriaSource(void)
{
	for (int i = 0; i < _capacity; ++i)
		_templates[i] = NULL;
}

MateriaSource::MateriaSource(MateriaSource const &other) : IMateriaSource()
{
	for (int i = 0; i < _capacity; ++i)
		_templates[i] = NULL;
	_copyFrom(other);
}

MateriaSource	&MateriaSource::operator=(MateriaSource const &other)
{
	if (this != &other)
	{
		_clear();
		_copyFrom(other);
	}
	return (*this);
}

MateriaSource::~MateriaSource(void)
{
	_clear();
}

void	MateriaSource::_clear(void)
{
	for (int i = 0; i < _capacity; ++i)
	{
		delete _templates[i];
		_templates[i] = NULL;
	}
}

void	MateriaSource::_copyFrom(MateriaSource const &other)
{
	for (int i = 0; i < _capacity; ++i)
	{
		if (other._templates[i])
			_templates[i] = other._templates[i]->clone();
	}
}

/*
** "can know at most 4 Materias. They are not necessarily unique."
** -> ไม่ต้องเช็คว่าซ้ำ, เต็มแล้วก็ทิ้ง (แต่ต้อง delete ไม่ให้ leak)
*/
void	MateriaSource::learnMateria(AMateria *m)
{
	if (!m)
		return ;
	for (int i = 0; i < _capacity; ++i)
	{
		if (!_templates[i])
		{
			_templates[i] = m;
			return ;
		}
	}
	delete m;
}

/*
** คืน 0 (NULL) ถ้าไม่รู้จัก type -- ตามที่โจทย์กำหนด
** ค้นจากท้ายมาหน้าหรือหน้าไปท้ายก็ได้ ที่นี่หน้าไปท้าย = เจอตัวที่เรียนก่อน
*/
AMateria	*MateriaSource::createMateria(std::string const &type)
{
	for (int i = 0; i < _capacity; ++i)
	{
		if (_templates[i] && _templates[i]->getType() == type)
			return (_templates[i]->clone());
	}
	return (0);
}
