#include <iomanip>
#include <iostream>
#include <sstream>
#include "PhoneBook.hpp"

/*
** initialization list ( : _count(0), _next(0) )
** ดีกว่าไป assign ใน body เพราะ member ถูก "สร้างพร้อมค่า" ในครั้งเดียว
** ไม่ใช่สร้างเปล่าๆ แล้วค่อยเขียนทับ -- และเป็นทางเดียวที่ init const/reference member ได้
*/
PhoneBook::PhoneBook(void) : _count(0), _next(0)
{
}

PhoneBook::~PhoneBook(void)
{
}

/*
** อ่าน 1 field จนกว่าจะไม่ว่าง
** return false = เจอ EOF (ผู้ใช้กด Ctrl-D) -> ผู้เรียกต้องเลิกทำงาน
** ใช้ std::getline ไม่ใช่ std::cin >> เพราะชื่อคนมีเว้นวรรคได้
*/
bool	PhoneBook::_promptField(const std::string &label, std::string &out)
{
	while (true)
	{
		std::cout << label << ": ";
		if (!std::getline(std::cin, out))
			return (false);
		if (!out.empty())
			return (true);
		std::cout << "This field cannot be empty." << std::endl;
	}
}

void	PhoneBook::add(void)
{
	Contact	contact;
	std::string	value;

	if (!_promptField("First name", value))
		return ;
	contact.setFirstName(value);
	if (!_promptField("Last name", value))
		return ;
	contact.setLastName(value);
	if (!_promptField("Nickname", value))
		return ;
	contact.setNickname(value);
	if (!_promptField("Phone number", value))
		return ;
	contact.setPhoneNumber(value);
	if (!_promptField("Darkest secret", value))
		return ;
	contact.setDarkestSecret(value);

	_contacts[_next] = contact;
	_next = (_next + 1) % _capacity;
	if (_count < _capacity)
		++_count;
	std::cout << "Contact saved." << std::endl;
}

/*
** ตัดข้อความให้พอดีคอลัมน์: ถ้ายาวเกิน width ให้เอา width-1 ตัวแรก + '.'
** เช่น width 10, "Bartholomew" (11 ตัว) -> "Bartholom."
*/
std::string	PhoneBook::_truncate(const std::string &value, int width)
{
	if (static_cast<int>(value.length()) <= width)
		return (value);
	return (value.substr(0, width - 1) + ".");
}

/*
** std::setw(10) = ความกว้างช่องถัดไป 10 ตัว, default คือชิดขวา (right-aligned)
** setw ใช้ได้ครั้งเดียวต่อ 1 การ insert -> ต้องเรียกซ้ำทุกคอลัมน์
*/
void	PhoneBook::_displayTable(void) const
{
	std::cout << std::setw(10) << "Index" << "|"
			  << std::setw(10) << "First Name" << "|"
			  << std::setw(10) << "Last Name" << "|"
			  << std::setw(10) << "Nickname" << std::endl;
	for (int i = 0; i < _count; ++i)
	{
		std::cout << std::setw(10) << i << "|"
				  << std::setw(10) << _truncate(_contacts[i].getFirstName(), 10) << "|"
				  << std::setw(10) << _truncate(_contacts[i].getLastName(), 10) << "|"
				  << std::setw(10) << _truncate(_contacts[i].getNickname(), 10)
				  << std::endl;
	}
}

void	PhoneBook::_displayContact(int index) const
{
	const Contact	&c = _contacts[index];

	std::cout << "First name     : " << c.getFirstName() << std::endl;
	std::cout << "Last name      : " << c.getLastName() << std::endl;
	std::cout << "Nickname       : " << c.getNickname() << std::endl;
	std::cout << "Phone number   : " << c.getPhoneNumber() << std::endl;
	std::cout << "Darkest secret : " << c.getDarkestSecret() << std::endl;
}

/*
** อ่าน index เป็น string ก่อน แล้วแปลงด้วย std::istringstream
** ทำไมไม่ใช้ std::cin >> index ตรงๆ?
**   ถ้าผู้ใช้พิมพ์ "abc" -> cin เข้า fail state ค้าง ต้อง clear()+ignore()
**   อ่านเป็น string แล้วแปลงเอง จัดการง่ายกว่าและไม่ทำให้ stream พัง
** ตรวจ (ss >> index) และ ss.eof() = แปลงได้ครบทุกตัวอักษร ไม่มีขยะต่อท้าย
*/
void	PhoneBook::search(void) const
{
	std::string	line;
	int			index;

	if (_count == 0)
	{
		std::cout << "The phonebook is empty." << std::endl;
		return ;
	}
	_displayTable();
	std::cout << "Index: ";
	if (!std::getline(std::cin, line))
		return ;

	std::istringstream	ss(line);
	if (!(ss >> index) || !ss.eof() || index < 0 || index >= _count)
	{
		std::cout << "Invalid index." << std::endl;
		return ;
	}
	_displayContact(index);
}
