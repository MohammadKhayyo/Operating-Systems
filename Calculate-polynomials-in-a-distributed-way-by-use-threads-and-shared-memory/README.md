# Polynomial Calculation Using Threads and Shared Memory

## Background
Created by Mohammad Khayyo, this program demonstrates a distributed approach to calculate polynomial values. Utilizing threads and shared memory, the program efficiently breaks down and processes polynomial expressions.

## Description
There are two primary parts to the program:

**Part 1:** Uses threads to calculate the polynomial's value. The program spawns a thread for each variable in the polynomial, and each thread is responsible for calculating a portion of the polynomial.

**Part 2:** The same objective as Part 1, but employs shared memory instead of threads for distributed computation.

## Usage
### Compilation and Execution:
#### Part 1 (Threads):
```bash
gcc ex5a.c -o ex5a -pthread
./ex5a
```
Enter polynomials as input. To terminate, type "done".

#### Part 2 (Shared Memory):
```bash
gcc ex5b.c -o ex5b
./ex5b
```
Input format remains consistent with Part 1.

## Program Files
- `ex5a.c`: Contains the main function and associated functions for the thread-based computation.
- `ex5b.c`: Houses the main function and its corresponding functions for the shared memory approach.
