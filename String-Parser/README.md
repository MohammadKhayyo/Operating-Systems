# String Parser
## Background
The **String Parser** program is a simple text analysis tool built using the C programming language. Authored by Mohammad Khayyo, it exemplifies a basic approach to parsing user-input strings and producing insights regarding word count and word lengths.

## Description
The **String Parser** tool prompts the user to input a sentence, which could be a single word or multiple words. The program processes this input to:
1. Display the total count of words in the sentence.
2. List each word alongside its length.

The essence of the program lies in its two core functions:
- `printHowManyWords`: Calculates and displays the number of words entered.
- `TheNumberOfLettersInEachWord`: Breaks the sentence into individual words and calculates the number of letters in each one.

## Usage
**Compilation**:
```bash
gcc ex1.c -o ex1
```
**Execution**:
```bash
./ex1
```

**Sample Input**:
```
It was raining yesterday
```

**Sample Output**:
```
4 words 
It : 2
was : 3
raining : 7
yesterday : 9
```

## Program Files
- `ex1.c`: Contains the main function and the two described helper functions.
