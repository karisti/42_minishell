# 42_minishell

## Description
This project consists of creating our own little bash. A program that can parse a command and execute it with arguments.

### Re-implemented features:
- Runs executables from an absolute, relative or environment PATH (`/bin/ls` or `ls`), including arguments or options. `'` and `"` work the same as bash, except for multiline commands.
- Redirections `>` `>>` `<`.
- Pipes `|`.
- You can separate commands with `;`.
- Environment variables like `$HOME`, including the return code `$?`.
- Handling signals: `Ctrl-C` to interrupt, `Ctrl-\` to quit a program and `Ctrl-D` to throw an EOF.
- Some "built-in" functions: `echo`, `pwd`, `cd`, `env`, `export`, `unset` and `exit`.

## Prerequisites
- Nothing needed

## Usage
- `make` for creating executable
- `./minishell` for execution
- Run commands

## Lessons
- Redirections
- Pipes
- Environment variables
- Signal handling
- Shell commands 

## Resources
- [harm-smits minishell](https://harm-smits.github.io/42docs/projects/minishell "harm-smits minishell")
- [Writing Your Own Shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf "Writing Your Own Shell")
- [minishell flow image](https://github.com/romanwrites/minishell/blob/master/images/3.png "minishell flow image")
- [Shell Command Language](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html "Shell Command Language")
- [Enseñarle a implementar un miniShell en lenguaje C](https://programmerclick.com/article/69491426925/ "Enseñarle a implementar un miniShell en lenguaje C")
- [How the shell works internally when entering a command](https://medium.com/@muxanz/how-the-shell-works-internally-when-entering-a-command-42f08458870 "How the shell works internally when entering a command")
- [Minishell explained](https://www.big-meter.com/opensource/en/60d00460ec41d21e72706e3b.html "Minishell explained")
- [Tester: minishell-tester](https://github.com/solaldunckel/minishell-tester "Tester: minishell-tester")
- [Tester: minishell tests excel](https://docs.google.com/spreadsheets/d/1fniV2dSRB5TaFGyX3O-iK0u61xR5jDdkFKYonKpilIc/edit#gid=0 "Tester: minishell tests excel")
- [Tester: mini_tester](https://github.com/potatokuka/mini_tester/blob/main/test_cmds.txt "Tester: mini_tester")
- [Tester: minishell_tests](https://github.com/t0mm4rx/minishell_tests "Tester: minishell_tests")
