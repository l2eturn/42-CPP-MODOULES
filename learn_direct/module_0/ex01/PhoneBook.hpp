#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# include <string>
# include "Contact.hpp"

/*
** PhoneBook = array ของ Contact ขนาดคงที่ 8 ช่อง (dynamic allocation ห้ามใช้)
**
** ทำไมต้องมี 2 ตัวแปร _count กับ _next?
**   _count = มีข้อมูลจริงกี่คน (0..8) ใช้ตอน SEARCH ว่าจะ loop ถึงไหน
**   _next  = ช่องถัดไปที่จะเขียน วนกลับด้วย % 8 (circular buffer)
** พอ _count เต็ม 8 แล้ว _next จะวนกลับไปที่ 0 = ทับคนที่เก่าสุดพอดี
** ซึ่งตรงกับโจทย์ "replace the oldest one by the new one"
** -> ไม่ต้องมีตัวแปร _oldest แยก เพราะช่องเก่าสุด == ช่องถัดไปที่จะเขียน
*/
class PhoneBook
{
	public:
		PhoneBook(void);
		~PhoneBook(void);

		void	add(void);
		void	search(void) const;

	private:
		static const int	_capacity = 8;

		Contact	_contacts[_capacity];
		int		_count;
		int		_next;

		void	_displayTable(void) const;
		void	_displayContact(int index) const;

		static bool			_promptField(const std::string &label,
								std::string &out);
		static std::string	_truncate(const std::string &value, int width);
};

#endif
