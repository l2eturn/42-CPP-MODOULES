#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongCat.hpp"

int	main(void)
{
	std::cout << "--- subject test ---" << std::endl;
	const Animal	*meta = new Animal();
	const Animal	*j = new Dog();
	const Animal	*i = new Cat();

	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	i->makeSound();
	j->makeSound();
	meta->makeSound();
	delete meta;
	delete j;
	delete i;

	std::cout << std::endl << "--- wrong animal (no virtual) ---" << std::endl;
	const WrongAnimal	*wrongMeta = new WrongAnimal();
	const WrongAnimal	*wrongCat = new WrongCat();

	std::cout << wrongCat->getType() << " " << std::endl;
	wrongCat->makeSound();
	wrongMeta->makeSound();
	delete wrongMeta;
	delete wrongCat;

	std::cout << std::endl << "--- WrongCat called directly ---" << std::endl;
	WrongCat	direct;
	direct.makeSound();

	std::cout << std::endl << "--- copy ---" << std::endl;
	Dog	dog;
	Dog	dogCopy(dog);
	std::cout << dogCopy.getType() << ": ";
	dogCopy.makeSound();

	std::cout << std::endl << "--- end of main ---" << std::endl;
	return (0);
}
