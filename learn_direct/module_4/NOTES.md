# Module 04 — Subtype polymorphism, abstract classes, interfaces

โมดูลนี้สำคัญที่สุดใน 5 โมดูลแรก — `virtual` คือแนวคิดที่ทำให้ OOP มีประโยชน์จริง

---

## 1. ⭐ `virtual` ทำอะไร

**`virtual` ทำให้ C++ เลือกฟังก์ชันตาม "ชนิดจริงของ object ตอน runtime"
ไม่ใช่ตาม "ชนิดของ pointer/reference ตอน compile"**

| | ไม่มี `virtual` | มี `virtual` |
|---|---|---|
| ชื่อ | static binding / early binding | **dynamic dispatch** / late binding |
| ตัดสินใจเมื่อ | compile time | runtime |
| ดูจาก | type ของตัวแปร | type จริงของ object |

```cpp
Animal *a = new Dog();
a->makeSound();
// virtual     -> "Woof! Woof!"      (ของ Dog)   ✅
// ไม่ virtual -> "* animal noises *" (ของ Animal) ❌
```

### กลไกข้างใน (ตอบได้จะได้แต้ม)

compiler สร้าง **vtable** (ตารางที่อยู่ของฟังก์ชัน) ให้ทุก class ที่มี virtual function
และฝัง **vptr** (pointer ไป vtable) ไว้ในทุก object

เรียก `a->makeSound()` → ตามหา vptr → เปิด vtable → กระโดดไปฟังก์ชันจริง
→ ค่าใช้จ่าย: pointer indirection 1 ครั้ง + object ใหญ่ขึ้น 8 byte

### ex00 ออกแบบมาให้เห็นความต่างชัดๆ

| class | `makeSound` เป็น virtual? | ผลลัพธ์ผ่าน pointer ของ base |
|---|---|---|
| `Animal` / `Dog` / `Cat` | ✅ | ได้เสียงของ Dog/Cat **ถูกต้อง** |
| `WrongAnimal` / `WrongCat` | ❌ | ได้เสียงของ WrongAnimal **ผิด** |

`WrongCat` คือ "ตัวควบคุมการทดลอง" — มันมีอยู่เพื่อพิสูจน์ว่า `virtual` จำเป็นจริงๆ

```bash
./ex00/polymorphism    # ดูสองส่วนเทียบกัน
```

สังเกตว่า `w->getType()` ยังได้ `"WrongCat"` ถูกต้อง เพราะ `_type` เป็น **data** ที่ถูกตั้ง
โดย `WrongCat` ctor — ปัญหาอยู่ที่การเลือก **ฟังก์ชัน** เท่านั้น

---

## 2. ⭐⭐ Virtual destructor — จุดที่พลาดแล้ว leak

```cpp
Animal *a = new Dog();
delete a;
```

| `~Animal` | สิ่งที่ถูกเรียก | ผล |
|---|---|---|
| **ไม่** virtual | `~Animal` เท่านั้น | `Brain*` ของ Dog **leak** (แถมเป็น undefined behavior) |
| virtual | `~Dog` → `~Animal` | ปลอดภัย ✅ |

### กฎที่ต้องท่อง

> **ถ้า class มี virtual function ตัวใดตัวหนึ่ง → destructor ต้องเป็น virtual**

พูดอีกแบบ: ถ้าคุณตั้งใจให้คนอื่นสืบทอด class ของคุณ → `virtual ~Class();`

`ex01` ทดสอบจุดนี้ตรงๆ ตามที่โจทย์เขียน:
```cpp
const Animal *j = new Dog();
delete j;   // should not create a leak
```

ตรวจได้จริง:
```bash
MallocStackLogging=1 leaks -atExit -- ./ex01/brain | grep "total leaked"
# 0 leaks for 0 total leaked bytes
```

---

## 3. ⭐ Deep copy vs Shallow copy — `Brain*` (ex01)

`Dog` มี `Brain *_brain;` → **นี่คือจุดที่ Rule of Three (module 02) มีความหมายจริง**

### ถ้าปล่อยให้ compiler สร้าง copy constructor ให้เอง

```cpp
Dog::Dog(const Dog &o) : _brain(o._brain) { }   // shallow -- สิ่งที่ compiler ทำ
```
→ สอง `Dog` ชี้ `Brain` ก้อนเดียวกัน:

1. แก้ idea ของ `dog1` → `dog2` เปลี่ยนตามด้วย (ไม่ควรเป็นแบบนั้น)
2. `dog1` ตาย `delete _brain` → `dog2` ตาย `delete` ก้อนเดิม**อีกรอบ**
   = **DOUBLE FREE** → crash

### Deep copy ที่ถูกต้อง

```cpp
Dog::Dog(const Dog &o) : Animal(o), _brain(new Brain(*o._brain)) { }
//                                          ^^^^^^^^^^^^^^^^^^^^ ก้อนใหม่ + copy เนื้อหา
```

`operator=` ต่างกันเล็กน้อย เพราะ `_brain` **มีอยู่แล้ว**:
```cpp
Dog &Dog::operator=(const Dog &o) {
    if (this != &o) {                 // 1. กัน self-assignment (สำคัญมาก!)
        Animal::operator=(o);         // 2. copy ส่วนของแม่
        *_brain = *o._brain;          // 3. copy "เนื้อหา" ไม่ต้อง new ใหม่
    }
    return (*this);
}
```

**ทำไมต้องกัน self-assignment?** ถ้าเวอร์ชันที่ `delete _brain; _brain = new Brain(...)`
แล้วเจอ `d = d` → `delete` ของตัวเองแล้วไป copy จากที่ลบไปแล้ว = อ่านหน่วยความจำที่ตายแล้ว

### พิสูจน์ว่า deep จริง

```cpp
std::cout << original.getBrain() << " vs " << clone.getBrain();   // address ต่างกัน
clone.getBrain()->setIdea(0, "sleep");                            // แก้ clone
original.getBrain()->getIdea(0);                                  // original ไม่เปลี่ยน
```
`ex01/main.cpp` ทำ 3 การทดสอบนี้ให้แล้ว — **peer evaluator จะขอดูจุดนี้แน่นอน**
เพราะโจทย์เขียนว่า *"you have to test that your copies are deep copies!"*

---

## 4. Abstract class (ex02)

```cpp
virtual void makeSound(void) const = 0;   // pure virtual
//                                  ^^^ pure specifier
```

class ที่มี pure virtual แม้แต่ตัวเดียว → **abstract** → instantiate ไม่ได้

```cpp
AAnimal a;               // ❌ error: variable type 'AAnimal' is an abstract class
new AAnimal();           // ❌ error: allocating an object of abstract class type
AAnimal *p = new Dog();  // ✅ ใช้เป็น pointer/reference ได้ตามปกติ
```

**นี่คือทั้งหมดที่ ex02 ต้องการ:** *"Creating Animal objects doesn't make sense...
Fix the Animal class so that nobody can instantiate it."*

compiler บังคับให้เราถูกต้องตั้งแต่ **compile time** ดีกว่ามาพังตอน runtime

### สิ่งที่ abstract class **ยัง** ทำได้

- มี constructor (ถูกเรียกตอนสร้างคลาสลูก เพื่อ init ส่วนของแม่)
- มี data member (`_type`)
- มี non-pure virtual function ที่มี body
- **destructor ต้องมี body และต้อง virtual** (dtor ของแม่ถูกเรียกเสมอ)

### คลาสลูกที่ไม่ implement pure virtual → ก็ยัง abstract ต่อ

pure virtual ส่งต่อลงไปเรื่อยๆ จนกว่าจะมีใคร implement

### Abstract class vs Interface

| | abstract class | interface |
|---|---|---|
| pure virtual | ≥ 1 ตัว | **ทุกตัว** |
| data member | มีได้ | ไม่มี |
| ตัวอย่างในโมดูลนี้ | `AAnimal`, `AMateria` | `ICharacter`, `IMateriaSource` |

C++98 **ไม่มี keyword `interface`** — ใช้ pure abstract class แทน
(subject บอกไว้: *"Interfaces don't exist in C++98 (not even in C++20). However,
pure abstract classes are commonly called interfaces."*)

ธรรมเนียมตั้งชื่อ: `A` prefix = abstract, `I` prefix = interface

---

## 5. ex03 — Materia system (ข้อที่ยากที่สุดของโมดูล)

### 5.1 `clone()` = Prototype pattern

```cpp
virtual AMateria *clone(void) const = 0;
```
```cpp
AMateria *Ice::clone(void) const { return (new Ice(*this)); }
```

**ทำให้เราสร้าง "ของชนิดเดียวกับตัวเอง" ได้โดยไม่ต้องรู้ว่ามันชนิดอะไร**

```cpp
AMateria *copy = unknown->clone();   // ได้ Ice ถ้า unknown เป็น Ice
```

ถ้าไม่มี `clone()` `MateriaSource` ต้องเขียน:
```cpp
if (type == "ice") return new Ice();
else if (type == "cure") return new Cure();
// ...เพิ่มชนิดใหม่ = ต้องกลับมาแก้ที่นี่ทุกครั้ง
```
→ โจทย์บอก *"Your character's inventory will be able to support **any type** of AMateria"*
`clone()` คือสิ่งที่ทำให้ข้อนั้นเป็นจริง

### 5.2 กับดัก: `operator=` ห้าม copy `_type`

โจทย์เตือนไว้ในกรอบ: *"While assigning a Materia to another, copying the type
doesn't make sense."*

```cpp
AMateria &AMateria::operator=(AMateria const &other) {
    (void)other;      // ตั้งใจไม่ copy _type
    return (*this);
}
```

**เพราะ `_type` คือ "ตัวตน" ของ materia** — `Ice` จะกลายเป็น `Cure` ไม่ได้
(ถ้ามี attribute อื่นเช่น `_xp` ค่อย copy อันนั้น)

แต่ **copy constructor ต้อง copy `_type`** เพราะกำลังสร้างตัวใหม่ชนิดเดียวกัน

### 5.3 ⭐ Ownership — ใครเป็นเจ้าของ materia

นี่คือหัวใจของ ex03 และเป็นที่มาของ leak ทั้งหมด

```
equip(m)    -> Character รับ ownership เข้ามา
unequip(i)  -> ปล่อย ownership โดย *ห้าม delete*  (โจทย์สั่งชัดเจน)
~Character  -> delete ทุกช่องที่ยังมีของ
```

**โจทย์:** *"The `unequip()` member function must NOT delete the Materia!
Handle the Materias your character leaves on the floor as you like."*
พร้อมเตือน: *"don't forget that you have to avoid memory leaks"*

→ ต้องไม่ delete **แต่ก็ต้องไม่ leak** — ดูขัดกัน แต่ไม่ใช่

**วิธีที่ใช้ในโค้ดนี้:** เก็บของที่ unequip ไว้ใน `_floor[]` ("พื้น") แล้ว delete ตอน dtor
→ `unequip` ไม่ delete ✅ และไม่ leak ✅

วิธีอื่นที่ยอมรับได้: คืน pointer ให้ผู้เรียกจัดการเอง / เก็บใน static pool

### 5.4 3 จุดที่ต้อง delete ให้ครบ

| สถานการณ์ | ที่ต้องจัดการ |
|---|---|
| `equip` ตอน inventory เต็ม | `m` ที่ส่งมาหลุดมือ → เก็บลงพื้น (ไม่ใช่ปล่อยทิ้ง) |
| `learnMateria` ตอนเรียนครบ 4 | `delete m` ทันที |
| `operator=` ของ Character | **ลบของเก่าก่อน** clone ของใหม่ |

จุดที่ 3 โจทย์สั่งลำดับไว้ตรงๆ: *"During copy, the Materias of a Character must be
deleted **before** the new ones are added to their inventory."*
สลับลำดับ → ของเก่า leak

### 5.5 Forward declaration แก้ circular include

```cpp
// ICharacter.hpp
class AMateria;      // ไม่ใช่ #include "AMateria.hpp"
class ICharacter {
    virtual void equip(AMateria *m) = 0;
};
```

`AMateria.hpp` ต้องใช้ `ICharacter` (ใน `use(ICharacter&)`)
`ICharacter.hpp` ต้องใช้ `AMateria` (ใน `equip(AMateria*)`)
→ include ไปกลับ = **circular dependency**

**forward declaration** บอก compiler แค่ว่า "มี class ชื่อนี้อยู่" — พอสำหรับ
pointer/reference (เพราะขนาดของ pointer เท่ากันหมด ไม่ต้องรู้เนื้อข้างใน)
ไม่พอถ้าจะเรียก method หรือใช้เป็น member แบบ by value

### 5.6 `learnMateria` — ownership ที่โจทย์เขียนกำกวม

โจทย์บอก *"**Copies** the Materia passed as a parameter and stores it"*
แต่ main ตัวอย่างเขียน `src->learnMateria(new Ice());` โดยไม่ delete อะไรเลย

→ ถ้าเก็บ `m->clone()` ตามตัวอักษร → `m` ที่รับมา (`new Ice()`) **leak**
→ โค้ดนี้เลือก **รับ ownership ของ `m` ไปตรงๆ** แล้ว delete ใน dtor = ไม่ leak

นี่คือการตัดสินใจที่ต้องอธิบายได้ตอน peer eval — ทั้งสองแบบมีเหตุผล
แต่แบบที่เลือกทำให้ main ตัวอย่างของโจทย์ไม่ leak

---

## 6. เช็ค leak จริงๆ

```bash
cd learn_direct/module_4
MallocStackLogging=1 leaks -atExit -- ./ex03/materia | grep "total leaked"
```
Linux: `valgrind --leak-check=full ./materia`

**ทุก binary ในโฟลเดอร์นี้ผ่าน 0 leaks** — ทดสอบเองได้:
```bash
cd learn_direct
for b in module_1/ex00/zombie module_1/ex01/horde module_3/ex03/diamondtrap \
         module_4/ex00/polymorphism module_4/ex01/brain module_4/ex02/abstract \
         module_4/ex03/materia; do
    echo -n "$b: "
    MallocStackLogging=1 leaks -atExit -- "$b" 2>/dev/null | grep "total leaked"
done
```

---

## 7. เกร็ด: `-Wself-assign-overloaded`

ทดสอบ self-assignment แบบนี้ **คอมไพล์ไม่ผ่าน** ด้วย `-Werror`:
```cpp
assigned = assigned;   // error: explicitly assigning value of variable to itself
```
→ ต้องผ่าน reference:
```cpp
Dog &selfRef = assigned;
assigned = selfRef;
```
จุดที่ทดสอบยังเหมือนเดิม (`if (this != &other)` ทำงานไหม) แต่ compiler ไม่ฟ้อง

---

## เช็คความเข้าใจ

1. `virtual` ทำอะไร — อธิบายด้วยคำว่า "compile time" กับ "runtime"
2. `WrongCat` มีอยู่ในโจทย์เพื่ออะไร?
3. `Animal *a = new Dog(); delete a;` ถ้า `~Animal` ไม่ virtual จะเกิดอะไร?
4. กฎเรื่อง virtual destructor ท่องว่าอย่างไร?
5. shallow copy ของ `Dog` ที่มี `Brain*` พังได้ 2 แบบ — บอกทั้งสองแบบ
6. `operator=` ของ `Dog` ทำไมต้องมี `if (this != &other)`?
7. abstract class ต่างจาก interface ตรงไหน? C++98 มี keyword `interface` ไหม?
8. `clone()` แก้ปัญหาอะไร — ถ้าไม่มีมันโค้ด `MateriaSource` จะเป็นอย่างไร?
9. `AMateria::operator=` ทำไมห้าม copy `_type` แต่ copy constructor ต้อง copy?
10. `unequip()` ห้าม delete แต่ห้าม leak — คุณแก้อย่างไร?
11. forward declaration (`class AMateria;`) จำเป็นเพราะอะไร?
12. `MateriaSource::createMateria("fire")` ต้องคืนอะไร เมื่อไม่เคยเรียน fire?
