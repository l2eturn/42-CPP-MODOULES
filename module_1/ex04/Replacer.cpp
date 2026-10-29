#include "Replacer.hpp"

Replacer::Replacer(std::string filename, std::string s1, std::string s2)
	: _filename(filename), _s1(s1), _s2(s2)
{
}

Replacer::~Replacer(void)
{
}

std::string	Replacer::replaceAll(const std::string &content) const
{
	std::string	result;
	size_t		start = 0;
	size_t		found = content.find(_s1);

	while (found != std::string::npos)
	{
		result += content.substr(start, found - start);
		result += _s2;
		start = found + _s1.length();
		found = content.find(_s1, start);
	}
	result += content.substr(start);
	return (result);
}

bool	Replacer::run() const
{
	std::ifstream	infile(_filename.c_str());
	if (!infile.is_open())
	{
		std::cerr << "Error: cannot open " << _filename << std::endl;
		return (false);
	}

	std::string	content;
	std::string	line;
	while (std::getline(infile, line))
	{
		content += line;
		if (!infile.eof())
			content += "\n";
	}
	infile.close();

	std::string		outname = _filename + ".replace";
	std::ofstream	outfile(outname.c_str());
	if (!outfile.is_open())
	{
		std::cerr << "Error: cannot create " << outname << std::endl;
		return (false);
	}
	outfile << replaceAll(content);
	outfile.close();
	return (true);
}
