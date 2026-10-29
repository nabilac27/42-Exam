# vect2

## Overview

`vect2` is a simple C++ exercise about implementing a **2D vector class** and overloading operators.

The class stores two integers:

```text
(x, y)
```

Example:

```cpp
vect2 a(3, 5);
```

```text
a
↓
x = 3
y = 5
```

Internally:

```cpp
int value[2];
```

```text
value[0] → x
value[1] → y
```

The main goal is to make `vect2` behave naturally with operators such as:

```text
+  -  *
+= -= *=
++ --
== !=
[]
<<
```

---

### Core Idea

```text
vect2
│
├── stores x and y
│
├── arithmetic on both coordinates
│
├── access with []
│
├── compare vectors
│
└── print with <<
```

```text
(x, y) + (a, b)
        ↓
(x + a, y + b)
```

Most operators simply perform the **same operation on both coordinates**.

---

<details>
<summary><b>1. Data Member</b></summary>

---

The class stores two integers:

```cpp
int value[2];
```

Visual:

```text
value
┌──────────┬──────────┐
│ value[0] │ value[1] │
│    x     │    y     │
└──────────┴──────────┘
```

Memory:

```text
0 → x
1 → y
```

Example:

```cpp
vect2 a(10, 20);
```

```text
value[0] = 10
value[1] = 20
```

</details>

<details>
<summary><b>2. Constructors</b></summary>

---

### Default

```cpp
vect2();
```

Creates:

```text
(0, 0)
```

### Parameter

```cpp
vect2(int x, int y);
```

Example:

```cpp
vect2 a(3, 5);
```

```text
value[0] = 3
value[1] = 5
```

### Copy

```cpp
vect2(const vect2& other);
```

```text
other (3,5)
      ↓ copy
new   (3,5)
```

### Assignment

```cpp
vect2& operator=(const vect2& other);
```

```text
a = b
```

Copies both coordinates from `b` into `a`.

</details>

<details>
<summary><b>3. Index Operator []</b></summary>

---

Allows direct access to coordinates:

```cpp
a[0]
a[1]
```

```text
a[0] → x
a[1] → y
```

Functions:

```cpp
int& operator[](int i);

const int& operator[](int i) const;
```

Example:

```cpp
vect2 a(3, 5);

a[0] = 10;
```

Result:

```text
before → (3,5)

a[0] = 10

after  → (10,5)
```

</details>

<details>
<summary><b>4. Arithmetic Operators</b></summary>

---

### Addition

```cpp
vect2 operator+(const vect2& other) const;
```

```text
(2,3) + (5,7)

↓ coordinate by coordinate

(2+5, 3+7)

↓

(7,10)
```

### Subtraction

```cpp
vect2 operator-(const vect2& other) const;
```

```text
(8,6) - (3,2)

↓

(8-3, 6-2)

↓

(5,4)
```

### Scalar Multiplication

```cpp
vect2 operator*(int scalar) const;
```

```text
(2,3) * 4

↓

(2*4, 3*4)

↓

(8,12)
```

Memory:

```text
+ → both coordinates
- → both coordinates
* → both coordinates
```

</details>

<details>
<summary><b>5. Compound Assignment</b></summary>

---

Operators:

```text
+=
-=
*=
```

Example:

```cpp
a += b;
```

Means:

```text
a = a + b
```

Example:

```text
a = (2,3)
b = (5,7)

a += b

↓

a = (7,10)
```

The difference is that `+=`, `-=`, and `*=` modify the current object directly.

</details>

<details>
<summary><b>6. Unary Minus</b></summary>

---

```cpp
-a
```

Changes the sign of both coordinates:

```text
(3,-2)

↓

(-3,2)
```

Think:

```text
(x,y)

↓

(-x,-y)
```

</details>

<details>
<summary><b>7. Increment / Decrement</b></summary>

---

There are two versions:

```text
PREFIX             POSTFIX

++a                a++
--a                a--
```

### Prefix

```cpp
++a;
```

```text
modify first
     ↓
return modified object
```

Example:

```text
(2,3)

++a

↓

(3,4)
```

Usually returns a reference:

```cpp
vect2& operator++();
```

### Postfix

```cpp
a++;
```

```text
copy old value
      ↓
modify original
      ↓
return old copy
```

Example:

```text
a = (2,3)

old = a++

returned → (2,3)
a       → (3,4)
```

Postfix has the dummy `int`:

```cpp
vect2 operator++(int);
```

Memory:

```text
++a     → change → return NEW

a++     → save OLD → change → return OLD
```

Same idea for `--`.

</details>

<details>
<summary><b>8. Comparison</b></summary>

---

Operators:

```cpp
==
!=
```

Two vectors are equal only when **both coordinates are equal**.

```text
(3,5) == (3,5)

x equal ✅
y equal ✅

→ true
```

But:

```text
(3,5) == (3,7)

x equal ✅
y equal ❌

→ false
```

Core idea:

```text
x equal
AND
y equal
```

</details>

<details>
<summary><b>9. Output Operator</b></summary>

---

Allows:

```cpp
std::cout << a;
```

Function:

```cpp
std::ostream&
operator<<(std::ostream& os, const vect2& v);
```

Example:

```text
a = (3,5)
```

Output:

```text
{3,5}
```

Visual:

```text
vect2
  ↓
operator <<
  ↓
std::cout
  ↓
{3,5}
```

</details>

<details>
<summary><b>10. Class Layout</b></summary>

---

```text
vect2
│
├── int value[2]
│
├── Constructors
│   ├── vect2()
│   ├── vect2(x,y)
│   ├── copy
│   └── assignment
│
├── Access
│   └── []
│
├── Arithmetic
│   ├── +
│   ├── -
│   └── *
│
├── Compound
│   ├── +=
│   ├── -=
│   └── *=
│
├── Unary
│   └── -
│
├── Increment
│   ├── ++a
│   ├── --a
│   ├── a++
│   └── a--
│
├── Comparison
│   ├── ==
│   └── !=
│
└── Output
    └── <<
```

</details>

<details>
<summary><b>11. Operator Summary</b></summary>

---

```text
ACCESS
------
[]

ARITHMETIC
----------
+
-
*

COMPOUND
--------
+=
-=
*=

UNARY
-----
-

INCREMENT
---------
++
--
++(int)
--(int)

COMPARE
-------
==
!=

OUTPUT
------
<<
```

</details>

<details>
<summary><b>12. Program Flow</b></summary>

---

```text
Create vect2
     ↓
store x and y
     ↓
perform operator
     ↓
operate on both coordinates
     ↓
return / modify result
     ↓
print
```

Example:

```text
vect2 a(2,3)
vect2 b(5,7)

      ↓

a + b

      ↓

x: 2 + 5
y: 3 + 7

      ↓

(7,10)

      ↓

std::cout << result
```

</details>

<details>
<summary><b>13. Quick Memorization Sheet</b></summary>

---

```text
DATA
----
value[2]

0 = x
1 = y


CTOR
----
()
(x,y)
copy
=


ACCESS
------
[]


ARITHMETIC
----------
+
-
*


COMPOUND
--------
+=
-=
*=


UNARY
-----
-


INCREMENT
---------
++
--
++(int)
--(int)


COMPARE
-------
==
!=


OUTPUT
------
<<
```

</details>

<details>
<summary><b>14. 30-Second Recall</b></summary>

---

```text
vect2
  ↓
value[2]
  ↓
0=x  1=y
  ↓
constructors
  ↓
[]
  ↓
+ - *
  ↓
+= -= *=
  ↓
unary -
  ↓
++ --
postfix ++(int) --(int)
  ↓
== !=
  ↓
ostream <<
```

### Mental Model

Think:

```text
       vect2 = TWO NUMBERS

              (x,y)
                │
      ┌─────────┴─────────┐
      ↓                   ↓
      x                   y
```

Almost every operation acts on **both**:

```text
(x,y) + (a,b)
↓
(x+a, y+b)
```

```text
(x,y) - (a,b)
↓
(x-a, y-b)
```

```text
(x,y) * s
↓
(x*s, y*s)
```

```text
++(x,y)
↓
(x+1, y+1)
```

If you remember:

```text
"DO IT TO X AND Y"
```


</details>
