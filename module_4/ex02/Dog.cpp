#include "Dog.hpp"

Dog::Dog(void) : AAnimal(), _brain(new Brain())
{
	this->type = "Dog";
	std::cout << "Dog default constructor called" << std::endl;
}

// deep copy: make a new Brain instead of sharing the pointer
Dog::Dog(const Dog &other) : AAnimal(other), _brain(new Brain(*other._brain))
{
	std::cout << "Dog copy constructor called" << std::endl;
}

Dog	&Dog::operator=(const Dog &other)
{
	std::cout << "Dog copy assignment operator called" << std::endl;
	if (this != &other)
	{
		AAnimal::operator=(other);
		*this->_brain = *other._brain;
	}
	return (*this);
}

Dog::~Dog(void)
{
	delete _brain;
	std::cout << "Dog destructor called" << std::endl;
}

void	Dog::makeSound() const
{
	std::cout << "Woof! Woof!" << std::endl;
}

Brain	*Dog::getBrain() const
{
	return (_brain);
}
