#include <iostream>
#include "Dog.hpp"

Dog::Dog(void) : Animal(), _brain(new Brain())
{
	_type = "Dog";
	std::cout << "Dog constructor" << std::endl;
}

/*
** DEEP COPY: new Brain(...) = จองก้อนใหม่ แล้วเรียก Brain copy constructor
** ถ้าเขียน _brain(other._brain) แบบนี้คือ shallow = ระเบิดตอน destructor
*/
Dog::Dog(const Dog &other) : Animal(other), _brain(new Brain(*other._brain))
{
	std::cout << "Dog copy constructor (deep)" << std::endl;
}

/*
** operator= ของ class ที่ถือ pointer ต้องทำ 3 ขั้น:
**   1) กัน self-assignment (ไม่กัน = delete ของตัวเองแล้วไป copy จากที่ลบแล้ว)
**   2) copy ส่วนของแม่
**   3) copy เนื้อหา Brain
**
** ที่นี่ใช้ *_brain = *other._brain (เรียก Brain::operator=)
** ดีกว่า delete แล้ว new ใหม่ เพราะ _brain มีอยู่แล้วแน่นอน -> ไม่ต้องจองซ้ำ
*/
Dog	&Dog::operator=(const Dog &other)
{
	std::cout << "Dog copy assignment operator (deep)" << std::endl;
	if (this != &other)
	{
		Animal::operator=(other);
		*_brain = *other._brain;
	}
	return (*this);
}

Dog::~Dog(void)
{
	delete _brain;
	std::cout << "Dog destructor" << std::endl;
}

void	Dog::makeSound(void) const
{
	std::cout << "Woof! Woof!" << std::endl;
}

Brain	*Dog::getBrain(void) const
{
	return (_brain);
}
