#ifndef CLAPTRAP_HPP
# define CLAPTRAP_HPP

# include <string>

/*
** ex00 - ClapTrap เดี่ยวๆ ยังไม่มี inheritance
** โจทย์บอกว่า attribute เป็น private -> ex00 ใช้ private ได้
** (ex01 จะต้องเปลี่ยนเป็น protected เพราะคลาสลูกต้องใช้)
**
** ทำไม unsigned int? เพราะ hit points / energy ติดลบไม่มีความหมาย
** แต่ระวัง! unsigned ลบเกิน 0 จะ "วนกลับ" เป็นเลขมหาศาล (underflow)
**   0u - 1u  =  4294967295   <-- ไม่ใช่ -1
** -> takeDamage ต้องเช็คก่อนลบทุกครั้ง (ดูใน .cpp)
*/
class ClapTrap
{
	public:
		ClapTrap(void);
		ClapTrap(const std::string &name);
		ClapTrap(const ClapTrap &other);
		ClapTrap	&operator=(const ClapTrap &other);
		~ClapTrap(void);

		void	attack(const std::string &target);
		void	takeDamage(unsigned int amount);
		void	beRepaired(unsigned int amount);

	private:
		std::string		_name;
		unsigned int	_hitPoints;
		unsigned int	_energyPoints;
		unsigned int	_attackDamage;
};

#endif
