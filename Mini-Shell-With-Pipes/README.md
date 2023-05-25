# Mini Shell With Pipes

### Authored by: Mohammad Khayyo

## Description

This program realizes a mini shell in C under the Linux operating system. We have enhanced the mini shell from exercise 2 by adding functionality for the '|' (pipe) character. This shell displays a prompt for the user, reads the commands, then sends them to the operating system for execution. In addition to reading commands, it is also able to execute the pipe function.

## Functions

1. `FreeIfFailed`: This method frees both pointers before exit if the system call or dynamic assignment is unsuccessful.
2. `Prompt`: This method displays the shell prompt.
3. `howManyQuotes`: This method calculates the number of Quotes in a string.
4. `howManyWords`: This method calculates the number of words in a string.
5. `freeDynamicAllocation`: This method frees allocated memory.
6. `TheNumberOfLettersInEachWord`: This method splits a sentence into words and calculates the number of letters in each word.
7. `thePlaceOfOnePipes`: This method returns the first index of pipe characters, if any.
8. `thePlaceOfSecondPipes`: This method returns the second index of pipe characters, if any.
9. `FreeMallocForOnePipes`: This method frees pointers if the system call or dynamic assignment failed.
10. `ProcessForOnePipes`: This method executes the Shell command if there is only one pipe.
11. `FreeForString`: This method frees allocated memory for created strings.
12. `FillTheStringsForOnePipe`: This method splits two strings at a single pipe character.
13. `TreatmentForOnePipe`: This method checks whether there is an empty command.
14. `FillTheStringsForTwoPipes`: This method splits three strings at two pipe characters.
15. `FreeMallocForTwoPipes`: This method frees pointers if the system call or dynamic assignment failed.
16. `ProcessForTwoPipes`: This method executes the Shell command if there are two pipe characters.
17. `closePiPes`: This method closes the open file descriptor entries.
18. `TreatmentForTwoPipe`: This method checks whether there is an empty command.
19. `ProcessForNonePipes`: This method executes the Shell command if there are no pipe characters.
20. `howManyPipes`: This method calculates the number of pipe characters.
21. `ProcessingForCommand`: This method selects a string from the user and redirects it to the appropriate method according to the number of pipes.

## Methods From Exercise 2

The following methods were available in exercise 2 and are used in exercise 3:

1. `howManyWords`
2. `TheNumberOfLettersInEachWord`
3. `freeDynamicAllocation`
4. `Process` (renamed to `ProcessForNonePipes` in this exercise)
5. `Prompt`

## New Methods

The following methods are new to exercise 3 and were not available in exercise 2:

1. `FreeIfFailed`
2. `howManyQuotes`
3. `thePlaceOfOnePipes`
4. `thePlaceOfSecondPipes`
5. `FreeMallocForOnePipes`
6. `ProcessForOnePipes`
7. `FreeForString`
8. `FillTheStringsForOnePipe`
9. `TreatmentForOnePipe`
10. `FillTheStringsForTwoPipes`
11. `FreeMallocForTwoPipes`
12. `ProcessForTwoPipes`
13. `closePiPes`
14. `TreatmentForTwoPipe`
15. `howManyPipes`
16. `ProcessingForCommand`

## Program Files

- `ex3.c`: Contains the main function and other functions.

## Compilation

Compile: `gcc ex3.c -o ex3`
Run: `./ex3`

## Input

`echo "hello,how are you?" | wc`

## Output

  1       3      19
