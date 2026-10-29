# BSQ

## Overview

`bsq` is a C program that finds the **biggest possible square of empty cells** in a map while avoiding obstacles.

```text
MAP
 ↓
VALIDATE
 ↓
FIND BIGGEST SQUARE
 ↓
REPLACE EMPTY CELLS WITH FULL CHAR
 ↓
PRINT RESULT
```

Program syntax:

```bash
./bsq map.txt
```

If no file is given:

```bash
./bsq
```

then the map must be read from `stdin`.

---

<details>
<summary><b>1. Map Header</b></summary>

The first line contains:

```text
number_of_lines empty obstacle full
```

Example:

```text
9 . o x
```

Means:

```text
9 → number of map rows
. → empty cell
o → obstacle
x → full / solution
```

Memory:

```text
LINES EMPTY OBSTACLE FULL
  9     .      o      x
```

</details>

---

<details>
<summary><b>2. Map</b></summary>

Example:

```text
...........................
....o......................
............o..............
...........................
....o......................
...............o...........
...........................
......o..............o.....
..o.......o................
```

Interpretation:

```text
. → empty
o → obstacle
```

Your program must find the largest square containing only:

```text
.
```

and replace those cells with:

```text
x
```

</details>

---

<details>
<summary><b>3. Goal</b></summary>

Find:

```text
BIGGEST SQUARE
```

that contains **no obstacles**.

Example:

```text
. . . . .
. o . . .
. . . . .
. . . . .
```

Possible square:

```text
. . .
. . .
. . .
```

After finding it:

```text
x x x
x x x
x x x
```

So:

```text
EMPTY AREA
    ↓
largest valid square
    ↓
FULL CHAR
```

</details>

---

<details>
<summary><b>4. Tie-Break Rule</b></summary>

If multiple squares have the same maximum size:

```text
choose TOP first
```

If they are on the same row:

```text
choose LEFT first
```

Memory:

```text
1. BIGGEST
2. TOPMOST
3. LEFTMOST
```

Example:

```text
AAA....BBB
AAA....BBB
AAA....BBB
```

Both are the same size.

Choose:

```text
AAA
```

because it is more to the **left**.

</details>

---

<details>
<summary><b>5. Valid Map</b></summary>

A map is valid only if:

```text
✓ correct header
✓ at least 1 row
✓ at least 1 column
✓ every row same width
✓ every row ends with '\n'
✓ only empty / obstacle characters are used
✓ empty, obstacle, full are all different
```

Otherwise:

```text
map error
```

must be printed to:

```c
stderr
```

Example:

```c
fprintf(stderr, "map error\n");
```

</details>

---

<details>
<summary><b>6. Invalid Map Examples</b></summary>

Different row lengths:

```text
.....
....
.....
```

❌ invalid

Unknown character:

```text
.....
..A..
.....
```

If `A` is not defined in the header:

```text
❌ invalid
```

Same characters:

```text
9 . . x
```

```text
empty    = .
obstacle = .
```

❌ invalid

Missing header character:

```text
9 . o
```

❌ invalid

</details>

---

<details>
<summary><b>7. Core Algorithm</b></summary>

The easiest common solution uses **dynamic programming**.

For each empty cell, calculate:

```text
largest square ending at this cell
```

Rule:

```text
if obstacle
    dp = 0

if empty
    dp = 1 + min(
        TOP,
        LEFT,
        TOP-LEFT
    )
```

Visual:

```text
TOP-LEFT   TOP
     ↖      ↑
       [ CELL ]
         ←
        LEFT
```

Core formula:

```c
dp[y][x] = 1 + min(
    dp[y - 1][x],
    dp[y][x - 1],
    dp[y - 1][x - 1]
);
```

</details>

---

<details>
<summary><b>8. Why min(top, left, diagonal)?</b></summary>

Imagine:

```text
? ? ?
? ? X
? X C
```

For `C` to complete a bigger square, all three surrounding areas must support it:

```text
↖ diagonal
↑ top
← left
```

Example:

```text
1 1 1
1 2 2
1 2 ?
```

At `?`:

```text
top      = 2
left     = 2
diagonal = 2
```

So:

```text
min = 2

2 + 1 = 3
```

Result:

```text
1 1 1
1 2 2
1 2 3
```

The `3` means:

```text
a 3 × 3 square ends here
```

</details>

---

<details>
<summary><b>9. Obstacle Rule</b></summary>

Obstacle:

```text
o
```

means:

```text
dp = 0
```

Example:

```text
MAP

. . .
. o .
. . .
```

DP:

```text
1 1 1
1 0 1
1 1 1
```

An obstacle breaks the square.

</details>

---

<details>
<summary><b>10. DP Example</b></summary>

Map:

```text
....
....
....
..o.
```

Start:

```text
. . . .
. . . .
. . . .
. . o .
```

DP becomes:

```text
1 1 1 1
1 2 2 2
1 2 3 3
1 2 0 1
```

Largest value:

```text
3
```

Therefore:

```text
largest square = 3 × 3
```

</details>

---

<details>
<summary><b>11. Store the Best Square</b></summary>

While filling the DP board, remember:

```c
best_size
best_x
best_y
```

Example:

```text
best_size = 7
best_x    = 11
best_y    = 6
```

Usually `best_x` and `best_y` represent the **bottom-right corner** of the square.

Then:

```text
top-left x = best_x - best_size + 1
top-left y = best_y - best_size + 1
```

Visual:

```text
top-left
   ↓
   x x x
   x x x
   x x X ← best_x,best_y
```

</details>

---

<details>
<summary><b>12. Fill the Solution</b></summary>

Once the best square is known:

```text
size = 3
bottom-right = (4, 5)
```

Calculate:

```text
start_x = 4 - 3 + 1 = 2
start_y = 5 - 3 + 1 = 3
```

Then replace:

```text
empty → full
```

Example:

```text
...
...
...
```

becomes:

```text
xxx
xxx
xxx
```

Using the map's own `full` character.

</details>

---

<details>
<summary><b>13. Multiple Files</b></summary>

The program may receive:

```bash
./bsq map1 map2 map3
```

Process each independently:

```text
map1
 ↓
solve
 ↓
print
 ↓
blank line

map2
 ↓
solve
 ↓
print
 ↓
blank line

map3
 ↓
solve
 ↓
print
```

If one is invalid:

```text
map error
```

then continue with the next map.

</details>

---

<details>
<summary><b>14. No Arguments</b></summary>

If:

```text
argc == 1
```

read from:

```c
stdin
```

Instead of:

```c
fopen(av[i], "r");
```

Mental model:

```text
FILE ARGUMENT?
   /      \
 YES       NO
 ↓          ↓
fopen      stdin
```

</details>

---

<details>
<summary><b>15. Useful Structures</b></summary>

A useful structure could store map information:

```c
typedef struct s_map
{
    int     rows;
    int     cols;
    char    empty;
    char    obstacle;
    char    full;
    char    **grid;
}   t_map;
```

And the solution:

```c
typedef struct s_square
{
    int size;
    int x;
    int y;
}   t_square;
```

Mental picture:

```text
t_map
│
├── rows
├── cols
├── empty
├── obstacle
├── full
└── grid


t_square
│
├── size
├── x
└── y
```

</details>

---

<details>
<summary><b>16. Suggested Functions</b></summary>

```text
read_map()
    ↓
read header + grid


validate_map()
    ↓
check map rules


solve_bsq()
    ↓
dynamic programming


fill_square()
    ↓
replace '.' with full char


print_map()
    ↓
output map


free_map()
    ↓
free memory
```

Possible layout:

```c
int     read_map(FILE *file, t_map *map);
int     validate_map(t_map *map);
void    solve_bsq(t_map *map);
void    fill_square(t_map *map, t_square best);
void    print_map(t_map *map);
void    free_map(t_map *map);
```

</details>

---

<details>
<summary><b>17. Program Flow</b></summary>

```text
main
 │
 ├── file argument?
 │
 ▼
open file / stdin
 │
 ▼
read header
 │
 ▼
read map
 │
 ▼
validate
 │
 ├── invalid
 │      ↓
 │   map error
 │
 └── valid
        ↓
     create DP
        ↓
     scan map
        ↓
     find biggest square
        ↓
     fill square
        ↓
     print map
        ↓
     free memory
```

</details>

---

<details>
<summary><b>18. DP Memory Map</b></summary>

```text
FOR EVERY CELL
      │
      ▼
 obstacle?
   /      \
 YES       NO
 ↓          ↓
dp = 0    first row/column?
             /      \
           YES       NO
            ↓         ↓
          dp=1      min(
                     top,
                     left,
                     diagonal
                    ) + 1
                      ↓
                 update best
```

</details>

---

<details>
<summary><b>19. Quick Memorization Sheet</b></summary>

```text
INPUT
-----
./bsq map.txt

or

./bsq < stdin


HEADER
------
rows empty obstacle full

9 . o x


MAP
---
. = empty
o = obstacle
x = full


GOAL
----
find largest square
without obstacles


TIE
---
biggest
↓
topmost
↓
leftmost


DP
--
obstacle → 0

first row / col
empty → 1

other empty:

1 + min(
    top,
    left,
    diagonal
)


STORE
-----
best_size
best_x
best_y


FINISH
------
find
↓
fill
↓
print
↓
free
```

</details>

---

<details>
<summary><b>20. 30-Second Recall</b></summary>

```text
READ HEADER

rows empty obstacle full
        ↓
READ MAP
        ↓
VALIDATE
        ↓
FOR EACH CELL
        ↓
obstacle?
  ↓
0

empty?
  ↓
1 + min(
    TOP,
    LEFT,
    DIAGONAL
)
        ↓
SAVE BIGGEST
        ↓
TOPMOST / LEFTMOST
        ↓
REPLACE AREA WITH FULL CHAR
        ↓
PRINT
```

### Mental Model

Split `bsq` into only **three problems**:

```text
PART 1: READ + VALIDATE

file
 ↓
header
 ↓
map
```

```text
PART 2: FIND SQUARE

for every cell
 ↓
top + left + diagonal
 ↓
largest size
```

```text
PART 3: DRAW RESULT

best position + size
 ↓
replace empty with full
 ↓
print
```

The most important formula to remember is:

```text
EMPTY CELL

        top
         ↓
diag → CELL ← left

CELL = min(top, left, diag) + 1
```

So the exam memory phrase is:

```text
READ
↓
VALIDATE
↓
MIN(TOP, LEFT, DIAGONAL) + 1
↓
SAVE BIGGEST
↓
FILL
↓
PRINT
```
