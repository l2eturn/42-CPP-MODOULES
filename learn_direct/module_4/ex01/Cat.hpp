#ifndef CAT_HPP
# define CAT_HPP

# include "Animal.hpp"
# include "Brain.hpp"

/*
** ============ SHALLOW COPY vs DEEP COPY ============
**
** Cat มี Brain* -> ถ้าปล่อยให้ compiler สร้าง copy constructor เอง
** มันจะ copy "ค่าของ pointer" = สองตัวชี้ Brain ก้อนเดียวกัน (SHALLOW)
** ผลลัพธ์ 2 อย่าง ที่พังหนักทั้งคู่:
**   1) แก้ idea ของ dog1 -> dog2 เปลี่ยนตามด้วย (ไม่ควรเป็นแบบนั้น)
**   2) dog1 ตาย delete brain, dog2 ตาย delete brain ก้อนเดิมอีกรอบ
**      = DOUBLE FREE -> โปรแกรม crash
**
** DEEP COPY = new Brain(*other._brain) -> จอง Brain ก้อนใหม่ แล้ว copy เนื้อหา
** -> address ต่างกัน แก้แยกกันได้ ทำลายแยกกันได้
**
** วิธีทดสอบว่า deep จริง: พิมพ์ address ของ brain ทั้งสองตัวมาเทียบ (ดู main.cpp)
**
** นี่คือเหตุผลที่ Rule of Three มีอยู่: มี dtor ที่ delete -> ต้องเขียน
** copy constructor และ operator= เองเสมอ
*/
class Cat : public Animal
{
	public:
		Cat(void);
		Cat(const Cat &other);
		Cat	&operator=(const Cat &other);
		virtual ~Cat(void);

		virtual void	makeSound(void) const;

		Brain			*getBrain(void) const;

	private:
		Brain	*_brain;
};

#endif
