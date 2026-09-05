#ifndef HUMANA_HPP
# define HUMANA_HPP

# include <string>
# include "Weapon.hpp"

/*
** HumanA "มีอาวุธเสมอ" -> ใช้ REFERENCE
**
** เพราะ reference ต้องผูกกับของจริงตอนสร้าง และเปลี่ยนไปผูกตัวอื่นไม่ได้
** = compiler บังคับให้ตรงตามกฎ "always armed" ให้เราเลย
** reference member ต้อง init ใน initialization list เท่านั้น (assign ใน body ไม่ได้)
*/
class HumanA
{
	public:
		HumanA(std::string name, Weapon &weapon);
		~HumanA(void);

		void	attack(void) const;

	private:
		std::string	_name;
		Weapon		&_weapon;
};

#endif
