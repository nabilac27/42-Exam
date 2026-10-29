<center>
    <h1>Exam Rank 05</h1>
</center>

## Overview

| Level | Exercise | Main Concept |
|:---:|---|---|
| **1** | `bigint` | Class, operator overloading, big numbers |
| **1** | `vect2` | Class, operator overloading, 2D vector |
| **1** | `polyset` | Inheritance, polymorphism, set/bag |
| **2** | `life` | Game of Life, grid simulation |
| **2** | `bsq` | Parsing, dynamic programming |

---

## Folder Structure
```shell
    EXAM05
    │
    ├── LEVEL 1
    │   ├── bigint  → string + operators
    │   ├── vect2   → vector + operators
    │   └── polyset → inheritance + polymorphism
    │
    └── LEVEL 2
        ├── life    → grid + simulation
        └── bsq     → grid + dynamic programming
```


---

<details>
<summary><b>Level 1 — bigint</b></summary>

---
### Files

```text
    bigint.hpp
    bigint.cpp
```

### Goal

Create an arbitrary-precision **unsigned integer** using a string.

```text
    bigint(1337)
        ↓
    digits = "1337"
```

### Main Concepts

```text
    std::string
    constructors
    operator overloading
    addition
    comparison
    digit shifting
```

### Operations

```cpp
    a + b
    a += b

    ++a
    a++

    a < b
    a > b
    a <= b
    a >= b
    a == b
    a != b

    a << 2
    a >> 2
    a <<= 2
    a >>= 2
```

Example:

```text
    42   << 3   → 42000
    1337 >> 2   → 13
```

### Core Logic

```text
    digits → remove zeros
        → add right-to-left
        → carry
        → reverse result
```

</details>

---

<details>
<summary><b>Level 1 — vect2</b></summary>

---

### Files

```text
    vect2.hpp
    vect2.cpp
```

### Goal

Implement a simple **2D integer vector**.

```text
    vect2
    ├── x
    └── y
```

### Main Concepts

```text
    constructors
    operator overloading
    comparison
    arithmetic
    increment / decrement
    operator[]
    operator<<
```

Example:

```cpp
    vect2 v(2, 3);

    v[0];   // 2
    v[1];   // 3
```

Output:

```text
    {2, 3}
```

</details>

---

<details>
<summary><b>Level 1 — polyset</b></summary>

---

### Files to Implement

```text
    searchable_array_bag.hpp
    searchable_array_bag.cpp
    searchable_tree_bag.hpp
    searchable_tree_bag.cpp
    set.hpp
    set.cpp
```

### Goal

Use **inheritance and polymorphism** to create searchable bags and a set.

```text
    bag
    ├── array_bag
    │      └── searchable_array_bag
    │
    └── tree_bag
        └── searchable_tree_bag
```

`set` wraps a:

```text
    searchable_bag
        ↓
        set
```

A **bag** allows duplicates.

```text
    {1, 1, 2, 3}
```

A **set** does not.

```text
    {1, 2, 3}
```

### Main Concepts

```text
    inheritance
    abstract classes
    polymorphism
    wrapping / composition
```

</details>

---

<details>
<summary><b>Level 2 — life</b></summary>

---

### Goal

Implement **Conway's Game of Life**.

```text
    grid
    ↓
    check neighbors
    ↓
    apply rules
    ↓
    next generation
```

### Main Concepts

```text
    2D grid
    loops
    neighbor counting
    simulation
```

</details>

---

<details>
<summary><b>Level 2 — bsq</b></summary>

---

### Goal

Find the **biggest square** that can be placed on a map without touching obstacles.

```text
    map
    ↓
    parse input
    ↓
    dynamic programming
    ↓
    find largest square
    ↓
    draw result
```

### Main Concepts

```text
    file parsing
    2D grid
    dynamic programming
    error handling
```

</details>

---

