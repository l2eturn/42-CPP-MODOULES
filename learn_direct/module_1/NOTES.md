# Module 01 — Memory, references, pointers to members, switch

## 1. Stack vs Heap — คำถามที่โมดูลนี้ถามจริงๆ

subject ex00 เขียนตรงๆ: *"You have to determine in which case it is better to allocate
zombies on the stack or the heap."* — นี่คือข้อสอบ ไม่ใช่คำใบ้

| | Stack | Heap (`new`) |
|---|---|---|
| อายุ | ตายเองตอนจบ `{ }` | อยู่จนกว่าจะ `delete` |
| destructor | เรียกอัตโนมัติ | **คุณต้องเรียก `delete` เอง** |
| ความเร็ว | เร็วมาก (เลื่อน stack pointer) | ช้ากว่า (ขอ memory จาก allocator) |
| ขนาด | จำกัด (~8 MB) รู้ตอน compile | ใหญ่ได้ / กำหนดตอน runtime |
| leak ได้ไหม | ไม่ได้ | ได้ |

**กฎที่ใช้ได้จริง:** ใช้ stack เป็นค่าเริ่มต้น เปลี่ยนไป heap เมื่อมีเหตุผลข้อใดข้อหนึ่ง:
1. object ต้องมีชีวิตข้าม scope (→ `newZombie`)
2. ไม่รู้จำนวน/ขนาดตอน compile (→ `zombieHorde(N, ...)`)
3. object ใหญ่มากจนล้น stack

### `newZombie` ต้องใช้ heap เพราะอะไร

```cpp
Zombie *newZombie(std::string name) {
    Zombie z(name);
    return (&z);      // ❌ z ตายไปแล้วตอน return -> dangling pointer
}
```
stack frame ของฟังก์ชันถูกทำลายตอน return → pointer ชี้ไปที่หน่วยความจำที่ไม่ใช่ของเราแล้ว
อาจ "ดูเหมือนทำงานได้" ในการรันบางครั้ง — นั่นคือสิ่งที่ทำให้ undefined behavior อันตราย

### `randomChump` ต้องใช้ stack เพราะอะไร

zombie ตัวนี้ใช้แค่ในฟังก์ชัน → stack ให้ destructor อัตโนมัติ = **ลืม delete ไม่ได้**

---

## 2. `new` / `delete` — กฎเหล็ก

```
new      ต้องคู่กับ  delete
new[]    ต้องคู่กับ  delete[]
```

สลับคู่ = undefined behavior:
- `delete` แทน `delete[]` → เรียก destructor แค่ **ตัวแรก** → ที่เหลือ leak
- `delete[]` แทน `delete` → มักจะ crash ทันที

```cpp
Zombie *horde = new Zombie[N];   // "a single allocation" ตามที่โจทย์กำหนด
delete [] horde;                 // ต้องคู่กัน
```

**`new Zombie[N]` เรียก default constructor ทุกตัว** — ส่ง argument ไม่ได้
→ นั่นคือเหตุผลที่ ex01 ต้องมี `Zombie(void)` + `setName()` เพิ่มจาก ex00

`delete NULL` ปลอดภัย (ไม่ทำอะไร) — ไม่ต้องเช็คก่อน

---

## 3. Reference vs Pointer — ex02 คือการพิสูจน์ด้วยตา

| | pointer | reference |
|---|---|---|
| ประกาศ | `std::string *p = &s;` | `std::string &r = s;` |
| อ่านค่า | `*p` | `r` |
| เอา address | `p` | `&r` (ได้เท่ากับ `&s`) |
| เป็น NULL ได้ | ✅ | ❌ ต้องผูกของจริงตอนประกาศ |
| ชี้ที่อื่นทีหลัง | ✅ `p = &other` | ❌ `r = other` คือ **copy ค่าทับ `s`** |
| ต้อง init | ไม่ | ✅ บังคับ |

`ex02/main.cpp` พิมพ์ address ทั้ง 3 แบบออกมาแล้วมันเท่ากันหมด — เพราะทั้งสามพูดถึง
หน่วยความจำก้อนเดียวกัน **reference ไม่ใช่ object ใหม่ มันคือชื่อเรียกอีกชื่อ**

### เลือกใช้อันไหน (ex03 คือคำตอบ)

subject ถามไว้: *"In which case do you think it would be best to use a pointer to
Weapon? And a reference to Weapon?"*

```
HumanA — "will always be armed"        -> Weapon &   (compiler บังคับให้มีเสมอ)
HumanB — "may not always have a weapon" -> Weapon *   (NULL = ยังไม่มี, เปลี่ยนได้)
```

การเลือก type **คือ** การเขียนกฎธุรกิจลงไปในโค้ด — reference member ทำให้
"HumanA ไม่มีอาวุธ" เป็นสิ่งที่**เขียนไม่ได้เลย** ไม่ใช่แค่ "ไม่ควรเขียน"

### ทำไม `getType()` ต้องคืน `const std::string &`

```cpp
const std::string &getType(void) const;   // ✅
std::string        getType(void) const;   // ⚠️ คืนสำเนา
```
โจทย์บังคับ `const reference` และมีเหตุผล: ไม่ copy string (เร็ว) + คนนอกแก้ไม่ได้

**และนี่คือกลไกที่ทำให้ test case ของโจทย์ผ่าน:**
```cpp
club.setType("some other type of club");
bob.attack();   // ต้องเปลี่ยนตาม
```
ถ้า `HumanA` เก็บ `Weapon` แบบ by value (สำเนา) → `attack()` ครั้งที่สองจะยังพูดชื่อเก่า

### Ownership — ใครทำลาย

```cpp
HumanB::~HumanB(void) { }   // ✅ ไม่ delete _weapon
```
`Weapon club` ถูกสร้างบน stack ใน `main` → `main` เป็นเจ้าของ
HumanB แค่ "ยืมดู" → ถ้า `delete` = double free ตอนออก scope

**"ใครสร้าง คนนั้นทำลาย"** — กฎนี้จะกลับมาอีกใน module 04 (`unequip` ห้าม delete)

---

## 4. Pointer to member function — ex05

โจทย์บอกชัด: *"Harl has to complain without using a forest of if/else if/else.
He doesn't think twice!"*

### Syntax ที่ต้องท่อง

```cpp
void (Harl::*fn)(void);          // ประกาศ type
fn = &Harl::debug;               // ต้องมี & และ Harl:: เต็มๆ
(this->*fn)();                   // เรียกผ่าน pointer
(obj.*fn)();                     // เรียกผ่าน object
```

**วงเล็บครอบ `(this->*fn)` จำเป็น** เพราะ `()` มี precedence สูงกว่า `->*`
เขียน `this->*fn()` = compiler พยายามเรียก `fn()` ก่อน → error

### ทำไมต้องเป็น type แยกจาก function pointer ธรรมดา

member function ต้องมี object มาเป็น `this` → pointer ตัวนี้เก็บแค่ "ฟังก์ชันไหน"
ยังไม่มี object → ตอนเรียกต้องจับคู่กับ object ด้วย `->*` หรือ `.*`
(ขนาดของมันก็ต่างจาก function pointer ปกติด้วย เพราะต้องรองรับ virtual)

### โครงสร้างที่ใช้: lookup table

```cpp
const std::string levels[4]      = {"DEBUG", "INFO", "WARNING", "ERROR"};
void (Harl::*functions[4])(void) = {&Harl::debug, &Harl::info,
                                    &Harl::warning, &Harl::error};
```
index ตรงกัน → หา index ของ level แล้วเรียกที่ index เดียวกัน
**เพิ่ม level ใหม่ = แก้ 2 array ไม่ต้องแตะ logic เลย**

---

## 5. `switch` + fall-through — ex06

โจทย์: *"You must use, and maybe discover, the switch statement"* และ
*"one of the most effective is to SWITCH it off"*

### เทคนิค: ไม่ใส่ `break` โดยตั้งใจ

```cpp
switch (parseLevel(level)) {
    case DEBUG:   debug();    // fall through
    case INFO:    info();     // fall through
    case WARNING: warning();  // fall through
    case ERROR:   error();  break ;
    default:      ...       break ;
}
```
เข้า `case WARNING` → ไหลต่อไป `case ERROR` เอง = ได้ WARNING + ERROR พอดี
ตรงกับโจทย์ *"display all messages from this level and above"*

ปกติ fall-through คือบั๊ก → **ต้องเขียน comment `// fall through` กำกับไว้**
ไม่งั้น peer evaluator (และตัวคุณเองอีก 3 เดือน) จะคิดว่าลืมใส่ `break`

### `switch` ใช้กับ `std::string` ไม่ได้

`switch` ใน C++ รับได้แค่ integral type (`int`, `char`, `enum`)
→ ต้องแปลง string เป็น `enum` ก่อน (`parseLevel`) — นี่คือเหตุผลที่ต้องมี enum

```cpp
enum Level { DEBUG = 0, INFO = 1, WARNING = 2, ERROR = 3, UNKNOWN = 4 };
```
ให้ค่าเป็น 0..3 เพื่อ map กับ index ของ array ได้ตรงๆ
และ `static_cast<Level>(i)` แปลง int → enum ได้

---

## 6. ex04 — ห้ามใช้ `std::string::replace`

โจทย์ห้าม `replace` และห้ามฟังก์ชันไฟล์ของ C (`fopen`, `read`, ...)

### วิธีคิด: ประกอบ string ใหม่ทีละชิ้น

```
เดินหา s1 ด้วย find(from)
  เจอที่ pos -> ต่อช่วง [from, pos) เข้าผล -> ต่อ s2 -> from = pos + s1.length()
  ไม่เจอ     -> ต่อที่เหลือทั้งหมด -> จบ
```

**สองกับดัก:**
1. `from = pos + _s1.length()` ไม่ใช่ `pos + 1` → ป้องกันการ replace ทับซ้อน
2. **`s1` ว่าง** → `find("")` คืน `from` ทุกครั้ง = **loop ไม่จบ**
   → ต้องเช็คและ error ออกมาก่อน (ลอง `./sedislame f.txt "" x` ดู)

### อ่านไฟล์ทั้งก้อน

```cpp
std::ifstream      in(filename.c_str(), std::ios::binary);
std::ostringstream buffer;
buffer << in.rdbuf();          // อ่านทั้งไฟล์บรรทัดเดียว
std::string content = buffer.str();
```
- `.c_str()` จำเป็นใน C++98 (constructor ที่รับ `std::string` เพิ่มมาใน C++11)
- `std::ios::binary` → stream ไม่แปลง newline ให้เอง
- เช็ค `is_open()` ทุกครั้ง — โจทย์บอก *"handle unexpected inputs and errors"*

---

## เช็คความเข้าใจ

1. `newZombie` ใช้ heap, `randomChump` ใช้ stack — อธิบายเหตุผลของแต่ละอันในประโยคเดียว
2. `new Zombie[5]` แล้ว `delete` (ไม่มี `[]`) — เกิดอะไรขึ้นกับ zombie ตัวที่ 2-5?
3. `HumanA` ใช้ reference, `HumanB` ใช้ pointer — ถ้าสลับกันจะพังตรงไหน?
4. ทำไม `(this->*fn)()` ต้องมีวงเล็บครอบ?
5. `switch` ใช้กับ `std::string` ไม่ได้ — ทำไม?
6. ถ้า `s1` เป็น string ว่างใน ex04 จะเกิดอะไรถ้าไม่กัน?
7. `Weapon &getType()` (ไม่มี const) จะเปิดช่องให้ทำอะไรที่ไม่ควรทำได้?
