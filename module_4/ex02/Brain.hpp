#ifndef BRAIN_HPP
# define BRAIN_HPP
# include <iostream>
# include <string>

class Brain
{
	private :
		std::string _ideas[100];

	public :
		Brain(void);
		Brain(const Brain &other);
		Brain &operator=(const Brain &other);
		~Brain(void);

		const std::string &getIdea(int index) const;
		void setIdea(int index, const std::string &idea);
};

#endif
