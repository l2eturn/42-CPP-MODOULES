#ifndef AANIMAL_HPP
# define AANIMAL_HPP

# include <string>

/*
** ============ ex02: ABSTRACT CLASS ============
**
** "Creating Animal objects doesn't make sense" -> ต้องห้ามสร้าง Animal เปล่าๆ
**
** วิธี: ทำให้มี PURE VIRTUAL FUNCTION อย่างน้อย 1 ตัว
**     virtual void makeSound(void) const = 0;
**                                        ^^^ = 0 คือ pure specifier
**
** ผลลัพธ์: class กลายเป็น abstract -> instantiate ไม่ได้เลย
**     AAnimal a;              // compile error
**     new AAnimal();          // compile error
**     AAnimal *p = new Dog(); // OK! ใช้เป็น pointer/reference ได้ตามปกติ
**
** compiler บังคับให้เราถูกต้องตั้งแต่ compile time -- ดีกว่ามาพังตอน runtime
**
** ===== ทำไม pure virtual ยังมี body ได้ (และเราให้มันมี) =====
** ที่นี่ makeSound เป็น pure จริงๆ ไม่มี body -> คลาสลูกทุกตัว *ต้อง* เขียนเอง
** ถ้าลูกตัวไหนไม่เขียน ลูกตัวนั้นก็ยัง abstract อยู่ สร้างไม่ได้เหมือนกัน
**
** destructor ยังต้อง virtual และยังต้องมี body! (dtor ของแม่ถูกเรียกเสมอ)
**
** ===== abstract class vs interface =====
** abstract class = มี pure virtual >= 1 ตัว (อาจมี data member / โค้ดจริงด้วย)
** interface      = pure virtual ทั้งหมด ไม่มี data member (ex03 จะได้เห็น)
** C++98 ไม่มี keyword interface -- ใช้ pure abstract class แทน
*/
class AAnimal
{
	public:
		AAnimal(void);
		AAnimal(const AAnimal &other);
		AAnimal	&operator=(const AAnimal &other);
		virtual ~AAnimal(void);

		virtual void		makeSound(void) const = 0;
		const std::string	&getType(void) const;

	protected:
		std::string	_type;
};

#endif
