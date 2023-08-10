# Mini Shell

### Background
Mini Shell is an interface program designed to emulate the behavior of a shell under the Linux operating system. Authored by Mohammad Khayyo, this program reads user commands and transmits them to the OS in the correct format for execution.

### Description
There are two main parts to the Mini Shell program:

- **ex2a**: This is a basic version of the shell that simply reads and executes user commands.

- **ex2b**: A more advanced version that operates like `ex2a` but has an additional feature. Before each command's execution, it prints out the scheduler information for the process that is running the command.

### Usage
To compile and run the two parts of the program:

**For ex2a**:
```
gcc ex2a.c -o ex2a
./ex2a
```

**For ex2b**:
```
gcc ex2b.c -o ex2b
./ex2b
```

### Program Files
- `ex2a.c`: Contains the main function and related functionalities for the first part.
- `ex2b.c`: Contains the main function and additional functionalities to print the scheduler information for the second part.
