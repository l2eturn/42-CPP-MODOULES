#include "MateriaSource.hpp"
#include "Character.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

int	main(void)
{
	std::cout << "--- subject test ---" << std::endl;
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

	std::cout << std::endl << "--- unknown type returns 0 ---" << std::endl;
	{
		MateriaSource	src;
		src.learnMateria(new Ice());
		AMateria	*fire = src.createMateria("fire");
		std::cout << "createMateria(\"fire\") = " << (fire == 0 ? "0" : "not 0") << std::endl;
	}

	std::cout << std::endl << "--- full inventory, bad index, unequip ---" << std::endl;
	{
		MateriaSource	src;
		src.learnMateria(new Ice());
		src.learnMateria(new Cure());

		Character	alice("alice");
		Character	target("target");
		for (int i = 0; i < 4; i ++)
			alice.equip(src.createMateria(i % 2 == 0 ? "ice" : "cure"));

		AMateria	*extra = src.createMateria("ice");
		alice.equip(extra);		// inventory full: nothing happens
		delete extra;

		alice.use(-1, target);	// nothing
		alice.use(4, target);	// nothing

		std::cout << "slot 0 before unequip: ";
		alice.use(0, target);
		AMateria	*dropped = alice.getMateria(0);	// save the address first
		alice.unequip(0);
		alice.use(0, target);	// nothing: slot 0 is empty now
		std::cout << "dropped materia type: " << dropped->getType() << std::endl;
		delete dropped;

		std::cout << "equip again into first empty slot (0):" << std::endl;
		alice.equip(src.createMateria("cure"));
		for (int i = 0; i < 4; i ++)
			alice.use(i, target);
	}

	std::cout << std::endl << "--- deep copy of Character ---" << std::endl;
	{
		MateriaSource	src;
		src.learnMateria(new Ice());

		Character	original("original");
		original.equip(src.createMateria("ice"));

		Character	copy(original);
		Character	assigned("assigned");
		assigned = original;

		std::cout << "same materia address? "
				  << (original.getMateria(0) == copy.getMateria(0) ? "yes (shallow!)" : "no (deep)") << std::endl;
		copy.use(0, original);
		assigned.use(0, original);
	}
	return (0);
}
