#include <iostream>
#include "Phonebook.hpp"
#include "Contact.hpp"

void	Phonebook::initialize()
{
	_size = 0;
	_oldest = 0;
	_index = 0;
}
void	Phonebook::addContact(Contact &a_contact)
{
	if (_size == 8)
	{
		// del oldest;
		// addContact 2 Oldest
		_contact[_oldest] = a_contact;
		_oldest = (_oldest + 1) % 8;
	}
	else
	{
		_size ++;		
		_contact[_index] = a_contact;
		_index ++;
	}
}

#include <iomanip>
#include <iostream>

void Phonebook::searchContact()
{
    int index;

    // Header
    std::cout << std::setw(10) << "Index" << "|"
              << std::setw(10) << "First Name" << "|"
              << std::setw(10) << "Last Name" << "|"
              << std::setw(10) << "Nickname" << '\n';

    // Contacts
    for (int i = 0; i < _size; i++)
    {
        std::cout << std::setw(10) << i << "|"
                  << std::setw(10) << /* first name */ << "|"
                  << std::setw(10) << /* last name */ << "|"
                  << std::setw(10) << /* nickname */ << '\n';
    }

    std::cout << "Index: ";
    std::cin >> index;

    if (index < 0 || index >= _size)
    {
        std::cout << "Invalid index\n";
        return;
    }

    // แสดงรายละเอียด contact ที่เลือก
}
