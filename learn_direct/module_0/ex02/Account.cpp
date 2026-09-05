#include <ctime>
#include <iostream>
#include "Account.hpp"

/*
** ex02 - The Job Of Your Dreams
** งานคือ reverse-engineer Account.cpp จาก Account.hpp + log file
**
** ===== หัวใจของ exercise นี้: static member =====
** static member ของ class = ตัวแปรตัวเดียวที่ "ทุก object แชร์กัน"
** ไม่ใช่ของใคร object ไหนเป็นเจ้าของ -> เลยต้อง "นิยาม" (define) ไว้ข้างนอก class
** ในไฟล์ .cpp เพียงที่เดียว ไม่งั้น linker จะไม่เจอ symbol (undefined reference)
**
** static member function ก็เรียกได้โดยไม่ต้องมี object: Account::getNbAccounts()
** และมันเข้าถึงได้แค่ static member (ไม่มี this)
*/
int	Account::_nbAccounts = 0;
int	Account::_totalAmount = 0;
int	Account::_totalNbDeposits = 0;
int	Account::_totalNbWithdrawals = 0;

int	Account::getNbAccounts(void)
{
	return (_nbAccounts);
}

int	Account::getTotalAmount(void)
{
	return (_totalAmount);
}

int	Account::getNbDeposits(void)
{
	return (_totalNbDeposits);
}

int	Account::getNbWithdrawals(void)
{
	return (_totalNbWithdrawals);
}

/*
** format ที่อ่านออกมาจาก log: "[19920104_091532] "
** = [YYYYMMDD_HHMMSS] + เว้นวรรค 1 ตัว, ไม่ขึ้นบรรทัดใหม่
** (บรรทัดที่เหลือถูกต่อท้ายโดยฟังก์ชันที่เรียกมัน)
**
** std::time(NULL) -> วินาทีนับจาก epoch
** std::localtime  -> แตกเป็น struct tm ตามโซนเวลาเครื่อง
** std::strftime   -> จัด format ตาม pattern
*/
void	Account::_displayTimestamp(void)
{
	std::time_t	now = std::time(NULL);
	char		buffer[32];

	std::strftime(buffer, sizeof(buffer), "[%Y%m%d_%H%M%S] ",
		std::localtime(&now));
	std::cout << buffer;
}

/*
** log บรรทัดแรก: [ts] index:0;amount:42;created
** index เริ่มที่ 0 -> เอาค่า _nbAccounts *ก่อน* เพิ่ม มาเป็น index ของตัวเอง
*/
Account::Account(int initial_deposit) :
	_accountIndex(_nbAccounts),
	_amount(initial_deposit),
	_nbDeposits(0),
	_nbWithdrawals(0)
{
	++_nbAccounts;
	_totalAmount += initial_deposit;
	_displayTimestamp();
	std::cout << "index:" << _accountIndex
			  << ";amount:" << _amount
			  << ";created" << std::endl;
}

/*
** log บรรทัดท้ายไฟล์: [ts] index:0;amount:47;closed
*/
Account::~Account(void)
{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex
			  << ";amount:" << _amount
			  << ";closed" << std::endl;
}

/*
** [ts] accounts:8;total:20049;deposits:0;withdrawals:0
*/
void	Account::displayAccountsInfos(void)
{
	_displayTimestamp();
	std::cout << "accounts:" << getNbAccounts()
			  << ";total:" << getTotalAmount()
			  << ";deposits:" << getNbDeposits()
			  << ";withdrawals:" << getNbWithdrawals() << std::endl;
}

/*
** [ts] index:0;amount:42;deposits:0;withdrawals:0
*/
void	Account::displayStatus(void) const
{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex
			  << ";amount:" << _amount
			  << ";deposits:" << _nbDeposits
			  << ";withdrawals:" << _nbWithdrawals << std::endl;
}

int	Account::checkAmount(void) const
{
	return (_amount);
}

/*
** [ts] index:0;p_amount:42;deposit:5;amount:47;nb_deposits:1
** p_amount = previous amount -> ต้องพิมพ์ *ก่อน* บวกเงินเข้า
*/
void	Account::makeDeposit(int deposit)
{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex
			  << ";p_amount:" << _amount
			  << ";deposit:" << deposit;
	_amount += deposit;
	++_nbDeposits;
	_totalAmount += deposit;
	++_totalNbDeposits;
	std::cout << ";amount:" << _amount
			  << ";nb_deposits:" << _nbDeposits << std::endl;
}

/*
** สำเร็จ:  [ts] index:1;p_amount:819;withdrawal:34;amount:785;nb_withdrawals:1
** ถูกปฏิเสธ: [ts] index:0;p_amount:47;withdrawal:refused
**
** เงื่อนไข refused อ่านออกจาก log ได้:
**   index 0: 47 - 321  -> refused   (เงินไม่พอ)
**   index 5: 23 - 275  -> refused
** ที่เหลือถอนได้ทุกตัว -> เงื่อนไขคือ _amount < withdrawal
** (ตรวจกลับ: 8 deposits, 6 withdrawals, total 12442 ตรงกับ log บรรทัดสรุป)
*/
bool	Account::makeWithdrawal(int withdrawal)
{
	_displayTimestamp();
	std::cout << "index:" << _accountIndex
			  << ";p_amount:" << _amount;
	if (_amount < withdrawal)
	{
		std::cout << ";withdrawal:refused" << std::endl;
		return (false);
	}
	_amount -= withdrawal;
	++_nbWithdrawals;
	_totalAmount -= withdrawal;
	++_totalNbWithdrawals;
	std::cout << ";withdrawal:" << withdrawal
			  << ";amount:" << _amount
			  << ";nb_withdrawals:" << _nbWithdrawals << std::endl;
	return (true);
}
