# ft_popen

A simplified reimplementation of the standard **`popen()`** using Unix system calls.

---

## Pipe Basics

Creating a pipe:
```c
int pipe_fd[2];
pipe(pipe_fd);
```

## Data flow:
```bash
pipe_fd[1]  --->  pipe_fd[0]
(write)          (read)
```

---

## BEFORE pipe()
```bash
Process
 ├─ 0 → STDIN
 ├─ 1 → STDOUT
 └─ 2 → STDERR
```

## AFTER pipe(pipe_fd)
```bash
Process
 ├─ 0 → STDIN
 ├─ 1 → STDOUT
 ├─ 2 → STDERR
 ├─ 3 → pipe read  (pipe_fd[0])
 └─ 4 → pipe write (pipe_fd[1])
```

So the pipe is like a tube:
```bash
pipe_fd[1]  --->  pipe_fd[0]
(write)          (read)
```

---

## AFTER fork()
```bash
Parent                     Child
------                     -----
0 stdin                    0 stdin
1 stdout                   1 stdout
2 stderr                   2 stderr
3 pipe read (pipe_fd[0])   3 pipe read (pipe_fd[0])
4 pipe write (pipe_fd[1])  4 pipe write (pipe_fd[1])
```

Now both processes have the same FDs.
But each process must close what it doesn't need.

---

## Case 'r'

Command output → parent

```bash
Child stdout
      │
      ▼
   pipe_fd[1]  ===== PIPE =====> pipe_fd[0]
                                      │
                                      ▼
                                   Parent
```

Code logic:
```c
    dup2(pipe_fd[1], STDOUT)
    return pipe_fd[0]
```

---

## Case 'w'

Parent sends input → command

```bash
Parent write
      │
      ▼
   pipe_fd[1]  ===== PIPE =====> pipe_fd[0]
                                      │
                                      ▼
                                  Child stdin
```

Code logic:
```c
    dup2(pipe_fd[0], STDIN)
    return pipe_fd[1]
```

---

Remember the meaning of 'r' and 'w'
Think from the parent perspective.

```bash
| type  | child does      | parent gets |
| ----- | --------------- | ----------- |
| `'r'` | writes to pipe  | read end    |
| `'w'` | reads from pipe | write end   |
```

---

| Function             | Error signal          |
| -------------------- | --------------------- |
| `return -1`          | function failed       |
| `exit(EXIT_FAILURE)` | terminate the process |

===

| Code                 | Meaning                        |
| -------------------- | ------------------------------ |
| `exit(EXIT_SUCCESS)` | program finished successfully  |
| `exit(EXIT_FAILURE)` | program failed                 |
| `exit(1)`            | also failure (common shortcut) |



