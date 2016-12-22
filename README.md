# Simple Shell

A re-creation of a UNIX shell using C.

**NOTE: Add a picture here!**


## Examples

Please follow __Download and Run Instructions__ below for initial setup. When inside the shell, you can:

Run an executable:
```
$ /bin/ls
```

Run an executable found in the `$PATH` environment variable:
```
$ ls
```

Run a shell built-in:
```
$ printenv
```

To find all built-ins, run the manual:
```
$ man ./man_1_simple_shell
```


## Download and Run Instructions

Clone Repo:
```
$ git clone https://github.com/guptaNswati/simple_shell.git
```

Compile:
```
$ gcc -Wall -Werror -Wextra -pedantic *.c ./tests/prompt-main.c -o simple_shell
```

Run the Executable:
```
$ ./simple_shell
```


## Requirements for this project

- All files will be compiled on Ubuntu 14.04 LTS
- Programs and functions will be compiled with `gcc 4.8.4` using the flags `-Wall`, `-Werror`, `-Wextra`, and `-pedantic`
- Code should comply with [Betty](https://github.com/holbertonschool/Betty) style.
- No more than 5 functions per file.
- All header files should be include guarded.
- List of allowed functions and system calls:
  * `access` (man 2 access)
  * `chdir` (man 2 chdir)
  * `close` (man 2 close)
  * `closedir` (man 3 closedir)
  * `execve` (man 2 execve)
  * `exit` (man 3 exit)
  * `fork` (man 2 fork)
  * `free` (man 3 free)
  * `fstat` (man 2 fstat)
  * `getcwd` (man 3 getcwd)
  * `getline` (man 3 getline)
  * `kill` (man 2 kill)
  * `lstat` (man 2 lstat)
  * `malloc` (man 3 malloc)
  * `open` (man 2 open)
  * `opendir` (man 3 opendir)
  * `perror` (man 3 perror)
  * `read` (man 2 read)
  * `readdir` (man 3 readdir)
  * `signal` (man 2 signal)
  * `stat` (man 2 stat)
  * `strtok` (man 3 strtok) - advanced task recreate
  * `wait` (man 2 wait)
  * `waitpid` (man 2 waitpid)
  * `wait3` (man 2 wait3)
  * `wait4` (man 2 wait4)
  * `write` (man 2 write)
  * `_exit` (man 2 _exit)


## File Descriptions

- `shell.h`: Header file which contains any library includes, structs created, and all function prototypes.
- `prompt.c`: Main shell file which prints and asks for prompt from User, creates tokens from User input, and runs executable or returns response if no executable found.
- `get-line.c`: Contains a rewrite of function getline and a tokenize function to split apart strings by delimiters.
- `env-get-set.c`: All functions related to environment variables. Functions include ability to Get, Set, Unset, Print, Check.
- `builtins.c`: Functions to handle built-in commands and checking commands via PATH environment variable.
- `string-funcs.c`: Helper functions that handle strings, include copy, compare, tokenize/parse, and concatenate.
- `string-funcs2.c`: More helper functions.
- `memory.c`: Functions to handle memory allocation and frees.
- `cd.c`: Shell built-in change directory command.
- `alias.c`: Functions to handle alias built-in command.
- `aliasFunc.c`: Contains a helper function to handle aliases.
- `hstry.c`: Functions to handle history built-in and storing history of inputted commands in an external parent directory.
- `help.c`: Functions to handle help built-in.
- `duplict-parse.c`: Helper functions for parsing and deep duping.


## Team

*Swati Gupta* - [Github](https://github.com/guptaNswati) || [Twitter](https://github.com/guptaNswati)

*Philip Yoo* - [Github](https://github.com/philipyoo) || [Twitter](https://twitter.com/philipYoo10)