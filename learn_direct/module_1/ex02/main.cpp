#include <iostream>
#include <string>

/*
** ex02 - HI THIS IS BRAIN
** เป้าหมาย: ให้เห็นด้วยตาว่า reference คือ "ชื่อเรียกอีกชื่อ" ของตัวแปรเดิม
**
** ===== pointer vs reference =====
**              pointer                  reference
** ประกาศ      std::string *p = &s;      std::string &r = s;
** อ่านค่า      *p                       r        (ไม่มี * ไม่มี &)
** เอา address  p                        &r       (ได้ address เดียวกับ &s)
** เป็น NULL    ได้                      ไม่ได้ (ต้องผูกกับของจริงตอนประกาศ)
** ชี้ที่อื่น     ได้ (p = &other)         ไม่ได้ (r = other คือ "copy ค่า" ทับ s!)
**
** ผลลัพธ์: 3 address ที่พิมพ์ออกมา "เหมือนกันหมด" และ 3 ค่าก็เหมือนกันหมด
** เพราะทั้งสามอย่างพูดถึงหน่วยความจำก้อนเดียวกัน
*/
int	main(void)
{
	std::string	brain = "HI THIS IS BRAIN";
	std::string	*stringPTR = &brain;
	std::string	&stringREF = brain;

	std::cout << "address of brain      : " << &brain << std::endl;
	std::cout << "address held by PTR   : " << stringPTR << std::endl;
	std::cout << "address held by REF   : " << &stringREF << std::endl;
	std::cout << std::endl;
	std::cout << "value of brain        : " << brain << std::endl;
	std::cout << "value pointed by PTR  : " << *stringPTR << std::endl;
	std::cout << "value pointed by REF  : " << stringREF << std::endl;
	return (0);
}
