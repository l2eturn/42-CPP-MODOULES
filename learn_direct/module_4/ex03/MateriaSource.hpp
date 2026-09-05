#ifndef MATERIASOURCE_HPP
# define MATERIASOURCE_HPP

# include "AMateria.hpp"
# include "IMateriaSource.hpp"

/*
** MateriaSource = "โรงงาน" ที่จำแม่พิมพ์ (template) ได้ 4 แบบ
** แล้วผลิตของใหม่จาก string ชื่อชนิด
**
** learnMateria(AMateria *m):
**   โจทย์บอก "Copies the Materia passed as a parameter and stores it"
**   -> เก็บ m->clone() ไม่ใช่ m เอง
**   แต่ถ้าเก็บ clone แล้ว m ที่รับมา (มักเป็น new Ice()) จะหลุดมือ = leak
**   -> ทางออกที่ปลอดภัย: เก็บ m เองไปเลย (รับ ownership) -- ตรงตามที่ main
**      ตัวอย่างในโจทย์เขียน src->learnMateria(new Ice()); โดยไม่ delete
**   ที่นี่เลือกรับ ownership ตรงๆ แล้ว delete ใน dtor -> ไม่ leak แน่นอน
**
** createMateria(type): หา template ที่ type ตรง -> คืน clone()
**   ไม่เจอ -> return 0 ตามที่โจทย์กำหนด
*/
class MateriaSource : public IMateriaSource
{
	public:
		MateriaSource(void);
		MateriaSource(MateriaSource const &other);
		MateriaSource	&operator=(MateriaSource const &other);
		virtual ~MateriaSource(void);

		virtual void		learnMateria(AMateria *m);
		virtual AMateria	*createMateria(std::string const &type);

	private:
		static const int	_capacity = 4;

		AMateria	*_templates[_capacity];

		void	_clear(void);
		void	_copyFrom(MateriaSource const &other);
};

#endif
