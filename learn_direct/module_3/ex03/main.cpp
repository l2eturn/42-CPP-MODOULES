#include <iostream>
#include "DiamondTrap.hpp"

int	main(void)
{
	std::cout << "=== สร้าง DiamondTrap: ClapTrap ถูกสร้างครั้งเดียว ==="
			  << std::endl;
	{
		DiamondTrap	diamond("Diamond");

		std::cout << std::endl << "--- ความสามารถที่ได้มาจากทั้งสองสาย ---"
				  << std::endl;
		diamond.whoAmI();
		diamond.guardGate();		// จาก ScavTrap
		diamond.highFivesGuys();	// จาก FragTrap
		diamond.attack("a bandit");	// using ScavTrap::attack -> ข้อความ ScavTrap
		diamond.takeDamage(40);		// จาก ClapTrap
		diamond.beRepaired(20);

		std::cout << std::endl
				  << "--- stats หลังโดนตี/ซ่อม (เริ่มต้นคือ 100/50/30) ---"
				  << std::endl;
		std::cout << "hp=" << diamond.getHitPoints()
				  << " energy=" << diamond.getEnergyPoints()
				  << " dmg=" << diamond.getAttackDamage() << std::endl;

		std::cout << std::endl
				  << "--- ออก scope: ดู dtor -- ClapTrap dtor ครั้งเดียว ---"
				  << std::endl;
	}

	std::cout << std::endl << "=== copy constructor ===" << std::endl;
	{
		DiamondTrap	original("Origin");
		DiamondTrap	copy(original);

		copy.whoAmI();
	}
	return (0);
}
