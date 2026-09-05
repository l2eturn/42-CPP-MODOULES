#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

# include <string>

/*
** WrongAnimal = "ตัวควบคุมการทดลอง" ของ exercise นี้
** เหมือน Animal ทุกอย่าง ยกเว้น makeSound() *ไม่ใช่ virtual*
**
** ผลลัพธ์:
**   const WrongAnimal *w = new WrongCat();
**   w->makeSound();   ->  เสียงของ WrongAnimal  (ผิดจากที่ควรเป็น!)
**
** เพราะ compiler ตัดสินใจตอน compile จาก type ของ pointer (WrongAnimal*)
** ไม่สนว่าจริงๆ ข้างในเป็น WrongCat = static binding
**
** เอาไว้เทียบกับ Animal/Cat ที่ virtual แล้วให้ผลถูกต้อง
** -> นี่คือทั้งบทเรียนของ ex00 ในโค้ด 2 คลาส
*/
class WrongAnimal
{
	public:
		WrongAnimal(void);
		WrongAnimal(const WrongAnimal &other);
		WrongAnimal	&operator=(const WrongAnimal &other);
		~WrongAnimal(void);

		void				makeSound(void) const;
		const std::string	&getType(void) const;

	protected:
		std::string	_type;
};

#endif
