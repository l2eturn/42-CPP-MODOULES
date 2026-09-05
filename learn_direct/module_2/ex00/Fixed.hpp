#ifndef FIXED_HPP
# define FIXED_HPP

/*
** ex00 - ORTHODOX CANONICAL FORM (OCF)
**
** OCF = 4 อย่างที่ class "ที่โตแล้ว" ต้องมีครบ:
**   1) default constructor          Fixed();
**   2) copy constructor             Fixed(const Fixed &other);
**   3) copy assignment operator     Fixed &operator=(const Fixed &other);
**   4) destructor                   ~Fixed();
**
** ทำไมต้องครบ 4? เพราะถ้าไม่เขียน compiler จะสร้างให้เอง แบบ "copy ทีละ member"
** (shallow copy) ซึ่งพังทันทีถ้า class มี pointer ที่เป็นเจ้าของ memory
** (จะเจอปัญหานี้เต็มๆ ใน module 04 - Brain*)
** -> กฎ Rule of Three: ถ้าต้องเขียนอันใดอันหนึ่งของ (dtor/copy ctor/operator=)
**    แปลว่าต้องเขียนทั้งสามอัน
**
** ===== FIXED-POINT NUMBER คืออะไร =====
** เก็บ int ตัวเดียว แต่ "ตีความ" ว่า 8 bit ล่างคือทศนิยม
**   raw 256 -> 256/256 = 1.0
**   raw 1   -> 1/256   = 0.00390625   <-- นี่คือ epsilon ที่เล็กสุดที่แทนได้
** ต่างจาก float: fixed-point มีความละเอียด "เท่ากันทุกช่วงค่า"
** ส่วน float ยิ่งเลขใหญ่ยิ่งหยาบ (แต่ float ครอบช่วงกว้างกว่ามาก)
*/
class Fixed
{
	public:
		Fixed(void);
		Fixed(const Fixed &other);
		Fixed	&operator=(const Fixed &other);
		~Fixed(void);

		int		getRawBits(void) const;
		void	setRawBits(int const raw);

	private:
		int					_value;
		static const int	_fractionalBits = 8;
};

#endif
