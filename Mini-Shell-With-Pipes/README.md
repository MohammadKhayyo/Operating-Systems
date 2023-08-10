# Mini Shell with Pipes

## Background
Authored by: **Mohammad Khayyo**

This software is a C-based implementation of a mini shell for the Linux operating system. It extends the functionalities of a previous project (referred to as Mini-shell) by introducing support for pipe functionality (`|`). The shell's primary objective is to parse user input commands, detect the presence of pipes, and execute the commands accordingly.

## Description

Upon initiation, the mini shell displays a prompt for the user. The user can then input commands that the shell reads and sends to the operating system for execution. One of the distinguishing features of this shell compared to its predecessor is its capability to handle the piping function. It can process commands with a maximum of two pipes.

### Key Features
- User command prompt display
- Command parsing and execution
- Support for single and double pipe commands

## Usage

1. **Compilation**: Use the following command to compile the source code:
   ```bash
   gcc ex3.c -o ex3
   ```

2. **Running the Shell**: Once compiled, run the shell using:
   ```bash
   ./ex3
   ```

3. **Sample Command**: 
   ```bash
   echo "hello,how are you?" | wc
   ```
   Expected Output:
   ```
   1 3 19
   ```

## Program Files
- **ex3.c**: Contains the main logic and functions of the mini shell.
