# life 

## Overview

`life` is a C program that:

* Creates a board
* Draws the starting pattern from `stdin`
* Simulates Conway's **Game of Life**
* Prints the final board

```text
INPUT COMMANDS
      ↓
DRAW BOARD
      ↓
GAME OF LIFE
      ↓
ITERATIONS
      ↓
PRINT RESULT
```

Program syntax:

```bash
./life width height iterations
```

Example:

```bash
echo 'dxss' | ./life 3 3 1
```

---

<details>
<summary><b>1. Arguments</b></summary>

```c
int main(int ac, char **av)
```

```text
./life 3 3 2
       │ │ │
       │ │ └── iterations = 2
       │ └──── height = 3
       └────── width = 3
```

```c
int width = atoi(av[1]);
int height = atoi(av[2]);
int iterations = atoi(av[3]);
```

Remember:

```text
av[1] → WIDTH
av[2] → HEIGHT
av[3] → ITERATIONS
```

</details>

---

<details>
<summary><b>2. Board</b></summary>

The board is:

```c
int **board;
```

Created with:

```c
int **create_board(int w, int h);
```

Visual:

```text
height = 3
width  = 4

        x →
      0 1 2 3
    ┌─────────
y 0 │ 0 0 0 0
↓ 1 │ 0 0 0 0
  2 │ 0 0 0 0
```

Access:

```c
board[y][x]
```

Remember:

```text
FIRST  = y
SECOND = x

board[y][x]
```

`calloc()` initializes everything to `0`.

```text
0 → dead
1 → alive
```

</details>

---

<details>
<summary><b>3. Pen Commands</b></summary>

The pen starts at:

```text
(0,0)
```

Commands:

```text
        w
        ↑
    a ← P → d
        ↓
        s
```

```text
w → up
a → left
s → down
d → right
x → drawing ON / OFF
```

`x` is a toggle:

```c
if (c == 'x')
    draw = !draw;
```

Visual:

```text
draw = 0
   ↓ x
draw = 1
   ↓ x
draw = 0
```

</details>

---

<details>
<summary><b>4. Drawing</b></summary>

When drawing is ON:

```c
if (draw)
    b[y][x] = 1;
```

Example:

```text
commands:

d x s s
```

```text
start

P . .
. . .
. . .
```

After `d`:

```text
. P .
. . .
. . .
```

After `x`:

```text
drawing ON
```

After `s s`:

```text
. 0 .
. 0 .
. 0 .
```

Output:

```text
 0 
 0 
 0 
```

</details>

---

<details>
<summary><b>5. Board Boundaries</b></summary>

The pen cannot move outside the board.

```c
c == 'w' && y > 0
```

```c
c == 's' && y < h - 1
```

```c
c == 'a' && x > 0
```

```c
c == 'd' && x < w - 1
```

Visual:

```text
┌─────────────┐
│             │
│      P →    │
│             │
└─────────────┘
       ↑
cannot leave board
```

If movement would leave the board:

```text
pen stays still
```

</details>

---

<details>
<summary><b>6. Game of Life</b></summary>

Each cell checks its **8 neighbors**:

```text
┌───┬───┬───┐
│ 1 │ 2 │ 3 │
├───┼───┼───┤
│ 4 │ X │ 5 │
├───┼───┼───┤
│ 6 │ 7 │ 8 │
└───┴───┴───┘
```

`X` is the current cell.

Function:

```c
count_neighbors(b, w, h, x, y);
```

</details>

---

<details>
<summary><b>7. Neighbor Loop</b></summary>

```c
for (int i = -1; i <= 1; i++)
{
    for (int j = -1; j <= 1; j++)
```

Offsets:

```text
(-1,-1) (-1,0) (-1,+1)

( 0,-1)    X    ( 0,+1)

(+1,-1) (+1,0) (+1,+1)
```

Where:

```text
i → y offset
j → x offset
```

Skip the center:

```c
if (i || j)
```

Because:

```text
i = 0
j = 0
↓
current cell
↓
DO NOT COUNT
```

</details>

---

<details>
<summary><b>8. Life Rules</b></summary>

Only memorize **two rules**.

### Alive cell

```text
2 or 3 neighbors
       ↓
    survives
```

```c
if (b[y][x] && (n == 2 || n == 3))
    new[y][x] = 1;
```

### Dead cell

```text
exactly 3 neighbors
       ↓
      born
```

```c
else if (!b[y][x] && n == 3)
    new[y][x] = 1;
```

Everything else becomes dead.

```text
ALIVE + 2/3 → ALIVE

DEAD + 3    → ALIVE

EVERYTHING ELSE → DEAD
```

Quick memory:

```text
SURVIVE = 2 / 3
BIRTH   = 3
```

</details>

---

<details>
<summary><b>9. Why Use a New Board?</b></summary>

The Game of Life updates all cells **simultaneously**.

Wrong:

```text
OLD BOARD
   ↓
change cell immediately
   ↓
next cell sees changed data
   ↓
WRONG
```

Correct:

```text
OLD BOARD
    │
    │ calculate
    ↓
NEW BOARD
```

Code:

```c
int **new = create_board(w, h);
```

After calculating:

```c
free_board(b, h);
return new;
```

Then:

```c
board = update_board(board, width, height);
```

</details>

---

<details>
<summary><b>10. Functions</b></summary>

```text
create_board()
    ↓
create empty board


read_input()
    ↓
move pen + draw


count_neighbors()
    ↓
count surrounding alive cells


update_board()
    ↓
apply Game of Life rules


print_board()
    ↓
alive = '0'
dead  = ' '


free_board()
    ↓
free memory
```

</details>

---

<details>
<summary><b>11. Program Flow</b></summary>

```text
main
 │
 ├── check arguments
 │
 ├── atoi()
 │
 ↓
create_board()
 │
 ↓
read_input()
 │
 ↓
┌───────────────────────┐
│ repeat N iterations   │
│                       │
│ update_board()        │
└───────────────────────┘
 │
 ↓
print_board()
 │
 ↓
free_board()
 │
 ↓
return 0
```

</details>

---

<details>
<summary><b>12. Output</b></summary>

Alive cell:

```c
putchar('0');
```

Dead cell:

```c
putchar(' ');
```

End of row:

```c
putchar('\n');
```

Example:

```text
0 0
 0 
000
```

</details>

---

<details>
<summary><b>13. Blinker Example</b></summary>

Starting board:

```text
 0 
 0 
 0 
```

After 1 iteration:

```text
   
000
   
```

After 2 iterations:

```text
 0 
 0 
 0 
```

Visual:

```text
ITERATION 0

 0
 0
 0

    ↓

ITERATION 1

000

    ↓

ITERATION 2

 0
 0
 0
```

</details>

---

<details>
<summary><b>14. Function Memory Map</b></summary>

```text
life
│
├── create_board
│      └── calloc
│
├── read_input
│      ├── x, y
│      ├── draw
│      ├── wasd
│      └── x toggle
│
├── count_neighbors
│      ├── -1 → +1
│      └── skip center
│
├── update_board
│      ├── alive + 2/3
│      └── dead + 3
│
├── print_board
│      ├── 1 → '0'
│      └── 0 → ' '
│
└── free_board
       ├── free rows
       └── free board
```

</details>

---

<details>
<summary><b>15. Quick Memorization Sheet</b></summary>

```text
INPUT
-----
./life WIDTH HEIGHT ITERATIONS


BOARD
-----
int **board

board[y][x]

0 = dead
1 = alive


PEN
---
w = up
a = left
s = down
d = right
x = draw ON/OFF


NEIGHBORS
---------
8 around cell

i = -1..1
j = -1..1

skip center:
i == 0 && j == 0


LIFE
----
alive + 2/3 → alive

dead + 3 → alive

else → dead


FLOW
----
create
↓
draw
↓
update × iterations
↓
print
↓
free
```

</details>

---

<details>
<summary><b>16. 30-Second Recall</b></summary>

```text
ARGS
width height iterations
        ↓
CREATE BOARD
        ↓
READ stdin
        ↓
wasd = move
x = draw toggle
        ↓
GAME OF LIFE
        ↓
count 8 neighbors
        ↓
alive + 2/3 = survive
dead + 3 = born
else = dead
        ↓
NEW BOARD
        ↓
repeat iterations
        ↓
PRINT
0 = alive
space = dead
        ↓
FREE
```

### Mental Model

Split the assignment into only **two problems**:

```text
PART 1: DRAWING

wasd + x
    ↓
initial board
```

```text
PART 2: LIFE

initial board
    ↓
count neighbors
    ↓
2/3 survive
3 born
    ↓
next board
```

Remember:

```text
DRAW FIRST
↓
SIMULATE SECOND
```
