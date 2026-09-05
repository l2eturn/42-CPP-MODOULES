#include "Contact.hpp"

/*
** std::string มี default constructor ที่ทำให้เป็น "" อยู่แล้ว
** เลยไม่ต้องทำอะไรใน constructor -- แต่เขียนไว้ให้ครบรูปแบบ
*/
Contact::Contact(void)
{
}

Contact::~Contact(void)
{
}

void	Contact::setFirstName(const std::string &value)
{
	_firstName = value;
}

void	Contact::setLastName(const std::string &value)
{
	_lastName = value;
}

void	Contact::setNickname(const std::string &value)
{
	_nickname = value;
}

void	Contact::setPhoneNumber(const std::string &value)
{
	_phoneNumber = value;
}

void	Contact::setDarkestSecret(const std::string &value)
{
	_darkestSecret = value;
}

const std::string	&Contact::getFirstName(void) const
{
	return (_firstName);
}

const std::string	&Contact::getLastName(void) const
{
	return (_lastName);
}

const std::string	&Contact::getNickname(void) const
{
	return (_nickname);
}

const std::string	&Contact::getPhoneNumber(void) const
{
	return (_phoneNumber);
}

const std::string	&Contact::getDarkestSecret(void) const
{
	return (_darkestSecret);
}
