# Mini Shell With Signals

## Authored by: Mohammad Khayyo

## Description
This exercise is a simple shell that receives a command from the user, parses a string to perform the command. This shell handles piping and signals. The types of signals that this exercise includes are the stop signal (SIGTSTP “^z”) and the continue signal (SIGCONT “fg”). The process will pause upon entering (^z) and continue the operation when entering (fg).

## Functions
These methods were used in a previous exercise (exercise 3) and in this exercise they are also used to do similar tasks, apart from function No. 19 (ProcessForNonePipes) that has been changed to handle the signal order:

1. `FreeIfFailed`: Method that frees both pointers before exit if a system call or dynamic assignment fails.
2. `Prompt`: This method gets the Prompt.
3. `howManyQuotes`: Method that calculates the number of quotes.
4. `howManyWords`: This method calculates the number of words entered through the string.
5. `freeDynamicAllocation`: This method frees memory of all allocated objects.
6. `TheNumberOfLettersInEachWord`: This method divides the sentence into words and calculates the number of letters in them.
7. `thePlaceOfOnePipes`: Method that returns the first index of Pipes, if any.
8. `thePlaceOfSecondPipes`: Method that returns the second index of Pipes, if any.
9. `FreeMallocForOnePipes`: Method that frees pointers if a system call or dynamic assignment fails.
10. `ProcessForOnePipes`: This method takes the Shell command and activates it if there is only one pipe.
11. `FreeForString`: Makes a free for dynamic assignment of the strings we have created.
12. `FillTheStringsForOnePipe`: Method that fills two strings if there is only one pipe, with the string before the pipe and what comes after it in another string.
13. `TreatmentForOnePipe`: It makes two strings and sends them to the FillTheStringsForOnePipe function. Its purpose is to check whether there is an empty command.
14. `FillTheStringsForTwoPipes`: Method that fills two strings if there are only two pipes. Before the pipe in the string and what is after the pipe up to the second pipe in the second string, and what is after the second pipe in another string.
15. `FreeMallocForTwoPipes`: Method that frees pointers if a system call or dynamic assignment fails.
16. `ProcessForTwoPipes`: This method takes the Shell command and activates it if there are only two pipes.
17. `closePiPes`: Method that closes open file descriptor entries.
18. `TreatmentForTwoPipe`: It makes three strings and sends them to the FillTheStringsForTwoPipes function. Its purpose is to check whether there is an empty command.
19. `ProcessForNonePipes`: This method takes the Shell command and activates it if it does not have Pipes. It handles the signal order for stopping and continuing the process by entering legal input.
20. `howManyPipes`: Method that calculates how many Pipes there are.
21. `ProcessingForCommand`: Method that receives a string from the user and, based on the number of pipes, will refer it to the appropriate method.

## Program Files
`ex4.c`: Contains the main function and other functions.

## How to Compile
Compile with `gcc ex4.c -o ex4`
Run with `./ex4`

## Input
Enter `cat` and press enter, then press `Ctrl-Z`. Then enter `fg`.

## Output
Displays the message "running the last suspended process"
