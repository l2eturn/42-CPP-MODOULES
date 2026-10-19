#include "Dog.hpp"
#include "Cat.hpp"

int	main(void)
{
	std::cout << "--- subject test ---" << std::endl;
	const Animal	*j = new Dog();
	const Animal	*i = new Cat();

	delete j;
	delete i;

	std::cout << std::endl << "--- array of animals (half dogs, half cats) ---" << std::endl;
	const int	size = 4;
	Animal		*animals[size];

	for (int k = 0; k < size; k ++)
	{
		if (k < size / 2)
			animals[k] = new Dog();
		else
			animals[k] = new Cat();
	}
	for (int k = 0; k < size; k ++)
		animals[k]->makeSound();
	for (int k = 0; k < size; k ++)
		delete animals[k];

	std::cout << std::endl << "--- deep copy (copy constructor) ---" << std::endl;
	Dog	dog;
	dog.getBrain()->setIdea(0, "chase the cat");
	Dog	copy(dog);
	copy.getBrain()->setIdea(0, "sleep");
	std::cout << "dog  idea[0]: " << dog.getBrain()->getIdea(0) << std::endl;
	std::cout << "copy idea[0]: " << copy.getBrain()->getIdea(0) << std::endl;
	std::cout << "same brain address? "
			  << (dog.getBrain() == copy.getBrain() ? "yes (shallow!)" : "no (deep)") << std::endl;

	std::cout << std::endl << "--- deep copy (assignment) ---" << std::endl;
	Cat	cat;
	Cat	other;
	cat.getBrain()->setIdea(1, "eat fish");
	other = cat;
	cat.getBrain()->setIdea(1, "knock things off the table");
	std::cout << "cat   idea[1]: " << cat.getBrain()->getIdea(1) << std::endl;
	std::cout << "other idea[1]: " << other.getBrain()->getIdea(1) << std::endl;

	std::cout << std::endl << "--- end of main ---" << std::endl;
	return (0);
}
