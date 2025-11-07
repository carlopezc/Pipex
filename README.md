# 🚀 Pipex

> A C program that simulates the behavior of shell pipes (`|`).

---

## 🎯 Project Goals

This project is a fundamental introduction to **UNIX processes and inter-process communication (IPC)**. The main goal is to understand how the shell executes commands and makes them communicate. It involved learning to create new processes with `fork()`, manage file descriptors, redirect I/O, and use `execve()` to run external commands.

## 🛠️ Technical Details

* **Process Creation:** Uses `fork()` to create child processes, one for each command being executed.
* **Inter-Process Communication:** Implements a `pipe()` which is a one-way data channel. The `stdout` (output) of the first command is redirected to the write-end of the pipe, and the `stdin` (input) of the second command is redirected from the read-end.
* **Command Execution:** Uses `execve()` to replace the child process's memory space with the new command. This involves finding the correct path of the command executable from the `PATH` environment variable.
* **File Redirection:** Manages file descriptors to take input from an `infile` (simulating `<`) and send the final output to an `outfile` (simulating `>`).
* **Challenge:** The most complex part was managing all the file descriptors correctly. It's critical to close the right ends of the pipe in both the parent and child processes at the right time to avoid hangs (deadlocks) or processes waiting for input forever.

## ⚙️ How to Compile & Run

1.  Clone the repository:
    ```bash
    git clone [https://github.com/carlopezc/Pipex.git](https://github.com/carlopezc/Pipex.git)
    cd Pipex
    ```
2.  Compile the project:
    ```bash
    make
    ```
    This will create the main executable `pipex`.

3.  Run the program with four arguments:
    ```bash
    ./pipex [infile] [cmd1] [cmd2] [outfile]
    ```
    * `infile`: The name of an existing file to read from.
    * `cmd1`: The first command (e.g., "grep a").
    * `cmd2`: The second command (e.g., "wc -l").
    * `outfile`: The name of the file to write the final output to.

    **Example:**
    ```bash
    # This command is equivalent to the shell command:
    # < infile grep a | wc -l > outfile
    ./pipex infile "grep a" "wc -l" outfile
    ```
