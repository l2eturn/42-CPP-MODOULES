#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <string>

/*
** ex01 ต้องมี default constructor ด้วย!
** เพราะ new Zombie[N] เรียก default constructor ของทุกตัว -- ส่ง argument ไม่ได้
** เลยต้องมี setName() มาตั้งชื่อทีหลัง
*/
class Zombie
{
	public:
		Zombie(void);
		Zombie(std::string name);
		~Zombie(void);

		void	setName(std::string name);
		void	announce(void);

	private:
		std::string	_name;
};

Zombie	*zombieHorde(int N, std::string name);

#endif
