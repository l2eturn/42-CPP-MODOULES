#ifndef HARL_HPP
# define HARL_HPP

# include <string>

/*
** ex05 - หัวใจคือ POINTER TO MEMBER FUNCTION
** โจทย์ห้าม "forest of if/else if/else" ชัดเจน
**
** ===== syntax ที่ต้องจำ =====
**   ประกาศ type : void (Harl::*fn)(void);
**   เอา address : &Harl::debug        <-- ต้องมี & และต้องมี Harl:: เต็มๆ
**   เรียกใช้    : (this->*fn)();      <-- วงเล็บครอบจำเป็น เพราะ () มี
**                 (obj.*fn)();            precedence สูงกว่า ->*
**
** ทำไมต้องเป็น type แยกจาก function pointer ธรรมดา?
** เพราะ member function ต้องมี object มาเป็น this -> pointer ตัวนี้เก็บแค่
** "ฟังก์ชันไหน" ยังไม่มี object -> ตอนเรียกจึงต้องจับคู่กับ object ด้วย ->*
*/
class Harl
{
	public:
		Harl(void);
		~Harl(void);

		void	complain(std::string level);

	private:
		void	debug(void);
		void	info(void);
		void	warning(void);
		void	error(void);
};

#endif
