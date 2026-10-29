#ifndef REPLACER_HPP
# define REPLACER_HPP
# include <iostream>
# include <fstream>
# include <string>

class Replacer
{
	private :
		std::string _filename;
		std::string _s1;
		std::string _s2;

		std::string replaceAll(const std::string &content) const;

	public :
		Replacer(std::string filename, std::string s1, std::string s2);
		~Replacer(void);

		bool run() const;
};

#endif
