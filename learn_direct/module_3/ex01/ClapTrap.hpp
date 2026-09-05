#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

# include <string>

/*
** ex01+ - ClapTrap ต้องเปลี่ยน private -> PROTECTED
** โจทย์บอกตรงๆ ว่า "ScavTrap will use the attributes of ClapTrap
** (update ClapTrap accordingly)"
**
** ===== private vs protected vs public =====
**   private   : เฉพาะ class ตัวเอง (คลาสลูกก็แตะไม่ได้)
**   protected : class ตัวเอง + คลาสลูกทุกชั้น
**   public    : ใครก็ได้
**
** destructor เป็น virtual: ไม่ได้บังคับในโจทย์ แต่ควรทำทุกครั้งที่คลาสมีลูก
** เพราะถ้า  ClapTrap *p = new ScavTrap("x"); delete p;
** โดยที่ dtor ไม่ virtual -> เรียกแค่ ~ClapTrap ไม่เรียก ~ScavTrap = leak
** (เรื่องนี้จะเป็นหัวใจของ module 04)
*/
class ClapTrap
{
	public:
		ClapTrap(void);
		ClapTrap(const std::string &name);
		ClapTrap(const ClapTrap &other);
		ClapTrap			&operator=(const ClapTrap &other);
		virtual ~ClapTrap(void);

		void	attack(const std::string &target);
		void	takeDamage(unsigned int amount);
		void	beRepaired(unsigned int amount);

		const std::string	&getName(void) const;
		unsigned int		getHitPoints(void) const;
		unsigned int		getEnergyPoints(void) const;
		unsigned int		getAttackDamage(void) const;

	protected:
		std::string		_name;
		unsigned int	_hitPoints;
		unsigned int	_energyPoints;
		unsigned int	_attackDamage;
};

#endif
