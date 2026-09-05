#include "HumanA.hpp"
#include "HumanB.hpp"
#include "Weapon.hpp"

/*
** ทำไม setType() แล้ว attack() ครั้งที่ 2 เปลี่ยนตาม?
** เพราะ HumanA ถือ reference และ HumanB ถือ pointer ไปที่ Weapon "ตัวเดียวกัน"
** ถ้าเก็บเป็น Weapon (by value) มันจะเป็นสำเนา -> จะไม่เปลี่ยนตาม
*/
int	main(void)
{
	{
		Weapon	club = Weapon("crude spiked club");
		HumanA	bob("Bob", club);

		bob.attack();
		club.setType("some other type of club");
		bob.attack();
	}
	{
		Weapon	club = Weapon("crude spiked club");
		HumanB	jim("Jim");

		jim.attack();
		jim.setWeapon(club);
		jim.attack();
		club.setType("some other type of club");
		jim.attack();
	}
	return (0);
}
