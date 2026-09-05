#include <iostream>
#include "Cat.hpp"

Cat::Cat(void) : AAnimal(), _brain(new Brain())
{
	_type = "Cat";
	std::cout << "Cat constructor" << std::endl;
}

/*
** DEEP COPY: new Brain(...) = จองก้อนใหม่ แล้วเรียก Brain copy constructor
** ถ้าเขียน _brain(other._brain) แบบนี้คือ shallow = ระเบิดตอน destructor
*/
Cat::Cat(const Cat &other) : AAnimal(other), _brain(new Brain(*other._brain))
{
	std::cout << "Cat copy constructor (deep)" << std::endl;
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
Cat	&Cat::operator=(const Cat &other)
{
	std::cout << "Cat copy assignment operator (deep)" << std::endl;
	if (this != &other)
	{
		AAnimal::operator=(other);
		*_brain = *other._brain;
	}
	return (*this);
}

Cat::~Cat(void)
{
	delete _brain;
	std::cout << "Cat destructor" << std::endl;
}

void	Cat::makeSound(void) const
{
	std::cout << "Meow! Meow!" << std::endl;
}

Brain	*Cat::getBrain(void) const
{
	return (_brain);
}
