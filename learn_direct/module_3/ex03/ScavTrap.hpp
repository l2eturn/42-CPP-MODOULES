#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

# include "ClapTrap.hpp"

/*
** ===== ลำดับการสร้าง / ทำลาย (คำถามที่ peer eval ถามแน่นอน) =====
** สร้าง ScavTrap:  ClapTrap ctor -> ScavTrap ctor   (จากฐานขึ้นไปหาลูก)
** ทำลาย ScavTrap:  ScavTrap dtor -> ClapTrap dtor   (กลับทาง)
**
** ทำไม? เพราะคลาสลูก "มี" ส่วนของคลาสแม่อยู่ในตัว และอาจใช้ member ของแม่
** -> ตอนสร้าง ส่วนของแม่ต้องพร้อมก่อน ลูกจึงจะใช้ได้
** -> ตอนทำลาย ลูกต้องเก็บของตัวเองให้เสร็จก่อน แม่จึงพังลงได้อย่างปลอดภัย
** (เหมือนสร้างบ้าน: ลงเสาเข็มก่อน มุงหลังคาทีหลัง / รื้อ: รื้อหลังคาก่อน)
**
** attack() ที่นี่ *ไม่ใช่* virtual override -- มันคือ "hiding" (ทับชื่อ)
** ผลคือ ScavTrap s; s.attack() เรียกของ ScavTrap
** แต่ ClapTrap &r = s; r.attack() เรียกของ ClapTrap!  <-- จำจุดนี้ไว้
** ถ้าอยากให้เรียกของ ScavTrap ต้องประกาศ attack เป็น virtual (module 04)
*/
class ScavTrap : virtual public ClapTrap
{
	public:
		ScavTrap(void);
		ScavTrap(const std::string &name);
		ScavTrap(const ScavTrap &other);
		ScavTrap	&operator=(const ScavTrap &other);
		virtual ~ScavTrap(void);

		void	attack(const std::string &target);
		void	guardGate(void);
};

#endif
