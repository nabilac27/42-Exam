## Exam 04
### ft_popen
**Assignment**: Implement a simplified version of the C standard library function `popen()`
- **Goal:** Launch an executable with arguments, return a file descriptor for reading (`'r'`) or writing (`'w'`)
- **Allowed functions:** `pipe`, `fork`, `dup2`, `execvp`, `close`, `exit`  
- **Key points:**  
  - Use `pipe()` to create communication channels  
  - Use `fork()` to create a child process  
  - Redirect `stdin`/`stdout` in the child using `dup2()`  
  - Execute the command with `execvp()`  
  - Close unused file descriptors and handle errors

---

### picoshell
**Assignment:** Implement a mini shell that executes pipelines of commands
- **Goal:** Execute a sequence of commands connected by pipes (like `cmd1 | cmd2 | cmd3`) 
- **Allowed functions:** `close`, `fork`, `wait`, `exit`, `execvp`, `dup2`, `pipe`  
- **Key points:**  
  - Convert received command-line arguments into a `cmds` array  
  - Create a **pipeline** connecting each command’s output to the next command’s input  
  - Use `fork()` for each command and `execvp()` to execute it  
  - Close all file descriptors properly to avoid leaks  
  - Wait for all child processes before returning  
  - Return `0` on success, `1` on any error

---

### sandbox
**Assignment:** Safely execute a function and determine if it behaves well.

- **Goal:** Test if a function `f` is "nice" (exits with 0) or "bad" (crashes, exits with nonzero, or times out).  
- **Allowed functions:** `fork`, `waitpid`, `exit`, `alarm`, `sigaction`, `kill`, `printf`, `strsignal`, `errno`  
- **Key points:**  
  - Use `fork()` to run `f` in a child process  
  - Use signals and `alarm()` to detect crashes or timeouts  
  - Return `1` if function is nice, `0` if bad, `-1` on error  
  - Print descriptive messages when `verbose` is true  
  - Avoid leaving zombie processes

---

### vbc
**Assignment:** Build a simple calculator that parses and evaluates arithmetic expressions.

- **Goal:** Parse expressions containing `+`, `*`, and parentheses `(` `)`, then evaluate them correctly.  
- **Allowed functions:** `malloc`, `calloc`, `realloc`, `free`, `printf`, `isdigit`, `write`  
- **Key points:**   
  - Recursively evaluate expressions  
  - Handle unexpected tokens and parenthesis errors  
  - Exit with code `1` and print a message if the input is invalid

---

### argo
**Assignment:** Implement a simplified JSON parser.

- **Goal:** Parse numbers, strings, and maps from a JSON-like input stream and reconstruct the structure.  
- **Allowed functions:** `getc`, `ungetc`, `printf`, `malloc`, `calloc`, `realloc`, `free`, `isdigit`, `fscanf`, `write`  
- **Key points:**  
  - Build an **AST** representing the JSON structure  
  - Handle recursive nesting (`{"a":{"b":42}}`)  
  - Detect syntax errors and print meaningful messages  
  - Preserve exact structure when printing valid JSON  
  - Return `1` on success, `-1` on failure
