# Calculate Polynomials in a Distributed Way by Using Threads and Shared Memory

## Authored by: Mohammad Khayyo

## Description

### First Part of the Exercise

In this exercise, we write a program that receives a polynomial from the user and calculates its value in a distributed way. The program runs in an infinite loop, creating threads depending on how many variables (how many `x`) are in the polynomial. Each thread calculates the variable and, at the end of the calculation, the program sums up the results from the threads and prints the final value of the polynomial on the screen. The program finishes when the user writes 'done'.

### Second Part of the Exercise

This part is similar to the first, but uses shared memory instead of threads.

## Functions

### First Part of the Exercise

The first part of the exercise contains 10 functions and one struct:

1. `Fgets`: This method gets a polynomial and its value from the user.

2. `count_of_x`: This method counts the number of `x` in the polynomial.

3. `count_of_Plus`: This method counts the number of plus signs in the polynomial.

4. `TheVal`: This method receives a string and a character and returns the string that comes after the character.

5. `ArrayToInt`: This method converts the String to int.

6. `selection`: This method gets the first polynomial.

7. `Factor`: This method returns the coefficient of the polynomial.

8. `Pow`: This method calculates `x^y`.

9. `Free_Polynomial`: This method frees allocations.

10. `thread`: This method receives the polynomial, places the value in it, and saves the result in the struct.

The `struct` stores the string for each thread and their results.

### Second Part of the Exercise

The second part of the exercise contains 11 functions and one struct:

#### Differences in the Second Part

1. `ForSons`: This method receives the polynomial, places the value in it, and saves the result in the shared memory.

2. `Find_result`: This method calculates the polynomial and saves it to the shared memory.

The `struct` stores the string for each thread.

#### Similar Methods

The following methods are the same in both parts:

1. `Fgets`
2. `count_of_x`
3. `count_of_Plus`
4. `TheVal`
5. `ArrayToInt`
6. `selection`
7. `Factor`
8. `Pow`
9. `Free_Polynomial`

## Program Files

1. `ex5a.c`: The first part. Contains the main function and other functions.
2. `ex5b.c`: The second part. Contains the main function and other functions.

## How to Compile

### First Part

Compile: `gcc ex5a.c -o ex5a -pthread`
Run: `./ex5a`

### Second Part

Compile: `gcc ex5b.c -o ex5b`
Run: `./ex5b`

## Input

For both parts:

`2*x^3+13*x^2+32*x^1+4, 3`

## Output

For both parts:

`The Final Result is: 271`
