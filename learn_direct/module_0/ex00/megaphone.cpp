#include <cctype>
#include <iostream>

/*
** ex00 - Megaphone
** โจทย์: รับ argv มาแปลงเป็นตัวพิมพ์ใหญ่ทั้งหมด, ถ้าไม่มี argv เลย -> ข้อความ default
**
** จุดที่ต้องเข้าใจ:
**  1) argc == 1 หมายถึง "มีแค่ชื่อโปรแกรม" = ไม่มี argument
**  2) std::toupper รับ int ที่ต้องอยู่ใน range ของ unsigned char (หรือ EOF)
**     ถ้าส่ง char ที่ติดลบ (เช่นตัวอักษร UTF-8) เข้าไปตรงๆ = undefined behavior
**     -> ต้อง cast เป็น unsigned char ก่อน แล้วค่อย cast ผลลัพธ์กลับเป็น char
**  3) ใช้ static_cast แทน (char) แบบ C -- นี่คือ "C++ manner" ที่โจทย์ขอ
*/

int	main(int argc, char **argv)
{
	if (argc == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return (0);
	}
	for (int i = 1; i < argc; ++i)
	{
		for (int j = 0; argv[i][j]; ++j)
		{
			unsigned char	c = static_cast<unsigned char>(argv[i][j]);

			std::cout << static_cast<char>(std::toupper(c));
		}
	}
	std::cout << std::endl;
	return (0);
}
