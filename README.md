# 0x16. C - Simple Shell

## Alx School - Alx Simple Shell(hsh)

This project is a simple UNIX command-line interpreter, also known as a shell. It is capable of reading commands from standard input, parsing them, and executing them.

### Prerequisites

Only use the following functions and system calls:

```
access (man 2 access)
chdir (man 2 chdir)
close (man 2 close)
closedir (man 3 closedir)
execve (man 2 execve)
exit (man 3 exit)
_exit (man 2 _exit)
fflush (man 3 fflush)
fork (man 2 fork)
free (man 3 free)
getcwd (man 3 getcwd)
getline (man 3 getline)
getpid (man 2 getpid)
isatty (man 3 isatty)
kill (man 2 kill)
malloc (man 3 malloc)
open (man 2 open)
opendir (man 3 opendir)
perror (man 3 perror)
read (man 2 read)
readdir (man 3 readdir)
signal (man 2 signal)
stat (__xstat) (man 2 stat)
lstat (__lxstat) (man 2 lstat)
fstat (__fxstat) (man 2 fstat)
strtok (man 3 strtok)
wait (man 2 wait)
waitpid (man 2 waitpid)
wait3 (man 2 wait3)
wait4 (man 2 wait4)
write (man 2 write)
```

### Installing

Compile like this:

```
gcc -Wall -Wextra -Werror -pedantic -g *.c -o hsh
```

The `-g` is for tracing Valgrind errors

# Testing

Your shell should work like this in interactive mode:

```
$ ./hsh($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
```

But also in non-interactive mode:

```
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
```

## Description of File Structure

1. [builtins.c](builtins.c) - Includes builtin functions:

- `is_builtin()` - checks to see if the command is a builtin, then returns a function pointer to one of the following functions:
- `_exit_with_grace` - exits the shell and frees any malloc'd space.
- `_env()` - prints the current environment.
- `_cd()` - change pwd. Can be used without arguments. `cd -` takes the user to the last directory. `cd ~` takes the user home.`<em>`Not yet built `</em>`
- `help()` - Prints help for builtin commands.`<em>`Not yet built `</em>`

2. [builtins_2.c](builtins_2.c) - Second file with builtin functions:

- `_setenv_usr()` - User creates or modifies an environment variable.
- `_unsetenv_usr()` - User deletes an environment variable.`<em>`Not yet built `</em>`
- `_alias` - Sets, modifies or prints an alias. `<em>`Not yet built `</em>`
- `_history` - Prints the history. Clear history with -c flag. `<em>`Not yet built `</em>`

3. [env_operations.c](env_operations.c)

- `_getenv()` - recreation of `getenv()` from `<stdlib.h>`. Gets the value of the provided key. Returns NULL if not found or on error.
- `_unsetenv()` - Unsets an environmental variable. `<em>`Not yet built. Currently, just returns the output from the standard library.`</em>`
- `_setenv()` - Adds or modifies an environmental variable. `<em>`Not yet built. Currently, just returns the output from the standard library.`</em>`

5. [execution.c](executor.c) - Includes only one function that is essential to the core functionality

- `executor()` - Executes a command

7. [shell.c](main.c) - Entry point to program, contains only the opening message.
8. [parse_command.c](parser.c) - Includes all string parsing related functions, and includes functions critical to the basic functionality:

- `_getline()` - Recreation of `getline()` from `<stdio.h>`. Gets a line from stdin, delimited by a `\n` character. Also handles `EOF`. Returns the line, or NULL on error.
- `parser()` - Parses a string into tokens. Returns a double pointer.
- `is_alias` - Filler function for handling aliases. Currently does not do anything. `<em>` This functionality has not been built.`</em>`
- global variable `flag` for `signalhandler()` - Triggers when `^C` is hit, then turns off.
- `sighandler`` - Interrupts the running process if it is not a builtin then prints the prompt again.
- `reader()` - Reads user input, turns it into a string and parses it into tokens. Then it performs actions based on the first token.

10. [shell.h](shell.h) - Header file: Contains all struct definitions, macros, standard library includes, and function prototypes.
11. \_[strtok.c](strtok.c) - Includes the strtok function, as well as helper functions that do not need to be referenced elsewhere

- `_strchr()` - Checks for a char in a string. Returns the string on success, and NULL on failure. Recreation of `strchr()` from `<string.h>`
- `_strspn()` - Gets the length of a substring. Recreation of `strspn()` from `<string.h>` with a different return type.
- `_strpbrk() - search a string for any set of bytes. Recreation of `strpbrk()`from`<string.h>``
- `_strtok_r()` - Split a string into tokens, and alters the string in the process. Recreation of `strtok` from `<string.h>`

## Team

- _Amal Cholo_ - [Github](https://github.com/ivy-515)
