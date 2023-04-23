Mini Shell With Signals
Authored by : Mohammad Khayyo

==Description==
This exercise is a simple shell, receives a command from the user, and  parsing a string to do the order, this shell doing piping and signals, the types of signals that this exercise contain is the stop signal(SIGTSTP “^z”)and the continue signal (SIGCONT “fg”), the process will pause when entering (^z) and continue the work when entering(fg).

===functions ===:
===these methods were used in the past exercise (exercise 3) and in this exercise they have been used also to do the same work apart from function No'.19 (ProcessForNonePipes) that been change to do the signals order ===:
1)FreeIfFailed :method that makes both pointer free before the exit If the system call or dynamic assignment unsuccessful
2)Prompt :this method will get the Prompt
3)howManyQuotes :method that calculates how many Quotes there are
4)howManyWords :the method will calculate how many words we entered through the string
5)freeDynamicAllocation :this method free's the memory of all alloc
6)TheNumberOfLettersInEachWord :this method will cut the sentence into words and calculate how many letters are in them
7)thePlaceOfOnePipes :method that returns the first index of Pipes if any
8)thePlaceOfSecondPipes :method that returns the Second index of Pipes if any
9)FreeMallocForOnePipes :method that frees pointers if the system call or dynamic assignment failed
10)ProcessForOnePipes :this method will take the Shell command and activate it if there is only one pipe
11)FreeForString :Makes free for dynamic assignment of the strings we have created
12)FillTheStringsForOnePipe :method that fills two strings if there is only one pipe ,Before the pipe in the string and what is after it in another string
13)TreatmentForOnePipe :It makes two strings and sends them to the FillTheStringsForOnePipe function And the purpose of it is to check whether there is an empty command
14)FillTheStringsForTwoPipes :method that fills two strings if there are only two pipes, Before the pipe in the string and what is after the pipe up to the second pipe in the second string and what is after the second pipe in another string
15)FreeMallocForTwoPipes :method that frees pointers if the system call or dynamic assignment failed
16)ProcessForTwoPipes :this method will take the Shell command and activate it if there are only two pipes
17)closePiPes :method that closes the open file descriptor entries
18)TreatmentForTwoPipe :It makes three strings and sends them to the FillTheStringsForTwoPipes function And the purpose of it is to check whether there is an empty command
19)ProcessForNonePipes :this method will take the Shell command and activate it  if it did not have Pipes, and it receives the signal order for stopping and continuing the process by entering legal input.
20)howManyPipes :method that calculates how many Pipes there are
21)ProcessingForCommand :method that picks up a string from the user and according to the pipe number it will refer it to the appropriate method

==Program Files==

ex4.c :  it contains the main and the functions.

==How to compile?==

compile: gcc ex4.c -o ex4
run: ./ex4

=======Input ==========
cat and press enter and  press Ctrl-Z
then enter fg

==========Output =============
running the last suspended process
