#ifndef HARL_HPP
# define HARL_HPP

# include <string>

/*
** ex06 - หัวใจคือ SWITCH + FALL-THROUGH
**
** โจทย์: แสดง level ที่ขอ "และทุก level ที่สูงกว่า"
** เทคนิค: แปลง string -> ตัวเลข 0..3 แล้ว switch โดย *ไม่ใส่ break*
** ทำให้มัน "ไหลลง" (fall through) case ถัดไปเองอัตโนมัติ
**
**   switch (2) { case 0: ... case 1: ... case 2: warning(); case 3: error(); }
**   -> เข้า case 2 แล้วไหลต่อไป case 3 = ได้ WARNING + ERROR พอดี
**
** ปกติ fall-through คือบั๊ก แต่ที่นี่มันคือ feature -- ต้อง comment ไว้ให้ชัด
** switch ใน C++98 ใช้ได้กับ integral type เท่านั้น (int, char, enum)
** ใช้กับ std::string ไม่ได้ -> จึงต้องแปลงเป็น enum ก่อน
*/
class Harl
{
	public:
		enum Level
		{
			DEBUG = 0,
			INFO = 1,
			WARNING = 2,
			ERROR = 3,
			UNKNOWN = 4
		};

		Harl(void);
		~Harl(void);

		void	complain(std::string level);

		static Level	parseLevel(const std::string &level);

	private:
		void	debug(void);
		void	info(void);
		void	warning(void);
		void	error(void);
};

#endif
