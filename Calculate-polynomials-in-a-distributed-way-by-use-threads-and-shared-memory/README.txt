Calculate polynomials in a distributed way by use threads and shared memory
Authored by : Mohammad Khayyo
===========Description=============

-----in the first part of exercise -----
In this exercise we write a program that gets from the user a polynomial and calculates its value in a distributed way, The program will runs in an infinite loop, the program creat threads Dependence on how many variable (how many x) in polynomial.
each thread calculate the variable and at the end of the calculation the variable, The program will sum the results from threads and print the final value of the polynomial on the screen.
when the user writes done if the user write done the program finish.

-----in the second part of exercise -----
The same as the first but used shared memory instead of threads.



functions:

-----in the first part of exercise -----
they have 10 functions and one struct:

1- Fgets: this method will get from the user a polynomial and the value.

2- count_of_x: this method counts the number of x's in the polynomial.

3- count_of_Plus: this method counts the number of plus's in the polynomial.

4- TheVal: this method will get a string and the char and return the string is after the char.

5- ArrayToInt:  this method convert the String to int.

6-  selection:  this method will get first polynomial.

7- Factor: this method returns coefficient of the polynomial.

8- Pow: this method doing x^y.

9- Free_Polynomial: free allocations.

10- thread:this method will get the polynomial and place the val in it and save the result in the struct.

struct :this struct save the string for each threads and there result.

main: this method have infinite loop, the user enter the polynomials then the main use functions to split the polynomials to strings,
and creat shared memory, each process calculate the constant then sum the results from threads and print it.

-----in the second part of exercise -----

they have 11 functions and one struct:

======================== the differences in the second part ( methods and line code) ========================

-------------the differences in methods----------------

1- ForSons: this method will get the polynomial and place the val in it and save the result in the shared memory.

2- Find_result: this method will calculate the polynomial and save it to the shared memory.

struct :this struct save the string for each thread.

main: this method have infinite loop, the user enter the polynomials then the main use functions to split the polynomials to strings,
and creat shared memory, each process calculate the constant ,then sum the results from processes and print it.

-------------how many differences ----------------
2 methods, one struct and the main.
======================================================================================================================================================================
-------the same methods-------
3- Fgets: this method will get from the user a polynomial and the value.

4- count_of_x: this method counts the number of x's in the polynomial.

5- count_of_Plus: this method counts the number of plus's in the polynomial.

6- TheVal: this method will get a string and the char and return the string is after the char.

7- ArrayToInt:  this method convert the String to int.

8-  selection:  this method will get first polynomial.

9- Factor: this method returns coefficient of the polynomial.

10- Pow: this method doing x^y.

11- Free_Polynomial: free allocations.

=======Program Files=========
ex5a.c : the first part , they contain the main only and the functions.

ex5b.c : the second part , they contain the main only and the functions.

=========How to compile?========
(the first part):
gcc ex5a.c -o ex5a -pthread 
run: ./ex5a

(the second part):
gcc ex5b.c -o ex5b 
run: ./ex5b

=======Input ===========
---in first and second parts:-----
2*x^3+13*x^2+32*x^1+4, 3

========output==========
---in first and second parts:-----
The Final Result is: 271
