*This project has been created as part of the 42 curriculum by [ atoumi ] , [ ssadi-ou ]*

# Minishell

## Description

Minishell is a simplified UNIX shell written in C.  
The goal of this project is to understand how a shell works by recreating core features of bash.

This includes:
    Command parsing and execution
    Environment variable management
    Handling pipes and redirections
    Signal management (Ctrl+C, Ctrl+D..)

Minishell reproduces a basic interactive shell where users can type commands, execute programs, and manage processes.

## Features

Prompt display
Execution of binaries (using PATH)

Built-in commands:

    `echo`
    `cd`
    `pwd`
    `export`
    `unset`
    `env`
    `exit`

Pipes (`|`)

Redirections:
- Input `<`
- Output `>`
- Append `>>`
- Heredoc `<<`

Environment variables (`$VAR`)

Signal handling 

## Instructions

### Compilation

Clone the repository 

make 

./minishell

## Resources

This project is based on concepts learned in previous 42 projects such as:

    Pipe handling from Pipex

    Signal management and inter-process communication from Minitalk

Some online resources, including technical videos. 

We also used AI to generate various command combinations in order to test the robustness and reliability of our Minishell.