# Module 00 — Namespaces, classes, static, stdio streams

## แนวคิดหลัก

### 1. class = struct + ฟังก์ชัน + การควบคุมการเข้าถึง

ใน C คุณมี `struct` ที่เก็บข้อมูล แล้วเขียนฟังก์ชันแยกที่รับ `struct*` เข้าไป
C++ ยุบสองอย่างนี้เข้าด้วยกัน และเพิ่ม "ใครแตะได้บ้าง"

```
private   : เฉพาะ class ตัวเอง          <-- ค่าเริ่มต้นของ class
protected : class ตัวเอง + คลาสลูก       <-- จะได้ใช้จริงใน module 03
public    : ใครก็ได้
```

**กฎที่ subject บอกไว้:** อะไรที่ใช้แต่ข้างในเป็น `private`, อะไรที่ข้างนอกต้องใช้เป็น `public`

### 2. `this` คือ pointer ที่หายไปจาก C

```cpp
void Contact::setFirstName(const std::string &v) { _firstName = v; }
// compiler แปลงเป็นประมาณ:
// void setFirstName(Contact *this, const std::string &v) { this->_firstName = v; }
```
`_firstName` เฉยๆ คือ `this->_firstName` — เลยรู้ว่าจะเขียนลง object ตัวไหน

### 3. `const` ท้าย member function

```cpp
const std::string &getFirstName(void) const;
//                               ^^^^^ สัญญาว่า "ฟังก์ชันนี้ไม่แก้ object"
```
ถ้าไม่ใส่ `const` → `const Contact c; c.getFirstName();` **คอมไพล์ไม่ผ่าน**
ติดนิสัยใส่ `const` ให้ getter ทุกตัวไว้เลย ไม่งั้นจะเจอ error แปลกๆ ใน module 02

### 4. Initialization list — ไม่ใช่แค่สไตล์

```cpp
PhoneBook::PhoneBook(void) : _count(0), _next(0) { }   // ✅ init
PhoneBook::PhoneBook(void) { _count = 0; _next = 0; }  // ⚠️ สร้างเปล่า แล้วเขียนทับ
```
สำคัญเพราะ:
- **จำเป็น** สำหรับ `const` member และ `reference` member (assign ทีหลังไม่ได้เลย)
- **จำเป็น** สำหรับการเรียก constructor ของคลาสแม่ (module 03)
- เร็วกว่าสำหรับ member ที่เป็น object ใหญ่ๆ (ไม่ต้องสร้างเปล่าแล้ว copy ทับ)

### 5. `static` member — หัวใจของ ex02

```cpp
class Account {
    static int _nbAccounts;   // ประกาศใน class (แชร์กันทุก object)
};
int Account::_nbAccounts = 0; // ต้อง "นิยาม" ใน .cpp เพียงที่เดียว
```

ถ้าลืมบรรทัดที่สอง → `Undefined symbols for architecture arm64: Account::_nbAccounts`
นี่คือ error ที่คนติดกันเยอะที่สุดใน ex02

`static member function` เรียกได้โดยไม่มี object: `Account::getNbAccounts()`
แต่มันไม่มี `this` → เข้าถึงได้แค่ static member

---

## ex00 — Megaphone

จุดเดียวที่ต้องระวัง: `std::toupper` รับ `int` ที่ต้องอยู่ใน range ของ `unsigned char`
ส่ง `char` ที่ติดลบเข้าไป = undefined behavior

```cpp
std::cout << static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
```

**`static_cast` ต่างจาก `(char)` อย่างไร?** ทำงานเหมือนกันในเคสนี้ แต่ `static_cast`
ค้นหาง่ายด้วย grep, และ compiler ปฏิเสธการแปลงที่ไม่สมเหตุสมผลให้ (เช่นข้าม type ที่ไม่เกี่ยวกัน)
subject บอก *"Solve the exercises in a C++ manner"* — cast แบบ C++ คือส่วนหนึ่งของคำตอบนั้น

---

## ex01 — PhoneBook

### ทำไมใช้ `_count` + `_next` แทน `_size` + `_oldest` + `_index`

circular buffer ต้องการแค่สองตัว:

```
_count = มีข้อมูลจริงกี่คน (0..8) ใช้ตอน SEARCH ว่า loop ถึงไหน
_next  = ช่องถัดไปที่จะเขียน, วนด้วย % 8
```

**เมื่อ buffer เต็ม ช่องที่เก่าสุดคือช่องถัดไปที่จะเขียนพอดี** — ไม่ต้องมีตัวแปรแยก

```
เพิ่มคนที่ 9: _next วนกลับมาที่ 0 = ทับคนที่ 1 (เก่าสุด) ✅
```

### การจัดตาราง — `std::setw`

```cpp
std::cout << std::setw(10) << "Index" << "|";
```
- `setw` มีผลกับ **การ insert ครั้งถัดไปครั้งเดียว** → ต้องเรียกซ้ำทุกคอลัมน์
- default คือ **ชิดขวา** (right-aligned) ตรงตามที่โจทย์ขอ ไม่ต้องทำอะไรเพิ่ม
- ตัดข้อความ: ยาวเกิน 10 → เอา 9 ตัวแรก + `'.'`
  `"Bartholomew"` (11) → `"Bartholom."` (10)

### ทำไมใช้ `std::getline` ไม่ใช่ `std::cin >>`

| | `std::cin >> s` | `std::getline(std::cin, s)` |
|---|---|---|
| เจอ space | หยุด → "John Smith" ได้แค่ "John" | อ่านทั้งบรรทัด ✅ |
| ทิ้ง `\n` ค้างใน buffer | ค้าง → บรรทัดต่อไปเพี้ยน | ไม่ค้าง |

การผสม `>>` กับ `getline` คือแหล่งบั๊กคลาสสิก — **เลือกใช้ `getline` อย่างเดียวไปเลย**

### จัดการ EOF

```cpp
if (!std::getline(std::cin, command))
    break ;   // Ctrl-D หรือ input หมด
```
ถ้าไม่เช็ค → โปรแกรม loop ไม่หยุดเมื่อ stdin ปิด (`echo ADD | ./phonebook` จะค้าง)
peer evaluator ชอบทดสอบด้วย Ctrl-D

### อ่าน index อย่างปลอดภัย

```cpp
std::istringstream ss(line);
if (!(ss >> index) || !ss.eof() || index < 0 || index >= _count)
```
- `ss >> index` fail → ไม่ใช่ตัวเลขเลย
- `!ss.eof()` → มีขยะต่อท้าย เช่น `"3abc"`
- อ่านเข้า `std::string` ก่อนแล้วแปลงเอง → `std::cin` ไม่เข้า fail state ค้าง

---

## เทียบกับโค้ดที่คุณเขียนไว้ใน `module_0/ex01`

โค้ดปัจจุบันมี 6 จุดที่ต้องแก้ก่อนส่ง:

| # | ไฟล์ | ปัญหา | ทำไมสำคัญ |
|---|---|---|---|
| 1 | `Phonebook.cpp:45-47` | มี `/* first name */` เป็น comment คาอยู่กลาง expression | **คอมไพล์ไม่ผ่าน** — `std::setw(10) << << "\|"` ไม่ใช่ C++ |
| 2 | `Makefile:14` | `%.o: %.c` ควรเป็น `%.cpp` | rule นี้ไม่เคย match → make ใช้ **built-in rule** แทน ซึ่งเรียก `$(CXX) $(CXXFLAGS) $(CPPFLAGS)` — ดูรายละเอียดข้างล่าง |
| 3 | ชื่อคลาส | `Phonebook` แต่ subject เขียน `PhoneBook` (B ใหญ่) | subject กำหนดชื่อไฟล์/คลาสไว้ และบอกว่า "Name your files, classes... as required" |
| 4 | `Contact.hpp` | มีแค่ `getFirstname()` ขาด getter อีก 4 ตัว | SEARCH แสดง last name / nickname ไม่ได้ |
| 5 | `main.cpp` | ใช้ `Contact a_contact` ตัวเดียวซ้ำ + ไม่ตรวจ field ว่าง | subject: "A saved contact can't have empty fields" |
| 6 | `main.cpp:40` | `std::cin >> mode` ไม่เช็ค EOF | Ctrl-D → infinite loop |

### เจาะจุดที่ 2 — Makefile ของคุณ "รอดแบบฟลุค"

รัน `make -n` ใน `module_0/ex01` จะเห็นว่า flag ถูกใส่ครบจริง:

```
c++  -Wall -Wextra -Werror -std=c++98  -c -o main.o main.cpp
```

เพราะ `%.o: %.c` ไม่ match `.cpp` → make ตกไปใช้ **built-in rule** ซึ่งคือ
`$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c` — และมันไปหยิบ `CPPFLAGS` ของคุณมาใช้พอดี

แต่มันรอดด้วยความบังเอิญ 2 ชั้น:
1. `$(CXX)` ที่ built-in rule ใช้ default เป็น `c++` อยู่แล้ว → **ตัวแปร `CPP = c++` ที่คุณตั้งไว้ไม่ถูกใช้เลย**
   ถ้าเปลี่ยนเป็น `CPP = g++` จะไม่มีผลอะไร — เป็นกับดักที่หาสาเหตุยากมาก
2. `CPPFLAGS` ตามธรรมเนียมหมายถึง **C PreProcessor flags** (`-I`, `-D`) ไม่ใช่ flag warning
   ที่มันได้ผลเพราะ built-in rule เอาไปต่อท้ายให้ ไม่ใช่เพราะชื่อถูก

**แก้ให้ถูกคือ** ใช้ชื่อตามธรรมเนียมและเขียน rule ให้ match จริง:
```make
CXX      = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
```
เทียบกับ `learn_direct/module_0/ex01/Makefile` ได้เลย

อีกจุดที่ควรเพิ่ม: `.PHONY: all clean fclean re` — ป้องกันกรณีมีไฟล์ชื่อ `clean` อยู่ในโฟลเดอร์
แล้ว make บอกว่า "nothing to be done"

จุดที่คุณทำถูกแล้วและควรเก็บไว้: แนวคิด `_oldest = (_oldest + 1) % 8` ถูกต้อง —
เพียงแต่รวมกับ `_index` ให้เป็นตัวเดียวได้

---

## ex02 — Account (reverse engineering)

วิธีทำ: อ่าน `19920104_091532.log` แล้วเดา format กลับ

| log | ฟังก์ชัน |
|---|---|
| `index:0;amount:42;created` | constructor |
| `accounts:8;total:20049;deposits:0;withdrawals:0` | `displayAccountsInfos()` (static) |
| `index:0;amount:42;deposits:0;withdrawals:0` | `displayStatus()` |
| `index:0;p_amount:42;deposit:5;amount:47;nb_deposits:1` | `makeDeposit()` |
| `index:0;p_amount:47;withdrawal:refused` | `makeWithdrawal()` กรณีเงินไม่พอ |
| `index:0;amount:47;closed` | destructor |

### จุดที่ต้องสังเกตให้เจอ

**`p_amount` = previous amount** → ต้องพิมพ์ **ก่อน** แก้ `_amount`

**เงื่อนไข refused** หาได้จากการเทียบตัวเลข:
```
index 0: มี 47   ถอน 321  -> refused
index 5: มี 23   ถอน 275  -> refused
index 1: มี 819  ถอน 34   -> ผ่าน
```
→ เงื่อนไขคือ `_amount < withdrawal`

ตรวจคำตอบ: log สรุปว่า `deposits:8;withdrawals:6` และ total ลดจาก 21524 → 12442
`21524 - (34+657+4+76+657+7654) = 12442` ✅ ตรง

**timestamp** `[19920104_091532]` = `[%Y%m%d_%H%M%S] ` (มีเว้นวรรคท้าย ไม่มี newline)

**ห้ามเขียน copy constructor** — log มี `created` แค่ 8 บรรทัด แต่ `tests.cpp` สร้าง
`std::vector<Account>` จาก array → ถ้าเขียน copy ctor ที่พิมพ์ข้อความ จะมีบรรทัดเกิน

### ตรวจคำตอบตัวเอง

```bash
cd learn_direct/module_0/ex02 && make
./account | sed 's/^\[[0-9_]*\] //' > /tmp/mine.txt
sed 's/^\[[0-9_]*\] //' 19920104_091532.log > /tmp/ref.txt
diff /tmp/mine.txt /tmp/ref.txt
```
เหลือต่างแค่ **ลำดับของบรรทัด `closed`** — subject บอกไว้แล้วว่ายอมรับได้:
> The order in which the destructors are called may differ depending on your compiler/OS

---

## เช็คความเข้าใจ (ตอบได้โดยไม่เปิดโค้ด?)

1. ถ้าลบบรรทัด `int Account::_nbAccounts = 0;` ออก จะเกิดอะไร และ error อยู่ขั้นตอนไหน (compile / link)?
2. ทำไม `getFirstName()` ต้องมี `const` ต่อท้าย?
3. `std::setw(10)` มีผลกี่ครั้ง?
4. ถ้าเปลี่ยน phonebook ให้เก็บได้ 16 คน ต้องแก้กี่ที่? (ตอบ: 1 ที่ ถ้าออกแบบดี)
5. `_next = (_next + 1) % 8` ถ้าเปลี่ยนเป็น `_next++` เฉยๆ จะพังตอนไหน?
6. `p_amount` ทำไมต้องพิมพ์ก่อนอัปเดต `_amount`?
