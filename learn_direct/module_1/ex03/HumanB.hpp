#ifndef HUMANB_HPP
# define HUMANB_HPP

# include <string>
# include "Weapon.hpp"

/*
** HumanB "อาจไม่มีอาวุธ" -> ใช้ POINTER
**
** pointer เป็น NULL ได้ = แทน "ยังไม่มีอาวุธ" ได้
** และเปลี่ยนไปชี้อาวุธอื่นได้ = setWeapon() ทำได้
**
** สังเกต: _weapon เป็น Weapon* ที่ "ไม่ได้เป็นเจ้าของ" อาวุธ
** -> destructor ต้อง *ไม่* delete มัน เพราะ Weapon ถูกสร้างบน stack ข้างนอก
**    ใครสร้างคนนั้นทำลาย (ownership) -- เป็นกฎที่จะเจอไปตลอดใน C++
*/
class HumanB
{
	public:
		HumanB(std::string name);
		~HumanB(void);

		void	setWeapon(Weapon &weapon);
		void	attack(void) const;

	private:
		std::string	_name;
		Weapon		*_weapon;
};

#endif
