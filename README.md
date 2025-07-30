# 🐚 Minishell — As Beautiful as a Shell

> A simplified recreation of Bash written in C, built from scratch as part of the 42 curriculum.  
> Designed to mimic a modern shell's behavior with process control, environment management, redirections, and more.

---

## 📜 Project Overview

**Minishell** is a minimal, interactive shell inspired by the original Unix shell experience.  
The project emphasizes deep learning of process management, file descriptors, and terminal behavior in Unix-like systems.  
It aims to provide a stable CLI environment with support for pipelines, redirections, and essential built-in commands.

---

## ⚙️ Features

### ✅ Mandatory
- 🧾 **Prompt** display with history and user input handling
- 🔍 **PATH resolution** and direct executable launching
- 🔄 **Environment variable expansion** (`$VAR`, `$?`)
- ⛔ **Quote handling** (single `'` and double `"` quotes)
- 🧭 **Built-in Commands**:
  - `echo` (supports `-n`)
  - `cd` (with path handling)
  - `pwd`
  - `export` / `unset`
  - `env`
  - `exit`
- 🔁 **Redirections**:
  - `<`, `>`, `>>`, `<<` (heredoc)
- 📡 **Pipes** (`|`)
- ⌨️ **Interactive signal handling**:
  - `ctrl-C` starts a new prompt
  - `ctrl-D` exits shell
  - `ctrl-\` is ignored
- 📚 **Memory-safe**: All heap allocations are freed (excluding `readline` internals)

### ✨ Bonus
- `&&` and `||` operators with parentheses for grouping
- `*` wildcard expansion in the current directory

---

## 🛠️ Technologies Used

- Language: **C**
- Library: [GNU Readline](https://tiswww.case.edu/php/chet/readline/rltop.html)
- System Calls: `fork()`, `execve()`, `pipe()`, `dup2()`, `signal()`, `wait()`, `open()`, `read()`, `write()`, and many more.

---

## 📦 Build Instructions

```bash
make
./minishell
