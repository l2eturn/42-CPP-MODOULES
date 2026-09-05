#include <fstream>
#include <iostream>
#include <sstream>
#include "Replacer.hpp"

Replacer::Replacer(const std::string &s1, const std::string &s2) :
	_s1(s1), _s2(s2)
{
}

Replacer::~Replacer(void)
{
}

/*
** ห้ามใช้ std::string::replace -> เลย "ประกอบ string ใหม่" ทีละชิ้นแทน
**
** วิธีคิด: เดินหา _s1 ด้วย find(from)
**   - เจอที่ pos -> เอาช่วง [from, pos) ต่อท้ายผล แล้วต่อด้วย _s2
**                   แล้วกระโดด from ไปหลัง _s1 (from = pos + _s1.length())
**   - ไม่เจอ (npos) -> เอาที่เหลือทั้งหมดต่อท้าย จบ
**
** ที่ต้องระวัง:
**   - from = pos + _s1.length()  ป้องกันการ replace ทับซ้อน/loop ไม่จบ
**   - _s1 ว่าง -> find คืน pos เดิมทุกครั้ง = loop ไม่จบ -> ต้องกันไว้ที่ run()
*/
std::string	Replacer::_replaceAll(const std::string &content) const
{
	std::string	result;
	size_t		from = 0;

	while (true)
	{
		size_t	pos = content.find(_s1, from);

		if (pos == std::string::npos)
		{
			result += content.substr(from);
			break ;
		}
		result += content.substr(from, pos - from);
		result += _s2;
		from = pos + _s1.length();
	}
	return (result);
}

/*
** ห้ามใช้ open/read/write/fopen ของ C -> ใช้ std::ifstream / std::ofstream
** เปิดแบบ binary เพื่อไม่ให้ stream ไปแปลง newline ให้เอง
** อ่านทั้งไฟล์ทีเดียวด้วย rdbuf() ใส่ stringstream -- สั้นและถูกต้อง
*/
bool	Replacer::run(const std::string &filename) const
{
	if (_s1.empty())
	{
		std::cerr << "Error: s1 must not be empty" << std::endl;
		return (false);
	}

	std::ifstream	in(filename.c_str(), std::ios::binary);

	if (!in.is_open())
	{
		std::cerr << "Error: cannot open input file: " << filename << std::endl;
		return (false);
	}

	std::ostringstream	buffer;

	buffer << in.rdbuf();
	in.close();

	std::string		outName = filename + ".replace";
	std::ofstream	out(outName.c_str(), std::ios::binary | std::ios::trunc);

	if (!out.is_open())
	{
		std::cerr << "Error: cannot open output file: " << outName << std::endl;
		return (false);
	}
	out << _replaceAll(buffer.str());
	out.close();
	std::cout << "Wrote " << outName << std::endl;
	return (true);
}
