#ifndef ICHARACTER_HPP
# define ICHARACTER_HPP

# include <string>

class AMateria;

/*
** ============ INTERFACE ใน C++98 ============
** C++98 (และ C++20) ไม่มี keyword `interface`
** เราใช้ "pure abstract class" แทน = ทุก method เป็น pure virtual, ไม่มี data member
**
** สังเกต 2 อย่างที่ต้องมีทุกครั้ง:
**   1) virtual ~ICharacter() {}   <-- virtual dtor ที่มี body ว่างๆ
**      จำเป็น! เพราะเราจะ delete ผ่าน ICharacter* -> ถ้าไม่ virtual จะ leak
**   2) = 0 ทุกตัว -> บังคับให้คลาสที่ implement เขียนให้ครบทุกตัว
**
** class AMateria;  <-- FORWARD DECLARATION
** บอก compiler แค่ว่า "มี class ชื่อนี้อยู่" พอสำหรับใช้เป็น pointer/reference
** ทำไมไม่ #include "AMateria.hpp"? เพราะ AMateria.hpp ก็ต้องใช้ ICharacter
** -> include ไปกลับกันจะเป็น circular dependency
*/
class ICharacter
{
	public:
		virtual ~ICharacter(void) {}

		virtual std::string const	&getName(void) const = 0;
		virtual void				equip(AMateria *m) = 0;
		virtual void				unequip(int idx) = 0;
		virtual void				use(int idx, ICharacter &target) = 0;
};

#endif
