#include <iostream>
#include "Character.hpp"

const int	Character::_slots;
const int	Character::_floorSize;

Character::Character(void) : _name("unnamed"), _floorCount(0)
{
	for (int i = 0; i < _slots; ++i)
		_inventory[i] = NULL;
	for (int i = 0; i < _floorSize; ++i)
		_floor[i] = NULL;
}

Character::Character(std::string const &name) : _name(name), _floorCount(0)
{
	for (int i = 0; i < _slots; ++i)
		_inventory[i] = NULL;
	for (int i = 0; i < _floorSize; ++i)
		_floor[i] = NULL;
}

Character::Character(Character const &other) :
	ICharacter(), _name(other._name), _floorCount(0)
{
	for (int i = 0; i < _slots; ++i)
		_inventory[i] = NULL;
	for (int i = 0; i < _floorSize; ++i)
		_floor[i] = NULL;
	_copyInventoryFrom(other);
}

/*
** ลำดับสำคัญมาก:
**   1) กัน self-assignment
**   2) _clearInventory()  <-- ลบของเก่า *ก่อน* (โจทย์สั่ง)
**   3) clone ของใหม่เข้ามา
** ถ้าสลับ 2 กับ 3 -> ของเก่า leak
*/
Character	&Character::operator=(Character const &other)
{
	if (this != &other)
	{
		_clearInventory();
		_name = other._name;
		_copyInventoryFrom(other);
	}
	return (*this);
}

Character::~Character(void)
{
	_clearInventory();
	for (int i = 0; i < _floorCount; ++i)
		delete _floor[i];
}

void	Character::_clearInventory(void)
{
	for (int i = 0; i < _slots; ++i)
	{
		delete _inventory[i];
		_inventory[i] = NULL;
	}
}

/*
** DEEP COPY ด้วย clone():
** _inventory[i] = other._inventory[i]        <-- ผิด! shallow = double free
** _inventory[i] = other._inventory[i]->clone() <-- ถูก ได้ของใหม่ชนิดเดียวกัน
*/
void	Character::_copyInventoryFrom(Character const &other)
{
	for (int i = 0; i < _slots; ++i)
	{
		if (other._inventory[i])
			_inventory[i] = other._inventory[i]->clone();
	}
}

std::string const	&Character::getName(void) const
{
	return (_name);
}

/*
** "equip in the first empty slot they find, from slot 0 to slot 3"
** "if they try to add a Materia to a full inventory ... nothing should happen"
** -> เต็มแล้ว return เฉยๆ (แต่ระวัง: m ที่ส่งมาจะหลุดมือ -> เก็บลงพื้นแทน)
*/
void	Character::equip(AMateria *m)
{
	if (!m)
		return ;
	for (int i = 0; i < _slots; ++i)
	{
		if (_inventory[i] == m)
			return ;
	}
	for (int i = 0; i < _slots; ++i)
	{
		if (!_inventory[i])
		{
			_inventory[i] = m;
			return ;
		}
	}
	if (_floorCount < _floorSize)
		_floor[_floorCount++] = m;
}

/*
** โจทย์: "The unequip() member function must NOT delete the Materia!"
** -> แค่ตัดการอ้างอิงออกจาก inventory
** เก็บ pointer ไว้ที่ _floor เพื่อ delete ตอน dtor = ไม่ leak แต่ก็ไม่ delete ตรงนี้
*/
void	Character::unequip(int idx)
{
	if (idx < 0 || idx >= _slots || !_inventory[idx])
		return ;
	if (_floorCount < _floorSize)
		_floor[_floorCount++] = _inventory[idx];
	_inventory[idx] = NULL;
}

/*
** "use/unequip a non-existent Materia -> nothing should happen (but bugs are
**  still forbidden)" -> ต้องเช็ค range และเช็ค NULL ทั้งคู่
*/
void	Character::use(int idx, ICharacter &target)
{
	if (idx < 0 || idx >= _slots || !_inventory[idx])
		return ;
	_inventory[idx]->use(target);
}
