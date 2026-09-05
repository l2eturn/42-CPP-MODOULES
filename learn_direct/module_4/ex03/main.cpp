#include <iostream>
#include "Character.hpp"
#include "Cure.hpp"
#include "Ice.hpp"
#include "MateriaSource.hpp"

int	main(void)
{
	std::cout << "=== main ตามโจทย์ ===" << std::endl;
	{
		IMateriaSource	*src = new MateriaSource();

		src->learnMateria(new Ice());
		src->learnMateria(new Cure());

		ICharacter	*me = new Character("me");
		AMateria	*tmp;

		tmp = src->createMateria("ice");
		me->equip(tmp);
		tmp = src->createMateria("cure");
		me->equip(tmp);

		ICharacter	*bob = new Character("bob");

		me->use(0, *bob);
		me->use(1, *bob);

		delete bob;
		delete me;
		delete src;
	}

	std::cout << std::endl << "=== edge cases ===" << std::endl;
	{
		MateriaSource	src;

		src.learnMateria(new Ice());
		src.learnMateria(new Cure());

		std::cout << "createMateria(\"fire\") -> "
				  << (src.createMateria("fire") ? "pointer" : "0 (ถูกต้อง)")
				  << std::endl;

		Character	hero("hero");
		Character	dummy("dummy");

		std::cout << "-- use ช่องว่าง / index ผิด: ต้องไม่มีอะไรเกิดขึ้น --"
				  << std::endl;
		hero.use(0, dummy);
		hero.use(-1, dummy);
		hero.use(99, dummy);
		hero.unequip(2);
		std::cout << "(ไม่มี output = ถูกต้อง)" << std::endl;

		std::cout << "-- inventory เต็ม 4 แล้ว equip ตัวที่ 5 --" << std::endl;
		for (int i = 0; i < 5; ++i)
			hero.equip(src.createMateria("ice"));
		for (int i = 0; i < 4; ++i)
			hero.use(i, dummy);
		std::cout << "(ยิง 4 ครั้ง ตัวที่ 5 ถูกทิ้ง ไม่ leak)" << std::endl;

		std::cout << "-- unequip แล้วช่องนั้นใช้ไม่ได้ --" << std::endl;
		hero.unequip(0);
		hero.use(0, dummy);
		std::cout << "(ไม่มี output = ถูกต้อง)" << std::endl;
	}

	std::cout << std::endl << "=== deep copy ของ Character ===" << std::endl;
	{
		MateriaSource	src;
		src.learnMateria(new Ice());
		src.learnMateria(new Cure());

		Character	original("original");
		original.equip(src.createMateria("ice"));
		original.equip(src.createMateria("cure"));

		Character	target("target");

		std::cout << "-- copy constructor: clone ใช้ได้เหมือนต้นฉบับ --"
				  << std::endl;
		Character	copy(original);
		copy.use(0, target);
		copy.use(1, target);

		std::cout << "-- copy assignment --" << std::endl;
		Character	assigned("assigned");
		assigned.equip(src.createMateria("ice"));
		assigned = original;
		assigned.use(0, target);
		std::cout << "assigned ชื่อใหม่คือ: " << assigned.getName() << std::endl;
		std::cout << "(ของเก่าถูก delete ก่อน copy -> ไม่ leak, ไม่ double free)"
				  << std::endl;
	}

	std::cout << std::endl << "=== deep copy ของ MateriaSource ===" << std::endl;
	{
		MateriaSource	a;
		a.learnMateria(new Ice());

		MateriaSource	b(a);
		Character		dummy("dummy");
		AMateria		*m = b.createMateria("ice");

		std::cout << "b ที่ copy มา สร้าง ice ได้: " << (m ? "ใช่" : "ไม่")
				  << std::endl;
		if (m)
		{
			m->use(dummy);
			delete m;
		}
	}
	return (0);
}
