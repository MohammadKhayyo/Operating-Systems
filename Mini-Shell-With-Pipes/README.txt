Mini Shell With Pipes
Authored by : Mohammad Khayyo


==Description==
In this exercise it is realized a mini shell In the language C Under the operating system linux this mini shell we did in exercise 2 but we will add in this exercise
the realized for character '|' Means creation pipe, and the max number of pipe will be in one command is two 
the shell Will display prompt for user And Read the commands then send them to the operating system To perform.
This program in addition to reading command is able to do the Pipe function.

===functions ===:
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
19)ProcessForNonePipes :this method will take the Shell command and activate it  if it did not have Pipes
20)howManyPipes :method that calculates how many Pipes there are
21)ProcessingForCommand :method that picks up a string from the user and according to the pipe number it will refer it to the appropriate method

===this methods are available in exercise 2 and i use them in the exercise 3===:
1: howManyWords: the method will calculate how many words we entered through the string.
2: TheNumberOfLettersInEachWord: this method will cut the sentence into words and calculate how many letters are in them.
3: freeDynamicAllocation: this method free's the memory of all alloc.
4: Process: this method will take the Shell command and activate it. and I change it's name to ProcessForNonePipes :this method will take the Shell command and activate it  if it did not have Pipes
5: Prompt: this method will get the Prompt.

===this methods are new and not available in exercise 2 ===:
1)FreeIfFailed :method that makes both pointer free before the exit If the system call or dynamic assignment unsuccessful
2)howManyQuotes :method that calculates how many Quotes there are
3)thePlaceOfOnePipes :method that returns the first index of Pipes if any
4)thePlaceOfSecondPipes :method that returns the Second index of Pipes if any
5)FreeMallocForOnePipes :method that frees pointers if the system call or dynamic assignment failed
6)ProcessForOnePipes :this method will take the Shell command and activate it if there is only one pipe
7)FreeForString :Makes free for dynamic assignment of the strings we have created
8)FillTheStringsForOnePipe :method that fills two strings if there is only one pipe ,Before the pipe in the string and what is after it in another string
9)TreatmentForOnePipe :It makes two strings and sends them to the FillTheStringsForOnePipe function And the purpose of it is to check whether there is an empty command
10)FillTheStringsForTwoPipes :method that fills two strings if there are only two pipes, Before the pipe in the string and what is after the pipe up to the second pipe in the second string and what is after the second pipe in another string
11)FreeMallocForTwoPipes :method that frees pointers if the system call or dynamic assignment failed
12)ProcessForTwoPipes :this method will take the Shell command and activate it if there are only two pipes
13)closePiPes :method that closes the open file descriptor entries
14)TreatmentForTwoPipe :It makes three strings and sends them to the FillTheStringsForTwoPipes function And the purpose of it is to check whether there is an empty command
15)howManyPipes :method that calculates how many Pipes there are
16)ProcessingForCommand :method that picks up a string from the user and according to the pipe number it will refer it to the appropriate method

==Program Files==

ex3.c :  they contain the main and the functions.

==How to compile?==

compile: gcc ex3.c -o ex3
run: ./ex3

=======Input ==========

echo "hello,how are you?" | wc

==========Output =============

      1       3      19

