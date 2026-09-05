#ifndef BRAIN_HPP
# define BRAIN_HPP

# include <string>

/*
** Brain = array ของ std::string 100 ตัว
** ตัวนี้ "ใหญ่" (100 x std::string) -> เป็นตัวอย่างของทรัพยากรที่ต้องจัดการ
*/
class Brain
{
	public:
		Brain(void);
		Brain(const Brain &other);
		Brain	&operator=(const Brain &other);
		~Brain(void);

		void				setIdea(int index, const std::string &idea);
		const std::string	&getIdea(int index) const;

	private:
		static const int	_size = 100;

		std::string	_ideas[_size];
};

#endif
