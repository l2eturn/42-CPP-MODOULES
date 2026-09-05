#include <iostream>
#include <string>
#include "Phonebook.hpp"

static bool	readField(const std::string &label, std::string &value)
{
	while (true)
	{
		std::cout << label << ": ";
		if (!std::getline(std::cin, value))
			return (false);
		if (!value.empty())
			return (true);
		std::cout << "This field cannot be empty." << std::endl;
	}
}

static bool	readContact(Contact &contact)
{
	std::string value;

	if (!readField("First name", value))
		return (false);
	contact.setFirstName(value);
	if (!readField("Last name", value))
		return (false);
	contact.setLastName(value);
	if (!readField("Nickname", value))
		return (false);
	contact.setNickname(value);
	if (!readField("Phone number", value))
		return (false);
	contact.setPhoneNumber(value);
	if (!readField("Darkest secret", value))
		return (false);
	contact.setDarkestSecret(value);
	return (true);
}

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
		{
			Contact contact;
			if (readContact(contact))
				phonebook.addContact(contact);
		}
		else if (command == "SEARCH")
			phonebook.searchContact();
		else if (command == "EXIT")
			break ;
	}
	return (0);
}
