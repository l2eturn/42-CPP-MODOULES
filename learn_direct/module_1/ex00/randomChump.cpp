#include "Zombie.hpp"

/*
** ต้องใช้ STACK เพราะ zombie ตัวนี้ใช้แค่ในฟังก์ชันนี้ แล้วก็ทิ้ง
**
** ข้อดี: destructor ถูกเรียกอัตโนมัติตอนจบ scope -> ลืม delete ไม่ได้ = leak ไม่ได้
** เร็วกว่า new ด้วย (แค่เลื่อน stack pointer ไม่ต้องขอ memory จาก OS)
**
** กฎง่ายๆ ของโมดูลนี้: ใช้ stack เป็นค่าเริ่มต้น
** ใช้ heap เมื่อ (1) ต้องมีชีวิตข้าม scope หรือ (2) ไม่รู้จำนวน/ขนาดตอน compile
*/
void	randomChump(std::string name)
{
	Zombie	chump(name);

	chump.announce();
}
