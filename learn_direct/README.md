# learn_direct — เฉลย + คำอธิบาย C++ Modules 00–04

โฟลเดอร์นี้คือ **reference implementation** ของทุก exercise ใน module 00–04
โดยแยกออกจาก `module_0/` … `module_4/` ที่ใช้ส่งจริง

ทุกไฟล์:
- คอมไพล์ผ่าน `c++ -Wall -Wextra -Werror -std=c++98` ไม่มี warning
- รันแล้ว output ตรงกับตัวอย่างใน subject PDF
- ตรวจด้วย `leaks` แล้ว 0 leaks
- มี comment ภาษาไทยอธิบาย **"ทำไมเขียนแบบนี้"** ไม่ใช่แค่ "โค้ดทำอะไร"

---

## ⚠️ อ่านก่อนใช้

subject PDF ของทุกโมดูลเขียนไว้ตรงๆ ในหัวข้อ *AI Instructions*:

> - You should not ask for direct answers to the AI.
> - **Bad practice:** I secretly use AI, copy some code that looks right. During peer
>   evaluation, I can't explain anything. I fail. During the exam — no AI — I'm stuck
>   again. I fail.

โฟลเดอร์นี้จะช่วยคุณได้จริง**เฉพาะ**ถ้าใช้แบบนี้:

### วิธีใช้ที่ได้ผล
1. อ่าน subject → **ลองเขียนเองก่อน** จนติด
2. เปิด `NOTES.md` ของโมดูลนั้นก่อน (ไม่ใช่เปิดโค้ด) — มันตอบ "แนวคิด" ไม่ใช่ "คำตอบ"
3. ถ้ายังไม่ออก เปิดโค้ดอ่าน **comment** ก่อนอ่าน implementation
4. **ปิดไฟล์** แล้วเขียนใหม่จากศูนย์ในโฟลเดอร์ `module_X/` ของตัวเอง
5. เช็คตัวเอง: ตอบคำถามท้าย `NOTES.md` ได้ไหมโดยไม่เปิดโค้ด?

### วิธีใช้ที่จะทำให้พัง
- `cp -r learn_direct/module_2/ex02 module_2/ex02` → peer eval ถามคำถามเดียวก็จบ
- ลอกไปแล้วไม่รู้ว่า `operator++(int)` ทำไมมี `int` เปล่าๆ อยู่ในวงเล็บ

**exam ไม่มี AI ไม่มีอินเทอร์เน็ต** — สิ่งเดียวที่ช่วยคุณได้คือความเข้าใจที่สร้างด้วยมือตัวเอง

---

## แผนที่เนื้อหา

| Module | หัวข้อ | สิ่งที่ต้องเข้าใจให้ได้ |
|---|---|---|
| [00](module_0/NOTES.md) | class, static, stdio stream, iomanip | class คืออะไร, `static` member แชร์กันได้อย่างไร, initialization list |
| [01](module_1/NOTES.md) | memory, reference, pointer to member | stack vs heap เลือกอย่างไร, reference ต่างจาก pointer ตรงไหน |
| [02](module_2/NOTES.md) | operator overloading, Orthodox Canonical Form | Rule of Three, ทำไม `operator<<` ต้องเป็น free function |
| [03](module_3/NOTES.md) | inheritance | ลำดับ ctor/dtor, protected, **diamond problem + virtual inheritance** |
| [04](module_4/NOTES.md) | polymorphism, abstract class, interface | **`virtual` ทำอะไร**, virtual destructor, deep vs shallow copy |

**ลำดับความสำคัญถ้าเวลาน้อย:** virtual (m04) > diamond (m03) > Rule of Three (m02) > stack/heap (m01)
สามอย่างแรกคือสิ่งที่ exam ถามและที่ interview งานถาม

---

## คอมไพล์และรัน

ทุก exercise มี `Makefile` ของตัวเอง:

```bash
cd learn_direct/module_2/ex02
make          # build
./fixed       # run
make fclean   # ล้าง
```

build ทั้งหมดทีเดียว:

```bash
cd learn_direct
for d in module_*/ex*; do make -C "$d" >/dev/null || echo "FAIL $d"; done
```

ตรวจ leak (macOS):

```bash
MallocStackLogging=1 leaks -atExit -- ./module_4/ex03/materia | grep "total leaked"
```

Linux ใช้ `valgrind --leak-check=full ./materia` แทน

---

## หมายเหตุเรื่องโค้ดของคุณเองใน `module_0/ex01`

โค้ด phonebook ที่มีอยู่มีจุดที่ต้องแก้ก่อนส่ง — ดูรายละเอียดใน
[`module_0/NOTES.md`](module_0/NOTES.md) หัวข้อ *"เทียบกับโค้ดที่คุณเขียนไว้"*
