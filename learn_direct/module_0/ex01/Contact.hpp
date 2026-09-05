#ifndef CONTACT_HPP
# define CONTACT_HPP

# include <string>

/*
** Contact = ข้อมูลคน 1 คน
** ทุก field เป็น private -> ข้างนอกแตะไม่ได้ ต้องผ่าน setter/getter
** getter เป็น const เพราะมันแค่ "อ่าน" ไม่แก้ state ของ object
** คืนค่าเป็น const std::string & เพื่อไม่ copy string ทิ้งเปล่าๆ
*/
class Contact
{
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

	private:
		std::string	_firstName;
		std::string	_lastName;
		std::string	_nickname;
		std::string	_phoneNumber;
		std::string	_darkestSecret;
};

#endif
