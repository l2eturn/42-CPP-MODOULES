#ifndef CHARACTER_HPP
# define CHARACTER_HPP

# include "AMateria.hpp"
# include "ICharacter.hpp"

/*
** Character implement ICharacter (pure abstract) -> ต้องเขียนครบทุก method
**
** ===== OWNERSHIP: ใครเป็นเจ้าของ materia? =====
** _inventory[4] เป็น AMateria* -> Character "เป็นเจ้าของ" ของที่ equip อยู่
**   equip()    -> รับ ownership เข้ามา
**   unequip()  -> "ปล่อย" ownership โดย *ไม่* delete (โจทย์สั่งชัดเจน)
**                 -> ของหลุดมือ = ใครก็ไม่ได้ถือ = leak ถ้าไม่มีคนเก็บ!
**   dtor       -> delete ทุกช่องที่ยังมีของ
**
** ===== วิธีจัดการ unequip ไม่ให้ leak =====
** โจทย์บอก "handle the Materias your character leaves on the floor as you like"
** ที่นี่ใช้ "พื้น" (_floor) เก็บของที่ถูก unequip ไว้ แล้ว delete ตอน dtor
** -> ตรงตามโจทย์ (ไม่ delete ใน unequip) และไม่ leak
**
** ===== deep copy =====
** โจทย์: "Any copy of a Character must be deep"
** และ "During copy, the Materias of a Character must be deleted before
**      the new ones are added" -> operator= ต้องล้างของเก่าก่อน clone ของใหม่
** ใช้ clone() ทำ deep copy: ไม่ต้องรู้ว่าเป็น Ice หรือ Cure ก็ copy ถูกชนิดได้
*/
class Character : public ICharacter
{
	public:
		Character(void);
		Character(std::string const &name);
		Character(Character const &other);
		Character	&operator=(Character const &other);
		virtual ~Character(void);

		virtual std::string const	&getName(void) const;
		virtual void				equip(AMateria *m);
		virtual void				unequip(int idx);
		virtual void				use(int idx, ICharacter &target);

	private:
		static const int	_slots = 4;
		static const int	_floorSize = 32;

		std::string	_name;
		AMateria	*_inventory[_slots];
		AMateria	*_floor[_floorSize];
		int			_floorCount;

		void	_clearInventory(void);
		void	_copyInventoryFrom(Character const &other);
};

#endif
