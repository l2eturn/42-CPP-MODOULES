#ifndef CONTACT_HPP
# define CONTACT_HPP
# include <iostream>

class Contact 
{
	private:
		std::string _firstname;
		std::string _lastname;
		std::string _nickname;
		std::string _phoneNumber;
		std::string _darkestSecret;

	public:
		void		setFirstname(std::string name);
		void		setLastname(std::string name);
		void		setNickname(std::string name);
		void		setPhonenumber(std::string name);
		void		setDarkestsecret(std::string name);

		std::string	getFirstname() const;
};

#endif
