#include <iostream>
#include "Animal.hpp"
#include "Brain.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int	main(void)
{
	std::cout << "=== array ของ Animal* ครึ่งหมาครึ่งแมว ===" << std::endl;
	{
		const int	count = 4;
		Animal		*animals[count];

		for (int i = 0; i < count; ++i)
		{
			if (i < count / 2)
				animals[i] = new Dog();
			else
				animals[i] = new Cat();
		}

		std::cout << std::endl << "--- makeSound ผ่าน Animal* ---" << std::endl;
		for (int i = 0; i < count; ++i)
			animals[i]->makeSound();

		std::cout << std::endl
				  << "--- delete ทุกตัว *ในฐานะ Animal* (dtor virtual ทำงาน) ---"
				  << std::endl;
		for (int i = 0; i < count; ++i)
			delete animals[i];
	}

	std::cout << std::endl << "=== พิสูจน์ว่าเป็น DEEP copy ===" << std::endl;
	{
		Dog	original;

		original.getBrain()->setIdea(0, "chase the ball");

		std::cout << std::endl << "-- copy constructor --" << std::endl;
		Dog	clone(original);

		std::cout << std::endl;
		std::cout << "brain address original : " << original.getBrain()
				  << std::endl;
		std::cout << "brain address clone    : " << clone.getBrain()
				  << std::endl;
		std::cout << "address ต่างกัน? "
				  << (original.getBrain() != clone.getBrain()
						? "ใช่ -> DEEP copy ถูกต้อง"
						: "ไม่ -> SHALLOW copy ผิด!")
				  << std::endl;
		std::cout << "idea ที่ clone ได้มา: \""
				  << clone.getBrain()->getIdea(0) << "\"" << std::endl;

		std::cout << std::endl << "-- แก้ของ clone แล้วดูว่า original เปลี่ยนไหม --"
				  << std::endl;
		clone.getBrain()->setIdea(0, "sleep all day");
		std::cout << "original idea : \"" << original.getBrain()->getIdea(0)
				  << "\"" << std::endl;
		std::cout << "clone idea    : \"" << clone.getBrain()->getIdea(0)
				  << "\"" << std::endl;
		std::cout << "แยกกันจริง? "
				  << (original.getBrain()->getIdea(0) != clone.getBrain()->getIdea(0)
						? "ใช่" : "ไม่")
				  << std::endl;

		std::cout << std::endl << "-- copy assignment operator --" << std::endl;
		Dog	assigned;
		assigned = original;
		std::cout << "assigned idea : \"" << assigned.getBrain()->getIdea(0)
				  << "\"" << std::endl;
		std::cout << "brain address assigned : " << assigned.getBrain()
				  << " (ต่างจาก original)" << std::endl;

		std::cout << std::endl << "-- self-assignment (ต้องไม่ crash) --"
				  << std::endl;
		/*
		** ผ่าน reference เพื่อเลี่ยง warning -Wself-assign-overloaded
		** (เขียน assigned = assigned; ตรงๆ compiler จะฟ้องว่าไร้ประโยชน์)
		** จุดที่ทดสอบคือ if (this != &other) ใน operator= ทำงานจริง
		*/
		Dog	&selfRef = assigned;
		assigned = selfRef;
		std::cout << "ยังอยู่ดี idea = \"" << assigned.getBrain()->getIdea(0)
				  << "\"" << std::endl;

		std::cout << std::endl << "--- ออก scope ---" << std::endl;
	}

	std::cout << std::endl << "=== delete Dog/Cat ผ่าน Animal* ไม่ leak ==="
			  << std::endl;
	{
		const Animal	*j = new Dog();
		const Animal	*i = new Cat();

		delete j;
		delete i;
	}
	return (0);
}
