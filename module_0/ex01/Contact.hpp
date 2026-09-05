#ifndef CONTACT_HPP
# define CONTACT_HPP

# include <string>

class Contact
{
private:
	std::string	_firstName;
	std::string	_lastName;
	std::string	_nickname;
	std::string	_phoneNumber;
	std::string	_darkestSecret;

public:
	Contact(void);
	~Contact(void);

	void	setFirstName(const std::string &value);
	void	setLastName(const std::string &value);
	void	setNickname(const std::string &value);
	void	setPhoneNumber(const std::string &value);
	void	setDarkestSecret(const std::string &value);

	const std::string	&getFirstName(void) const;
	const std::string	&getLastName(void) const;
	const std::string	&getNickname(void) const;
	const std::string	&getPhoneNumber(void) const;
	const std::string	&getDarkestSecret(void) const;
};

#endif
