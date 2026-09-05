#include <iostream>
#include "AAnimal.hpp"
#include "Brain.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int	main(void)
{
	/*
	** ลองเอา comment ออกดู -> compiler จะฟ้องทันที:
	**   "variable type 'AAnimal' is an abstract class"
	**   "allocating an object of abstract class type 'AAnimal'"
	** นี่คือทั้งหมดที่ ex02 ต้องการพิสูจน์
	*/
	// AAnimal	nope;
	// AAnimal	*nope2 = new AAnimal();

	std::cout << "=== ใช้เป็น AAnimal* ได้ปกติ (แต่สร้าง AAnimal ตรงๆ ไม่ได้) ==="
			  << std::endl;
	{
		const AAnimal	*animals[4];

		animals[0] = new Dog();
		animals[1] = new Dog();
		animals[2] = new Cat();
		animals[3] = new Cat();

		std::cout << std::endl;
		for (int i = 0; i < 4; ++i)
		{
			std::cout << animals[i]->getType() << " says: ";
			animals[i]->makeSound();
		}

		std::cout << std::endl << "--- delete ทั้งหมด ---" << std::endl;
		for (int i = 0; i < 4; ++i)
			delete animals[i];
	}

	std::cout << std::endl << "=== deep copy ยังทำงานเหมือน ex01 ==="
			  << std::endl;
	{
		Dog	a;
		a.getBrain()->setIdea(0, "dig a hole");

		Dog	b(a);
		std::cout << "brain a: " << a.getBrain()
				  << " / brain b: " << b.getBrain() << std::endl;
		std::cout << "b idea: \"" << b.getBrain()->getIdea(0) << "\""
				  << std::endl;
	}
	return (0);
}
