#include <iostream>
#include "PhoneBook.hpp"

/*
** loop หลัก: ADD / SEARCH / EXIT, อย่างอื่น ignore
**
** ใช้ std::getline แล้วเทียบด้วย == (std::string มี operator== ให้แล้ว)
** ไม่ต้องใช้ .compare() -- อ่านง่ายกว่าเยอะ
**
** เช็ค !std::getline(...) ด้วย เพื่อออกตอนเจอ EOF (Ctrl-D)
** ถ้าไม่เช็ค โปรแกรมจะ loop ไม่หยุดตอน stdin ปิด
*/
int	main(void)
{
	PhoneBook	phonebook;
	std::string	command;

	while (true)
	{
		std::cout << "Enter a command (ADD / SEARCH / EXIT): ";
		if (!std::getline(std::cin, command))
			break ;
		if (command == "ADD")
			phonebook.add();
		else if (command == "SEARCH")
			phonebook.search();
		else if (command == "EXIT")
			break ;
		else if (!command.empty())
			std::cout << "Unknown command: " << command << std::endl;
	}
	return (0);
}
