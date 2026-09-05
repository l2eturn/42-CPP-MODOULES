# Module 03 — Inheritance

## 1. ลำดับ constructor / destructor (peer eval ถามแน่นอน)

subject ถามตรงๆ: *"When a ScavTrap is created, the program starts by constructing
a ClapTrap. Destruction occurs in reverse order. **Why?**"*

```
สร้าง ScavTrap:   ClapTrap ctor  ->  ScavTrap ctor      (ฐาน -> ลูก)
ทำลาย ScavTrap:   ScavTrap dtor  ->  ClapTrap dtor      (ลูก -> ฐาน)
```

### คำตอบ

คลาสลูก **"มี" ส่วนของคลาสแม่อยู่ในตัว** และโค้ดของลูกอาจใช้ member ของแม่

- **ตอนสร้าง:** ส่วนของแม่ต้องพร้อมก่อน ลูกจึงจะใช้ได้อย่างปลอดภัย
  (`ScavTrap` ctor เขียน `_hitPoints = 100;` ได้เพราะ `ClapTrap` ctor สร้าง `_hitPoints` แล้ว)
- **ตอนทำลาย:** ลูกต้องเก็บของตัวเองให้เสร็จก่อน แม่จึงพังลงได้
  (ถ้าแม่ตายก่อน แล้ว dtor ลูกไปอ่าน `_name` ของแม่ → อ่านหน่วยความจำที่ถูกทำลายแล้ว)

**อุปมา:** สร้างบ้านลงเสาเข็มก่อนมุงหลังคา / รื้อบ้านรื้อหลังคาก่อนถอนเสาเข็ม

---

## 2. `private` → `protected`

ex00 โจทย์บอกว่า attribute เป็น `private`
ex01 โจทย์บอก *"ScavTrap will use the attributes of ClapTrap (update ClapTrap accordingly)"*

```
private   : เฉพาะ class ตัวเอง — คลาสลูกก็แตะไม่ได้
protected : class ตัวเอง + คลาสลูกทุกชั้น
public    : ใครก็ได้
```

→ ต้องเปลี่ยนเป็น `protected` ตั้งแต่ ex01 (ในโฟลเดอร์นี้ ex00 ใช้ `private`,
ex01–ex03 ใช้ `protected` ตามโจทย์)

**ข้อควรคิด:** `protected` ทำให้ encapsulation อ่อนลง — คลาสลูกทุกตัวผูกกับโครงสร้างข้างในของแม่
ทางเลือกที่ดีกว่าในโปรเจกต์จริงคือ `private` + `protected` setter แต่ที่นี่ทำตามโจทย์

---

## 3. เรียก constructor ของแม่

```cpp
ScavTrap::ScavTrap(const std::string &name) : ClapTrap(name) {
    _hitPoints = 100;
    _energyPoints = 50;
    _attackDamage = 20;
}
```

**ถ้าไม่เขียน `: ClapTrap(name)`** → compiler เรียก `ClapTrap()` (default) ให้แทน
→ จะได้ชื่อ `"default"` ไม่ใช่ชื่อที่ส่งมา (บั๊กที่เจอบ่อยที่สุดของ ex01)

ตั้ง stat ใน body ได้เพราะ `ClapTrap` ctor ตั้ง default (10/10/0) ไปแล้ว
เราแค่เขียนทับ — ใส่ใน init list ของ `ScavTrap` ไม่ได้เพราะ member เป็นของแม่ ไม่ใช่ของเรา

### `operator=` ของคลาสลูก

```cpp
ScavTrap &ScavTrap::operator=(const ScavTrap &other) {
    if (this != &other)
        ClapTrap::operator=(other);   // ต้องเรียกของแม่ด้วย!
    return (*this);
}
```
ลืมบรรทัดนี้ → member ของแม่ (`_name`, `_hitPoints`, …) ไม่ถูก copy เลย

---

## 4. Function hiding — กับดักที่ต้องรู้ก่อนเข้า module 04

`ScavTrap::attack()` ทับ `ClapTrap::attack()` แต่ **`attack` ไม่ได้เป็น `virtual`**
→ นี่คือ **hiding** (ทับชื่อ) ไม่ใช่ **overriding**

```cpp
ScavTrap scav("Shadowed");
scav.attack("X");             // -> ข้อความของ ScavTrap  ✅

ClapTrap &asBase = scav;
asBase.attack("X");           // -> ข้อความของ ClapTrap  ⚠️
```

**เพราะ compiler เลือกฟังก์ชันตาม type ของตัวแปรตอน compile** (static binding)
ไม่สนว่าข้างในเป็นอะไรจริงๆ

`ex01/main.cpp` มีการทดสอบจุดนี้ให้เห็นด้วยตา — **นี่คือปัญหาที่ `virtual` (module 04) มาแก้**

### `virtual` destructor — ควรมีตั้งแต่ตอนนี้

```cpp
virtual ~ClapTrap(void);
```
โจทย์ module 03 ไม่ได้บังคับ แต่ควรทำทุกครั้งที่คลาสมีลูก:
```cpp
ClapTrap *p = new ScavTrap("x");
delete p;    // dtor ไม่ virtual -> เรียกแค่ ~ClapTrap -> ของที่ ScavTrap จองไว้ leak
```

---

## 5. ⭐ ex03: THE DIAMOND PROBLEM (ข้อที่ยากที่สุดของโมดูล)

```
        ClapTrap
        /      \
 ScavTrap      FragTrap
        \      /
       DiamondTrap
```

### ปัญหา

สืบทอดแบบธรรมดา → `DiamondTrap` มี **`ClapTrap` สองชุด**
(ชุดหนึ่งมาทาง `ScavTrap` อีกชุดมาทาง `FragTrap`)

ผลที่ตามมา:
- `_name` มี 2 ตัว, `_hitPoints` มี 2 ตัว
- `ClapTrap` ctor/dtor ถูกเรียก **2 ครั้ง**
- เขียน `_name` เฉยๆ → **ambiguous** คอมไพล์ไม่ผ่าน

แต่โจทย์บอกว่า *"the ClapTrap instance of DiamondTrap will be created **once, and
only once**. Yes, there's a trick."*

### ทางแก้: VIRTUAL INHERITANCE

```cpp
class ScavTrap : virtual public ClapTrap { ... };
class FragTrap : virtual public ClapTrap { ... };
class DiamondTrap : public ScavTrap, public FragTrap { ... };
```

`virtual` ที่นี่บอกว่า *"ถ้ามีใครสืบทอดฉันหลายทาง ให้แชร์ `ClapTrap` ชุดเดียว"*
→ `ClapTrap` มีชุดเดียว, ctor/dtor เรียกครั้งเดียว ✅

**ยืนยันด้วยตัวเอง:**
```bash
cd learn_direct/module_3/ex03 && make
./diamondtrap | grep -c "ClapTrap Diamond_clap_name constructor called"   # ได้ 1
./diamondtrap | grep -c "ClapTrap Diamond_clap_name destructor called"    # ได้ 1
```

### กฎพิเศษของ virtual base ที่ต้องรู้

**ผู้ที่เรียก constructor ของ virtual base คือ "คลาสที่ derived สุด"**

```cpp
DiamondTrap::DiamondTrap(const std::string &name)
    : ClapTrap(name + "_clap_name"),   // <-- DiamondTrap เรียกเอง
      ScavTrap(name),                  //     ที่ ScavTrap เขียน : ClapTrap(name)
      FragTrap(name),                  //     ไว้ จะถูก "ข้าม"
      _name(name)
```

ที่ `ScavTrap` เขียน `: ClapTrap(name)` ไว้ → ตอนสร้าง `ScavTrap` เดี่ยวๆ มันทำงาน
แต่ตอนสร้าง `DiamondTrap` มันถูกข้าม → `DiamondTrap` **ต้อง** เรียก `ClapTrap` เอง
(ถ้าไม่เรียก จะได้ `ClapTrap()` default = ชื่อ `"default"`)

### ลำดับใน initialization list — `-Wreorder` จะฟ้อง

ต้องเรียงตามลำดับที่ compiler สร้างจริง:
```
virtual base (ClapTrap) -> base ตามลำดับประกาศ (ScavTrap, FragTrap) -> member ของตัวเอง
```
เรียงผิด → `-Wall` เตือน `-Wreorder` → `-Werror` ทำ build ตก

### ค่า stat ที่โจทย์กำหนด

```
hit points    จาก FragTrap  = 100
energy points จาก ScavTrap  = 50
attack damage จาก FragTrap  = 30
attack()      จาก ScavTrap
```

**ต้องตั้งใน body ของ `DiamondTrap` ctor** เพราะลำดับการรันคือ:
```
ClapTrap ctor  -> 10/10/0
ScavTrap ctor  -> 100/50/20
FragTrap ctor  -> 100/100/30      <-- เขียนทับ energy เป็น 100!
DiamondTrap    -> ต้องแก้กลับเป็น 100/50/30
```

### แก้ ambiguity ของ `attack()`

`ScavTrap` มี `attack()` ของตัวเอง / `FragTrap` ไม่มี (ใช้ของ `ClapTrap`)
→ `diamond.attack()` กำกวมว่าเอาตัวไหน = **compile error**

```cpp
class DiamondTrap : public ScavTrap, public FragTrap {
public:
    using ScavTrap::attack;   // บอกชัดๆ ว่าเอาของ ScavTrap (ตามที่โจทย์กำหนด)
};
```

ทางเลือกอื่น: เขียน `void attack(const std::string &t) { ScavTrap::attack(t); }`
— ได้ผลเหมือนกันแต่ยาวกว่า

### `_name` ที่ชื่อซ้ำกับแม่ (โจทย์บังคับ)

```cpp
class DiamondTrap : ... {
private:
    std::string _name;   // ชื่อเดียวกับ ClapTrap::_name เป๊ะ
};
```

ในโค้ดของ `DiamondTrap`:
```cpp
_name              // -> ของ DiamondTrap (ชื่อจริง)
ClapTrap::_name    // -> ของแม่ (ชื่อ + "_clap_name") ต้องระบุ scope
```

`whoAmI()` ต้องพิมพ์ทั้งสอง → เป็นการพิสูจน์ว่าคุณเข้าใจ shadowing

### `-Wshadow` ที่โจทย์ใบ้ไว้

โจทย์ถาม: *"Do you know the `-Wshadow` and `-Wno-shadow` compiler flags?"*

บน clang ต้องใช้ `-Wshadow-all` (หรือ `-Wshadow-field`) จะเห็น:
```bash
c++ -std=c++98 -Wshadow-all -c DiamondTrap.cpp -o /dev/null
```
```
warning: non-static data member '_name' of 'DiamondTrap' shadows member
         inherited from type 'ClapTrap' [-Wshadow-field]
```

`-Wshadow` เฉยๆ บน clang **ไม่จับ member shadowing** (จับแค่ local variable) —
บน g++ `-Wshadow` จับให้ ต่างกันตามคอมไพเลอร์

**อย่าใส่ flag เหล่านี้ใน Makefile ที่ส่ง** — โจทย์กำหนดแค่ `-Wall -Wextra -Werror`

---

## 6. สรุปว่า inheritance ช่วยอะไร (และไม่ช่วยอะไร)

`ScavTrap` กับ `FragTrap` ต่างกันแค่ **ค่า stat 3 ตัว + ข้อความ**
แต่ต้องเขียน ctor / copy ctor / `operator=` / dtor ซ้ำกันเกือบทั้งหมด

→ inheritance ลด code ซ้ำได้ระดับหนึ่ง (`takeDamage`, `beRepaired` เขียนครั้งเดียว)
แต่ **boilerplate ของ OCF ยังซ้ำอยู่** — นั่นเป็นข้อจำกัดจริงของ C++98
(module 07 template จะแก้ปัญหาอีกแบบหนึ่ง)

---

## รายละเอียดที่พลาดกันบ่อย: `unsigned int` underflow

```cpp
unsigned int _hitPoints;
_hitPoints -= amount;   // ⚠️ ถ้า amount > _hitPoints
```
```
3u - 10u  =  4294967289    ไม่ใช่ -7!
```
หุ่นที่ควรตาย กลับกลายเป็นมี hp มหาศาล → ต้อง clamp:
```cpp
if (amount >= _hitPoints)
    _hitPoints = 0;
else
    _hitPoints -= amount;
```
peer evaluator ชอบทดสอบ `takeDamage(999)` — เตรียมไว้

และ *"ClapTrap can't do anything if it has no hit points or energy points left"*
→ ต้องเช็ค **ทั้งสอง** เงื่อนไขใน `attack()` และ `beRepaired()`

---

## เช็คความเข้าใจ

1. ทำไม destructor ถูกเรียกกลับทางกับ constructor? (ตอบให้ได้เป็นเหตุผล ไม่ใช่แค่ "มันเป็นแบบนั้น")
2. `private` กับ `protected` ต่างกันตรงไหน และทำไม ex01 ต้องเปลี่ยน?
3. ถ้าลืมเขียน `: ClapTrap(name)` ใน `ScavTrap` ctor จะเกิดอะไร?
4. `ScavTrap s; ClapTrap &r = s; r.attack("x");` ได้ข้อความของใคร? เพราะอะไร?
5. Diamond problem คืออะไร และ `virtual public` แก้มันอย่างไร?
6. ใครเป็นผู้เรียก constructor ของ virtual base?
7. ทำไม `DiamondTrap` ต้องตั้ง `_energyPoints = 50` ใน body ไม่ใช่พึ่ง `ScavTrap` ctor?
8. `using ScavTrap::attack;` แก้ปัญหาอะไร?
9. `_hitPoints` เป็น `unsigned int` แล้ว `takeDamage(999)` ตอน hp เหลือ 3 — เกิดอะไรถ้าไม่ clamp?
