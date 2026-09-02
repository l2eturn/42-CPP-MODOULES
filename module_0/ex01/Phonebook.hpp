#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

#include <iostream>
#include "Contact.hpp"

class Phonebook
{
	private:
		Contact _contact[8];
		int		_size;
		int		_oldest;
		int		_index;
	public:
		void	addContact(Contact &a_contact);
		void	searchContact();
		void	initialize();
};

#endif
