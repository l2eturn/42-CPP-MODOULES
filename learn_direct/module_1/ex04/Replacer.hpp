#ifndef REPLACER_HPP
# define REPLACER_HPP

# include <string>

class Replacer
{
	public:
		Replacer(const std::string &s1, const std::string &s2);
		~Replacer(void);

		bool	run(const std::string &filename) const;

	private:
		std::string	_s1;
		std::string	_s2;

		std::string	_replaceAll(const std::string &content) const;
};

#endif
