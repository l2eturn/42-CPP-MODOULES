#include <iostream>
#include <string>
#include "Contact.hpp"
#include "Phonebook.hpp"

void	assigned_contact(Contact *a_contact)
{
	std::string	tmp;

	std::cout << "What's your firstname\n";
	std::cin >> tmp;
	a_contact->setFirstname(tmp);

	std::cout << "What 'bout your lastname\n";
	std::cin >> tmp;
	a_contact->setLastname(tmp);

	std::cout << "What's your nickname\n";
	std::cin >> tmp;
	a_contact->setNickname(tmp);

	std::cout << "Gimme your number, Call me may be :>" << std::endl;
	std::cin >> tmp;
	a_contact->setPhonenumber(tmp);

	std::cout << "Tell me your favorite color, wanna know you\n";
	std::cin >> tmp;
	a_contact->setDarkestsecret(tmp);
}

int main(void)
{
	std::string mode;
	Phonebook	yellow_book;
	Contact 	a_contact;

	yellow_book.initialize(); 
	while (1)
	{
		std::cin >> mode;
		if (!mode.compare("ADD"))
		{
			assigned_contact(&a_contact);
			yellow_book.addContact(a_contact);
		}

		else if (!mode.compare("SEARCH"))
			yellow_book.searchContact();

		else if (!mode.compare("EXIT"))
			break;

		else
			std::cout << "INPUT AVAILDABLE : ADD, SEARCH, EXIT\n";
	}
}
