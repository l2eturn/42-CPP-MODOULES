#ifndef AMATERIA_HPP
# define AMATERIA_HPP

# include <string>
# include "ICharacter.hpp"

/*
** AMateria = abstract class (ไม่ใช่ interface เพราะมี data member _type)
**
** ===== clone() = PROTOTYPE PATTERN =====
**   virtual AMateria *clone() const = 0;
** ทำให้เราสร้าง "ของชนิดเดียวกับตัวเอง" ได้ โดยไม่ต้องรู้ว่ามันชนิดอะไร
**   AMateria *m = something->clone();   // ได้ Ice ถ้า something เป็น Ice
** ถ้าไม่มี clone() เราต้องเขียน if (type=="ice") new Ice(); else if ... ไปเรื่อยๆ
** = MateriaSource จะรองรับชนิดใหม่ไม่ได้เลยโดยไม่แก้โค้ด
**
** ===== "copying the type doesn't make sense" =====
** โจทย์เตือนไว้ตรงๆ: operator= ต้อง *ไม่* copy _type
** เพราะ type คือ "ตัวตน" ของ materia -- Ice จะกลายเป็น Cure ไม่ได้
** (ถ้ามี attribute อื่นเช่น xp ค่อย copy อันนั้น)
** แต่ copy CONSTRUCTOR ต้อง copy type เพราะกำลังสร้างตัวใหม่ชนิดเดียวกัน
*/
class AMateria
{
	public:
		AMateria(void);
		AMateria(std::string const &type);
		AMateria(AMateria const &other);
		AMateria	&operator=(AMateria const &other);
		virtual ~AMateria(void);

		std::string const	&getType(void) const;

		virtual AMateria	*clone(void) const = 0;
		virtual void		use(ICharacter &target);

	protected:
		std::string	_type;
};

#endif
