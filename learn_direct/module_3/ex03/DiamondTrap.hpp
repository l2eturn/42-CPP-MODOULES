#ifndef DIAMONDTRAP_HPP
# define DIAMONDTRAP_HPP

# include "FragTrap.hpp"
# include "ScavTrap.hpp"

/*
** ===================================================================
**  ex03 - THE DIAMOND PROBLEM  (ข้อที่ยากที่สุดของ module 03)
** ===================================================================
**
**          ClapTrap
**          /      \
**   ScavTrap      FragTrap
**          \      /
**         DiamondTrap
**
** ปัญหา: ถ้าสืบทอดธรรมดา DiamondTrap จะมี ClapTrap *สองชุด*
** (ชุดหนึ่งมาทาง ScavTrap อีกชุดมาทาง FragTrap)
** -> _name จะมี 2 ตัว, hp มี 2 ตัว, ctor/dtor ของ ClapTrap ถูกเรียก 2 ครั้ง
** -> แถมเรียก _name เฉยๆ จะ ambiguous คอมไพล์ไม่ผ่าน
**
** ===== ทางแก้ที่ 1: VIRTUAL INHERITANCE =====
** ใน ScavTrap.hpp / FragTrap.hpp เปลี่ยนเป็น:
**     class ScavTrap : virtual public ClapTrap
**     class FragTrap : virtual public ClapTrap
**
** ผลคือ ClapTrap ถูกแชร์เป็น "ชุดเดียว" -> ตรงกับที่โจทย์บอกว่า
** "the ClapTrap instance of DiamondTrap will be created once, and only once"
** นี่คือ "trick" ที่โจทย์ใบ้ไว้
**
** กฎพิเศษของ virtual base: ผู้ที่เรียก constructor ของ virtual base
** คือ "คลาสที่ derived สุด" (DiamondTrap) ไม่ใช่ ScavTrap/FragTrap
** -> ที่ ScavTrap เขียน : ClapTrap(name) ไว้ มันจะถูก "ข้าม" ตอนสร้าง DiamondTrap
** -> DiamondTrap จึงต้องเรียก ClapTrap(name + "_clap_name") ด้วยตัวเอง
**
** ===== ทางแก้ที่ 2: ambiguity ของ attack() =====
** ScavTrap มี attack() ของตัวเอง / FragTrap ใช้ของ ClapTrap
** -> d.attack() จึงกำกวมว่าเอาตัวไหน = compile error
** -> using ScavTrap::attack;  บอกชัดๆ ว่า "เอาของ ScavTrap"
**    (โจทย์กำหนดว่า attack() ต้องมาจาก ScavTrap)
**
** ===== _name ที่ชื่อซ้ำกับแม่ (โจทย์บังคับ) =====
** DiamondTrap::_name  ทับ (shadow) ClapTrap::_name
** ในโค้ดของ DiamondTrap:  _name            = ของ DiamondTrap
**                         ClapTrap::_name   = ของแม่ (ต้องระบุ scope)
** -> ลอง compile ด้วย -Wshadow ดูจะเห็น warning ตรงนี้
*/
class DiamondTrap : public ScavTrap, public FragTrap
{
	public:
		DiamondTrap(void);
		DiamondTrap(const std::string &name);
		DiamondTrap(const DiamondTrap &other);
		DiamondTrap	&operator=(const DiamondTrap &other);
		virtual ~DiamondTrap(void);

		using ScavTrap::attack;

		void	whoAmI(void);

	private:
		std::string	_name;
};

#endif
