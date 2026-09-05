#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# include <string>

/*
** =============== หัวใจของ module 04: VIRTUAL ===============
**
** virtual ทำให้ C++ เลือกฟังก์ชันตาม "ชนิดจริงของ object ตอน runtime"
** ไม่ใช่ตาม "ชนิดของ pointer/reference ตอน compile"
** เรียกว่า dynamic dispatch (ทำงานผ่านตาราง vtable ที่ compiler สร้างให้)
**
**   Animal *a = new Dog();
**   a->makeSound();   // virtual     -> "Woof!"   (ของ Dog)
**                     // ไม่ virtual -> ของ Animal
**
** ===== virtual destructor: สำคัญที่สุด =====
**   Animal *a = new Dog();
**   delete a;
** ถ้า ~Animal ไม่เป็น virtual -> เรียกแค่ ~Animal ไม่เรียก ~Dog
** -> ของที่ Dog จองไว้ (Brain* ใน ex01) leak ทันที
**
** กฎ: ถ้า class มี virtual function ตัวใดตัวหนึ่ง -> destructor ต้อง virtual
*/
class Animal
{
	public:
		Animal(void);
		Animal(const Animal &other);
		Animal	&operator=(const Animal &other);
		virtual ~Animal(void);

		virtual void		makeSound(void) const;
		const std::string	&getType(void) const;

	protected:
		std::string	_type;
};

#endif
