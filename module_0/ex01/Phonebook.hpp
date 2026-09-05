#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include <string>
# include "Contact.hpp"

class PhoneBook
{
private:
	static const int	_capacity = 8;

	Contact	_contacts[_capacity];
	int		_count;
	int		_next;

	static std::string	_truncate(const std::string &value, int width);
	void	_displayTable(void) const;
	void	_displayContact(int index) const;

public:
	PhoneBook(void);
	~PhoneBook(void);

	void	addContact(const Contact &contact);
	void	searchContact(void) const;
};

#endif
