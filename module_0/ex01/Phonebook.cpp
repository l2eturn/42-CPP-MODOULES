#include <iomanip>
#include <iostream>
#include <sstream>
#include "Phonebook.hpp"

PhoneBook::PhoneBook(void) : _count(0), _next(0)
{
}

PhoneBook::~PhoneBook(void)
{
}

void	PhoneBook::addContact(const Contact &contact)
{
	_contacts[_next] = contact;
	_next = (_next + 1) % _capacity;
	if (_count < _capacity)
		++_count;
}

std::string	PhoneBook::_truncate(const std::string &value, int width)
{
	if (static_cast<int>(value.length()) <= width)
		return (value);
	return (value.substr(0, width - 1) + ".");
}

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
	const Contact &contact = _contacts[index];

	std::cout << "First name     : " << contact.getFirstName() << std::endl;
	std::cout << "Last name      : " << contact.getLastName() << std::endl;
	std::cout << "Nickname       : " << contact.getNickname() << std::endl;
	std::cout << "Phone number   : " << contact.getPhoneNumber() << std::endl;
	std::cout << "Darkest secret : " << contact.getDarkestSecret() << std::endl;
}

void	PhoneBook::searchContact(void) const
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
	std::istringstream stream(line);
	std::string extra;
	if (!(stream >> index) || (stream >> extra)
		|| index < 0 || index >= _count)
	{
		std::cout << "Invalid index." << std::endl;
		return ;
	}
	_displayContact(index);
}
