# Polyset

## Overview

**Polyset** is an exercise about:
- Extending existing container classes using **inheritance**
- Adding search functionality through **polymorphism**
- Building a **`set`** that prevents duplicate values 
- The **`set`** is either an **array** or a **binary search tree** as the underlying data structure.


The project works with two container concepts:
- **`Bag`**: stores elements and **allows duplicates**.
- **`Set`**: stores only unique elements, allows **no duplicates**.


The exercise has two main parts:
* **Part I**
    
    `Searchable Bags`: Extend the provided `array_bag` and `tree_bag` classes with a `has()` function to search for values.
* **Part II**
    
    `Set`: Wrap a `searchable_bag` and prevent duplicate values from being inserted.

---

### Files

```cpp
    PROVIDED                    NEED TO BE IMPLEMENTED
    ────────────────────        ─────────────────────────
    main.cpp

    bag.hpp                     set.hpp, *.cpp
    searchable_bag.hpp          
    array_bag.hpp, *.cpp        searchable_array_bag.hpp, *.cpp  
    tree_bag.hpp, *.cpp         searchable_tree_bag.hpp, *.cpp                    

    subject.txt                 
    sets_and_bags.txt           
```

### Class Architecture
```shell
                    +---------+
                    |   bag   |
                    +---------+
                         ▲
                         │
             +-----------+-----------------------------------------+
             │                       │                             │
             │                       │                             │
      +-------------+         +-------------+       +-----------------------------+                     +-------------+
      |  array_bag  |         |  tree_bag   |       | searchable_bag              |                     |     set     |
      +-------------+         +-------------+       | abstract searching ability  | ──────> wrapped by  +-------------+
             ▲                       ▲              +-----------------------------+                     | searchable  |
             │                       │                              ▲                                   | bag inside  |
             │                       │                              │                                   +-------------+
             │                       │                              │                                   
             │-----------------------|------------------------------│
                     │               │                              │
                     │               │                              │
                     |               |------------------------------|
                     │                               │
+-------------------------------+   +-------------------------------+
| searchable_array_bag          |   | searchable_tree_bag           |
+-------------------------------+   +-------------------------------+
| inherits from array_bag       |   | inherits from tree_bag        |
| inherits from, searchable_bag |   | inherits from searchable_bag  |
+-------------------------------+   +-------------------------------+
```

### Core Idea
```shell
    searchable_array_bag = inherited from array_bag + searchable_bag
    searchable_tree_bag  = inherited from tree_bag  + searchable_bag
    set                  = wrap searchable_bag, no duplicates
```


```cpp
        array_bag ──→ searchable_array_bag ─┐
                                            ├──→ searchable_bag ──→ set
        tree_bag  ──→ searchable_tree_bag ──┘
```
---

<details>
<summary><b>1. Set vs. Bag</b></summary>

---

-  Memory: 
    - Bag = duplicates
    - Set = no duplicates

    ```shell
        BAG                         SET
        duplicates allowed          unique values only

        { 2, 5, 5, 8 } ✅            { 2, 5, 8 } ❌ 5 again
    ````

</details>

<details>
<summary><b>2. Array vs. Binary Search Tree</b></summary>

---

- Both store values, but differently.

- ARRAY
    ```shell
    [ 5 ][ 2 ][ 8 ][ 7 ]

    Search:
    5 → 2 → 8 → 7

    Array search checks elements one by one.
    ```

- BINARY SEARCH TREE
    ```shell

          5
         / \
        2   8
           /
          7

    smaller ← node → bigger

    Tree search:
        value smaller → LEFT
        value bigger  → RIGHT
        value equal   → FOUND
    ```
---

</details>

<details>
<summary><b>3. Existing Files</b></summary>

---

- Already provided:

    ```shell
    bag
        ├── array_bag
        └── tree_bag

        searchable_bag
        └── defines has()
    ```

- Need to be implemented:

    ```shell
        searchable_array_bag
        searchable_tree_bag
        set
    ```
---

</details>

<details>
<summary><b>4. Searchable Bags</b></summary>

---

- We combine storage + searching:

    ```shell
        array_bag + searchable_bag
                ↓
        searchable_array_bag
    ````

    ```shell
        tree_bag + searchable_bag
                ↓
        searchable_tree_bag
    ````

- Main new function:

    ```shell
        bool has(int value) const;
    ````

- Example:

    ```shell
        [ 3 ][ 7 ][ 10 ]

        has(7)  → true
        has(20) → false
    ```
</details>

<details>
<summary><b>5. Set</b></summary>

---

- A `set` uses a `searchable bag` but blocks duplicates.

    ```shell
        insert(5)
        ↓
        has(5)?
        /    \
        NO    YES
        ↓       ↓
        insert  ignore
    ```

- Core logic:

    ```cpp
        if (!bag.has(value))
            bag.insert(value);
    ```

- Example:

    ```shell
        insert: 5 2 5 8 2

        Bag → { 5, 2, 5, 8, 2 }

        Set → { 5, 2, 8 }
    ```
---

</details>

<details>
<summary><b>6. Inheritance vs. Wrapping</b></summary>

---

- **Inheritance** = IS-A

- `searchable_array_bag` IS AN `array_bag`

    ```cpp
        class searchable_array_bag : public array_bag
    ```

- **Wrapping** = HAS-A / USES-A
- `set` USES `searchable_bag``

    ```cpp
        searchable_bag& bag;
    ```

</details>

<details>
<summary><b>7. Summary</b></summary>

---

```shell
              bag
            /     \
     array_bag   tree_bag
         ↓          ↓
 searchable_    searchable_
 array_bag      tree_bag
         \          /
          \        /
        searchable_bag -> set
                            checks has()
                            before insert()
````

```shell
    bag
    → stores values
    → duplicates allowed

    searchable_bag
    → adds has()

    searchable_array_bag
    → array_bag + searchable_bag
    → linear search

    searchable_tree_bag
    → tree_bag + searchable_bag
    → tree search

    set
    → wraps searchable_bag
    → checks has()
    → prevents duplicates
```
</details>

<details>
<summary><b>8. Output Example</b></summary>

---

- Command

    ```cpp
        ./polyset 5 2 8 5
    ```

- Output

    ```cpp
    print tree: 2 5 5 8
    print array: 5 2 8 5

    tree value to find: 5
    return from function: 1

    array value to find: 5
    return from function: 1

    [set] before inserting duplicates:
    5 2 8

    [set] after attempting to insert duplicate:
    5 2 8

    set has value 8? 1
    ````

</details>

