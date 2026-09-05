#include "Zombie.hpp"

/*
** "allocate N Zombie objects in a single allocation"
** -> new Zombie[N] ครั้งเดียว ไม่ใช่ loop new Zombie ทีละตัว
**
** ===== กฎเหล็กที่ต้องจำ =====
**   new     ต้องคู่กับ  delete
**   new[]   ต้องคู่กับ  delete[]
** สลับคู่กัน = undefined behavior (delete แทน delete[] จะเรียก destructor
** แค่ตัวแรกตัวเดียว -> ที่เหลือ leak)
**
** N <= 0 -> คืน NULL, เพราะ new Zombie[0] ใช้ได้แต่ new Zombie[-1] จะ throw
*/
Zombie	*zombieHorde(int N, std::string name)
{
	if (N <= 0)
		return (NULL);

	Zombie	*horde = new Zombie[N];

	for (int i = 0; i < N; ++i)
		horde[i].setName(name);
	return (horde);
}
