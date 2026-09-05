#include <iostream>
#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int	main(void)
{
	std::cout << "=== ถูกต้อง: makeSound เป็น virtual ===" << std::endl;
	{
		const Animal	*meta = new Animal();
		const Animal	*j = new Dog();
		const Animal	*i = new Cat();

		std::cout << std::endl;
		std::cout << "type ของ j: " << j->getType() << std::endl;
		std::cout << "type ของ i: " << i->getType() << std::endl;
		i->makeSound();		// เสียงแมว
		j->makeSound();		// เสียงหมา
		meta->makeSound();	// เสียง Animal

		std::cout << std::endl << "--- delete ผ่าน Animal* ---" << std::endl;
		delete meta;
		delete j;			// เรียก ~Dog แล้วค่อย ~Animal (เพราะ dtor virtual)
		delete i;
	}

	std::cout << std::endl << "=== ผิด: makeSound ไม่ virtual ===" << std::endl;
	{
		const WrongAnimal	*w = new WrongCat();

		std::cout << std::endl;
		std::cout << "type ของ w: " << w->getType()
				  << "  <-- ตัวแปร _type ถูกตั้งเป็น WrongCat ถูกต้อง"
				  << std::endl;
		w->makeSound();
		std::cout << "^ ได้เสียง WrongAnimal! เพราะไม่ virtual = static binding"
				  << std::endl;

		std::cout << std::endl << "--- delete ผ่าน WrongAnimal* ---"
				  << std::endl;
		delete w;
		std::cout << "^ ไม่มี ~WrongCat ถูกเรียก = ถ้า WrongCat จองหน่วยความจำไว้ จะ leak"
				  << std::endl;
	}

	std::cout << std::endl << "=== object บน stack เรียกตรงๆ (ถูกทั้งคู่) ==="
			  << std::endl;
	{
		WrongCat	direct;

		direct.makeSound();
	}
	return (0);
}
