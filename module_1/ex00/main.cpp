#include <iostream>
#include "Zombie.hpp"

int	main(void)
{
	std::cout << "--- heap: newZombie() ---" << std::endl;
	Zombie	*heapZombie = newZombie("HeapFoo");
	heapZombie->announce();
	delete heapZombie;

	std::cout << std::endl << "--- stack: randomChump() ---" << std::endl;
	randomChump("StackBar");

	std::cout << std::endl << "--- stack ใน scope ย่อย ---" << std::endl;
	{
		Zombie	scoped("Scoped");
		scoped.announce();
	}
	std::cout << "ออกจาก scope แล้ว -- destructor ถูกเรียกไปก่อนบรรทัดนี้"
			  << std::endl;
	return (0);
}
