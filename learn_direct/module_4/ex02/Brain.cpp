#include <iostream>
#include "Brain.hpp"

const int	Brain::_size;

Brain::Brain(void)
{
	std::cout << "Brain constructor" << std::endl;
}

Brain::Brain(const Brain &other)
{
	std::cout << "Brain copy constructor" << std::endl;
	for (int i = 0; i < _size; ++i)
		_ideas[i] = other._ideas[i];
}

Brain	&Brain::operator=(const Brain &other)
{
	std::cout << "Brain copy assignment operator" << std::endl;
	if (this != &other)
	{
		for (int i = 0; i < _size; ++i)
			_ideas[i] = other._ideas[i];
	}
	return (*this);
}

Brain::~Brain(void)
{
	std::cout << "Brain destructor" << std::endl;
}

void	Brain::setIdea(int index, const std::string &idea)
{
	if (index < 0 || index >= _size)
		return ;
	_ideas[index] = idea;
}

const std::string	&Brain::getIdea(int index) const
{
	static const std::string	empty = "";

	if (index < 0 || index >= _size)
		return (empty);
	return (_ideas[index]);
}
