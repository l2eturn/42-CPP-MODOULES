#ifndef WEAPON_HPP
# define WEAPON_HPP

# include <string>

class Weapon
{
	public:
		Weapon(std::string type);
		~Weapon(void);

		/*
		** คืน const reference: ไม่ copy string (เร็ว) และคนนอกแก้ _type ไม่ได้
		** ถ้าคืนเป็น std::string (by value) จะได้ "สำเนา" -> ตอน setType
		** เปลี่ยนค่า สำเนาเก่าที่ใครถือไว้จะไม่อัปเดตตาม
		*/
		const std::string	&getType(void) const;
		void				setType(std::string type);

	private:
		std::string	_type;
};

#endif
