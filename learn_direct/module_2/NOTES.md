# Module 02 — Operator overloading & Orthodox Canonical Form

## 1. Orthodox Canonical Form (OCF)

4 อย่างที่ class "ที่โตแล้ว" ต้องมีครบ:

```cpp
Fixed(void);                            // 1. default constructor
Fixed(const Fixed &other);              // 2. copy constructor
Fixed &operator=(const Fixed &other);   // 3. copy assignment operator
~Fixed(void);                           // 4. destructor
```

### ทำไมต้องครบ 4

ถ้าไม่เขียน compiler สร้างให้เอง แบบ **copy ทีละ member (shallow copy)**
สำหรับ `Fixed` ที่มีแค่ `int _value` — shallow copy ถูกต้องอยู่แล้ว ไม่มีปัญหา

**แต่ถ้า class มี pointer ที่เป็นเจ้าของ memory → shallow copy พังทันที**
(module 04 `Dog` ที่มี `Brain*` จะเจอเต็มๆ: double free)

### Rule of Three

> ถ้าต้องเขียน **destructor**, **copy constructor**, หรือ **copy assignment operator**
> อันใดอันหนึ่ง → แปลว่าต้องเขียนทั้งสามอัน

เพราะ "ต้องเขียน destructor" = "class นี้จัดการทรัพยากรอะไรบางอย่าง"
= "การ copy แบบ default ต้องผิดแน่ๆ"

### `operator=` เขียนถูกต้องอย่างไร

```cpp
Fixed &Fixed::operator=(const Fixed &other) {
    if (this != &other)          // 1. กัน self-assignment
        _value = other._value;   // 2. copy
    return (*this);              // 3. คืน *this เป็น reference
}
```

- **ข้อ 1** สำคัญมากเมื่อมี pointer: ไม่กัน → `delete` ของตัวเองแล้วไป copy จากที่ลบแล้ว
- **ข้อ 3** ทำให้ chain ได้ (`a = b = c`) เหมือน built-in type — คืน `void` ก็คอมไพล์ผ่าน
  แต่ผิดธรรมเนียมและใช้ในบางบริบทไม่ได้

### copy constructor vs copy assignment — ต่างกันตรงไหน

```cpp
Fixed b(a);   // copy constructor  -> b ยังไม่มีอยู่ ต้อง "สร้าง"
Fixed c;      // default constructor
c = b;        // copy assignment   -> c มีอยู่แล้ว ต้อง "เขียนทับ"
```
`Fixed b = a;` เรียก **copy constructor** ไม่ใช่ `operator=` (แม้จะมีเครื่องหมาย `=`)
นี่คือจุดที่สอบถามบ่อย

---

## 2. Fixed-point number คืออะไร

เก็บ `int` ตัวเดียว แต่ **ตีความว่า 8 bit ล่างคือส่วนทศนิยม**

```
raw 256  ->  256/256 = 1.0
raw 128  ->  128/256 = 0.5
raw 1    ->  1/256   = 0.00390625    <-- epsilon (ค่าที่เล็กสุดที่แทนได้)
```

| | fixed-point | float |
|---|---|---|
| ความละเอียด | **เท่ากันทุกช่วงค่า** (1/256 เสมอ) | ยิ่งเลขใหญ่ยิ่งหยาบ |
| ช่วงค่า | แคบ | กว้างมาก |
| ความเร็ว | integer arithmetic (เร็ว) | ต้องมี FPU |
| ใช้ที่ไหน | graphics, DSP, embedded | ทั่วไป |

### สูตรแปลงค่า (bits = 8, ตัวคูณ = 2⁸ = 256)

```cpp
int   -> fixed : raw = value << 8
float -> fixed : raw = roundf(value * 256)
fixed -> int   : value = raw >> 8
fixed -> float : value = raw / 256.0f
```

### ทำไมต้อง `roundf` ไม่ใช่ `(int)`

```
42.42 * 256 = 10859.52
  (int)  -> 10859  -> 10859/256 = 42.4180   ❌ subject บอกว่าต้องได้ 42.4219
  roundf -> 10860  -> 10860/256 = 42.421875 -> พิมพ์ 42.4219 ✅
```
`(int)` cast ตัดเศษเข้าหา 0 เสมอ — เสียความแม่นไปครึ่ง epsilon ทุกครั้ง

### `>>` กับเลขลบ

```
-1 >> 8  =  -1     (ปัดลงเข้าหา -infinity)
(int)(-0.5f) = 0   (ตัดเข้าหา 0)
```
`toInt()` ที่ใช้ `>>` จึงปัดลงเสมอ ไม่ใช่ปัดเข้าหา 0 — รู้ไว้เวลาเจอ edge case กับเลขลบ

---

## 3. `operator<<` — ทำไมต้องเป็น free function

```cpp
std::ostream &operator<<(std::ostream &os, const Fixed &f);   // ✅ free function
```

**เพราะ left operand คือ `std::ostream` ไม่ใช่ `Fixed`**

member function `a.operator<<(b)` = `a << b` → left operand ต้องเป็น class ที่เป็นเจ้าของ
ถ้าเขียน `operator<<` เป็น member ของ `Fixed` → ต้องเขียน `f << std::cout` ซึ่งกลับหัว

แล้วทำไมไม่ไปเขียนใน `std::ostream`? เพราะเราแก้ standard library ไม่ได้
→ **free function คือทางเดียว**

คืน `std::ostream &` เพื่อให้ chain: `cout << a << b << endl`

> ถ้า `operator<<` ต้องเข้าถึง private member → ต้องประกาศเป็น `friend`
> แต่ที่นี่เรียก `toFloat()` ที่เป็น public ได้ → ไม่ต้องใช้ `friend` เลย ซึ่งดีกว่า

### กฎทั่วไปของการเลือก member vs free

| operator | เขียนเป็น |
|---|---|
| `=`, `[]`, `()`, `->` | **ต้อง** เป็น member |
| `<<`, `>>` | free function (left operand เป็น stream) |
| `+`, `-`, `==`, `<` | member ก็ได้ / free ก็ได้ (free ยืดหยุ่นกว่าเรื่อง implicit conversion) |

---

## 4. Pre vs Post increment — ex02

```cpp
Fixed &operator++(void);   // ++a : เพิ่มก่อน คืน "ตัวเดิม"  -> reference
Fixed  operator++(int);    // a++ : คืน "ค่าเก่า"           -> by value
```

### `int` เปล่าๆ ในวงเล็บคืออะไร

**dummy parameter** — ไม่ได้ใช้เลย มีไว้ให้ compiler แยก pre กับ post ออกจากกัน
เพราะสองอันมีชื่อเดียวกัน (`operator++`) และรับ argument จำนวนเท่ากันในสายตาผู้ใช้

**ห้ามตั้งชื่อมัน** ไม่งั้น `-Wunused-parameter` + `-Werror` จะทำให้ build ตก
(หรือใส่ชื่อแล้ว `(void)name;` แต่ปล่อยไม่มีชื่อสะอาดกว่า)

### ทำไม post ต้องคืน by value

```cpp
Fixed Fixed::operator++(int) {
    Fixed before(*this);   // เก็บสำเนาค่าเก่า
    ++_value;              // เพิ่มค่าจริง
    return (before);       // คืนสำเนา
}
```
ค่าเก่าไม่มีอยู่ใน object แล้ว → ต้องมี copy → **คืน reference ไปที่ local variable ไม่ได้**
(จะเป็น dangling reference)

**นี่คือเหตุผลที่ `++i` เร็วกว่า `i++`** — post มี copy เพิ่ม 1 ครั้งเสมอ
ใน loop ที่ไม่ใช้ค่าเก่า ให้เขียน `++i` ติดเป็นนิสัย

### ทำไม pre คืน reference ได้

`++a` คืน `a` ตัวเดิมที่ยังมีชีวิตอยู่ → `return (*this)` ปลอดภัย และไม่ต้อง copy

---

## 5. `min` / `max` — overloading บน constness

```cpp
static Fixed       &min(Fixed &a, Fixed &b);
static const Fixed &min(const Fixed &a, const Fixed &b);
```

สองตัวนี้ **ไม่ใช่โค้ดซ้ำไร้ประโยชน์** — ต่างกันที่ constness ซึ่งนับเป็น overload คนละตัว

```cpp
Fixed a(1), b(2);
Fixed::max(a, b) = Fixed(99);   // ใช้เวอร์ชัน non-const -> แก้ผลลัพธ์ได้!

Fixed const x(1), y(2);
Fixed::max(x, y);               // ใช้เวอร์ชัน const
```
ถ้ามีแค่เวอร์ชัน non-const → `Fixed const` ส่งเข้าไม่ได้เลย (คอมไพล์ไม่ผ่าน)

---

## 6. Arithmetic operators — ตรงไหนทำ raw ได้ ตรงไหนไม่ได้

### `+` และ `-` — ทำที่ raw ได้ แม่นเป๊ะ

```
(a*256) + (b*256) = (a+b)*256    <-- scale ยังถูกอยู่
```
```cpp
Fixed Fixed::operator+(const Fixed &r) const {
    Fixed result;
    result.setRawBits(_value + r._value);   // ไม่เสียความแม่นเลย
    return (result);
}
```
**ห้ามเขียน `return Fixed(_value + r._value);`** เพราะ `Fixed(int)` จะ shift ซ้ำอีก 8 bit

### `*` และ `/` — scale เพี้ยน ต้องปรับ

```
(a*256) * (b*256) = a*b*256²     <-- เกินมา 1 เท่าของ 256 -> ต้อง >> 8
(a*256) / (b*256) = a/b          <-- หายไป 256 เท่า      -> ต้อง << 8
```

**ที่นี่เลือกทำผ่าน `toFloat()` แทน:**
```cpp
return (Fixed(toFloat() * r.toFloat()));
```

เหตุผล: `raw * raw` ล้น `int` ง่ายมาก
```
1000 * 1000  ->  256000 * 256000 = 6.5e10   >  2.1e9 (32-bit int max)  ❌ overflow
```
ทางแก้ที่ไม่เสียความแม่นคือใช้ `long long` เป็นตัวกลาง — **แต่ `long long` เป็น C++11**
→ ในข้อจำกัด C++98 การผ่าน float คือ trade-off ที่สมเหตุสมผล และให้ผลตรงกับ subject

ตรวจ: `Fixed(5.05f) * Fixed(2)` → `5.05078125 * 2 = 10.1015625` → พิมพ์ `10.1016` ✅

---

## 7. ex03 BSP — กับดัก `const` member

โจทย์บังคับให้ `Point` มี `Fixed const _x, _y` **และ** ต้องมี copy assignment operator

```cpp
Point &Point::operator=(const Point &other) {
    _x = other._x;   // ❌ คอมไพล์ไม่ผ่าน! _x เป็น const
}
```

`const` member ตั้งค่าได้ครั้งเดียวใน initialization list เท่านั้น

**ทางออก:** เขียน `operator=` ให้มีตามที่โจทย์ขอ แต่ไม่ทำอะไร
```cpp
Point &Point::operator=(const Point &other) {
    (void)other;      // กัน -Wunused-parameter
    return (*this);
}
```
`Point` เป็น immutable value type ตามดีไซน์ที่โจทย์กำหนด — assign ทับไม่ได้ **ตั้งใจแล้ว**
(ถ้าจะให้ assign ได้จริง ต้องเอา `const` ออก ซึ่งขัดโจทย์)

### อัลกอริทึม: cross product 2D

```
cross(A, B, P) = (Bx-Ax)*(Py-Ay) - (By-Ay)*(Px-Ax)
```

เครื่องหมายบอกว่า **P อยู่ข้างไหนของเส้น AB**:
```
> 0  ->  ซ้ายมือ
< 0  ->  ขวามือ
= 0  ->  อยู่บนเส้นพอดี
```

**P อยู่ในสามเหลี่ยม ⟺ P อยู่ข้างเดียวกันของทั้งสามด้าน**

```cpp
Fixed d1 = cross(a, b, point);
Fixed d2 = cross(b, c, point);
Fixed d3 = cross(c, a, point);

if (d1 == 0 || d2 == 0 || d3 == 0)
    return (false);                    // บนขอบ/จุดยอด -> โจทย์บอกว่า false

return ((d1<0 && d2<0 && d3<0) || (d1>0 && d2>0 && d3>0));
```

**ทำไมต้องเช็คทั้งบวกหมดและลบหมด?** เพราะเครื่องหมายขึ้นกับว่า A,B,C เรียง
ตามเข็มหรือทวนเข็ม — ฟังก์ชันต้องทำงานได้ทั้งสองแบบ (มี test case ใน `main.cpp`)

**ข้อควรระวังเรื่องความแม่น:** เพราะ `*` ผ่าน float การเช็ค `== 0` อาจพลาดในเคสที่
พิกัดเป็นทศนิยมแปลกๆ — ในทางปฏิบัติควรใช้พิกัดที่หารด้วย 1/256 ลงตัว
ถ้าต้องแม่นจริงๆ ให้ทำ `*` ด้วย integer arithmetic + ตัวกลางที่กว้างพอ

---

## เช็คความเข้าใจ

1. Orthodox Canonical Form มีอะไร 4 อย่าง และทำไมต้องครบ?
2. `Fixed b = a;` เรียก copy constructor หรือ `operator=`?
3. ทำไม `operator<<` เป็น member ของ `Fixed` ไม่ได้?
4. `int` เปล่าๆ ใน `operator++(int)` มีหน้าที่อะไร? ตั้งชื่อมันได้ไหม?
5. `++a` กับ `a++` อันไหนคืน reference อันไหนคืน by value และเพราะอะไร?
6. `operator+` ทำที่ raw ได้ แต่ `operator*` ทำไม่ได้ — ทำไม?
7. `Fixed const _x;` ทำให้ `operator=` เขียนแบบปกติไม่ได้ — ทางออกคืออะไร?
8. ถ้าใช้ `(int)` แทน `roundf` ใน float constructor ค่าจะเพี้ยนไปเท่าไร?
9. `min`/`max` มีสองเวอร์ชัน (const / non-const) — ถ้าตัดเวอร์ชัน const ออกจะพังตอนไหน?
