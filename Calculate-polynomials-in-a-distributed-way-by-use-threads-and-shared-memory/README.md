# Calculate Polynomials in a Distributed Way

Calculate polynomials in a distributed way by using threads and shared memory.

Authored by: Mohammad Khayyo

## Description

### First Part

In this exercise, we write a program that gets a polynomial from the user and calculates its value in a distributed way. The program runs in an infinite loop, creating threads depending on the number of variables (x) in the polynomial. Each thread calculates the value of a variable, and at the end, the program sums the results from the threads and prints the final value of the polynomial on the screen. If the user enters "done," the program finishes.

### Second Part

The second part of the exercise is similar to the first part, but it uses shared memory instead of threads.

## Functions

### First Part

The first part includes 10 functions and one struct:

1. Fgets: This method gets a polynomial and its value from the user.
2. count_of_x: This method counts the number of x's in the polynomial.
3. count_of_Plus: This method counts the number of plus signs in the polynomial.
4. TheVal: This method returns the string after a given character.
5. ArrayToInt: This method converts a string to an integer.
6. selection: This method gets the first polynomial.
7. Factor: This method returns the coefficient of the polynomial.
8. Pow: This method performs x^y.
9. Free_Polynomial: This method frees memory allocations.
10. thread: This method calculates the value of the polynomial for each thread and saves the result in the struct.

Struct: This struct saves the string for each thread and its result.

Main: This method contains an infinite loop where the user enters polynomials. The main program uses the functions to split the polynomials into strings, creates shared memory, and calculates the constant. It then sums the results from the threads and prints the final result.

### Second Part

The second part includes 11 functions and one struct:

- The differences in the second part include two methods, one struct, and the main program.

- The methods are:
  - ForSons: This method calculates the value of the polynomial and saves it to the shared memory.
  - Find_result: This method calculates the polynomial and saves the result to the shared memory.

Struct: This struct saves the string for each thread.

Main: This method contains an infinite loop where the user enters polynomials. The main program uses the functions to split the polynomials into strings, creates shared memory, calculates the constant, sums the results from the processes, and prints the final result.

## Program Files

- `ex5a.c`: Contains the main program and functions for the first part.
- `ex5b.c`: Contains the main program and functions for the second part.

## How to Compile and Run

### First Part

To compile the first part of the program, use the following command:

gcc ex5a.c -o ex5a -pthread

To run the compiled program, execute the following command:

./ex5a

### Second Part

To compile the second part of the program, use the following command:

gcc ex5b.c -o ex5b

To run the compiled program, execute the following command:

./ex5b

## Input

Both the first and second parts of the program require the following input format:

<polynomial_expression>, <value>

For example:

2x^3+13x^2+32\*x^1+4, 3
