#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

# include "ClapTrap.hpp"

/*
** FragTrap: 100 hp / 100 energy / 30 damage
** ต่างจาก ScavTrap แค่ค่า stat กับข้อความ -- แต่โจทย์ให้เขียนซ้ำเพื่อให้เห็นว่า
** inheritance ช่วยลด code ซ้ำได้แค่ไหน (และ "ยังซ้ำอยู่" ตรงไหน)
**
** โจทย์ไม่ได้บอกให้ override attack() -> FragTrap ใช้ attack() ของ ClapTrap
** จุดนี้สำคัญมากสำหรับ ex03 (เป็นเหตุให้เกิด ambiguity)
*/
class FragTrap : public ClapTrap
{
	public:
		FragTrap(void);
		FragTrap(const std::string &name);
		FragTrap(const FragTrap &other);
		FragTrap	&operator=(const FragTrap &other);
		virtual ~FragTrap(void);

		void	highFivesGuys(void);
};

#endif
