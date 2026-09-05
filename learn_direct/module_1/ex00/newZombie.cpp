#include "Zombie.hpp"

/*
** ต้องใช้ HEAP (new) เพราะเราอยากให้ zombie "รอดออกไปจาก scope ของฟังก์ชัน"
**
** ถ้าเขียน  Zombie z(name); return (&z);  -> จะได้ pointer ชี้ไปที่ stack frame
** ที่ถูกทำลายไปแล้วตอน return = dangling pointer = undefined behavior
**
** ราคาที่จ่าย: คนที่รับ pointer ไปต้อง delete เอง ไม่งั้น leak
*/
Zombie	*newZombie(std::string name)
{
	return (new Zombie(name));
}
