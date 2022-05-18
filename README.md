# Holberton's simple shell.

##

### Description

This is a simple Shell based on the Sh Linux shell. It executes commands given by the user or from a file.

### Usage

You can compile the source files using ` $ gcc -Wall -Werror -Wextra -pedantic -std=c90 *.c -o hsh `
The shell can operate in two modes, interactive and non-interactive.
In the interactive mode, you run it by typing ` ./hsh ` and then typing your command when the prompt appears, finishing with the enter key. To exit the console in this mode, you can use the exit command or hit control + D.
In the non-interactive mode you can use a pipe to make the shell execute just one command, for example: ` echo ls | ./hsh ` will make the shell execute the ls command and go back to your current shell.
Also, you can use ` ./hsh file ` To execute a set of instructions from file.

### Files in this repo

| File | Description |
| ------ | ------ |
| [AUTHORS](https://github.com/Daransoto/simple_shell/blob/master/AUTHORS) | Authors of the shell.  |
| [README.md](https://github.com/Daransoto/simple_shell/blob/master/README.md) | Readme file for the repo. |
| [alias.c](https://github.com/Daransoto/simple_shell/blob/master/alias.c) | Functions to handle alias creation.  |
| [aliexpansion.c](https://github.com/Daransoto/simple_shell/blob/master/aliexpansion.c) | Functions to handle alias expansion.  |
| [atoi.c](https://github.com/Daransoto/simple_shell/blob/master/atoi.c) | Converts a string to a number.  |
| [change_dir.c](https://github.com/Daransoto/simple_shell/blob/master/change_dir.c) | Functions to handle the cd builtin.  |
| [check_builtins.c](https://github.com/Daransoto/simple_shell/blob/master/check_builtins.c) | Checks if the command entered is a builtin.  |
| [check_newlines.c](https://github.com/Daransoto/simple_shell/blob/master/check_newlines.c) | Checks if the command has multiple lines.  |
| [exit.c](https://github.com/Daransoto/simple_shell/blob/master/exit.c) | Exit builtin.  |
| [expand_vars.c](https://github.com/Daransoto/simple_shell/blob/master/expand_vars.c) | Handles variable expansion.  |
| [getenv.c](https://github.com/Daransoto/simple_shell/blob/master/getenv.c) | Gets an environment variable.  |
| [getline.c](https://github.com/Daransoto/simple_shell/blob/master/getline.c) | Own implementation of getline function, gets input from user.  |
| [history.c](https://github.com/Daransoto/simple_shell/blob/master/history.c) | Functions to handle the history builtin.  |
| [holberton.h](https://github.com/Daransoto/simple_shell/blob/master/holberton.h) | Header file with prototypes of functions.  |
| [man_1_simple_shell](https://github.com/Daransoto/simple_shell/blob/master/man_1_simple_shell) | Manual page for our shell.  |
| [prepare_command.c](https://github.com/Daransoto/simple_shell/blob/master/prepare_command.c) | Function that parses the input command and start the processes needed to execute it.  |
| [print_number.c](https://github.com/Daransoto/simple_shell/blob/master/print_number.c) | Prints a given number.  |
| [remove_spaces.c](https://github.com/Daransoto/simple_shell/blob/master/remove_spaces.c) | Removes unnecesary spaces from the command.  |
| [setenv.c](https://github.com/Daransoto/simple_shell/blob/master/setenv.c) | Functions to set and unset variables.  |
| [shell.c](https://github.com/Daransoto/simple_shell/blob/master/shell.c) | Main file of the shell, has the entry point.  |
| [strcat.c](https://github.com/Daransoto/simple_shell/blob/master/strcat.c) | Concatenates two strings.  |
| [strcmp.c](https://github.com/Daransoto/simple_shell/blob/master/strcmp.c) | Compares two strings.  |
| [strcpy.c](https://github.com/Daransoto/simple_shell/blob/master/strcpy.c) | Copies one string into a memory space.  |
| [strlen.c](https://github.com/Daransoto/simple_shell/blob/master/strlen.c) | Gives the length of a string.  |
| [strncmp.c](https://github.com/Daransoto/simple_shell/blob/master/strncmp.c) | Compares n bytes of two strings.  |
| [strtok.c](https://github.com/Daransoto/simple_shell/blob/master/strtok.c) | Own implementation of strtok function.  |


## Authors

[Darwin Soto](https://twitter.com/darutos)\
[Santiago Herrera](https://twitter.com/santiherrerago)
