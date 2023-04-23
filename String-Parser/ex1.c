
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#define MAX 511// length of the String
void howManyWords(const char str[]); // the method will calculate how many words we entered through the string
void TheNumberOfLettersInEachWord(const char str[],char temp[],char* text);// this method will cut the sentence into words and calculate how many letters are in them
int main() {
    char str[MAX];// String we want to enter by use fgets
    char temp[MAX]; //temp string
    char *text = NULL;
    for(;;) {
        if(fgets(str, MAX, stdin)==NULL) {// Checks if the String we enter it was NULL
            printf("the scanner is filed");// Print error
            continue;
        }
        str[strlen(str) - 1] = '\0';
        if(strcmp(str , "exit" )== 0){
            break;
        }
        howManyWords(str);
        TheNumberOfLettersInEachWord(str,temp,text);
    }
    return 0;
}
void howManyWords(const char str[]) { // the method will calculate how many words we entered through the string
    int i;
    int countOfWords = 0;
    for (i = 0; str[i] != '\0'; i++) {// this Loop count how many words in the String
        if (str[i] != ' ' && (str[i+1] == ' ' || str[i+ 1] == '\0')) {// this condition checks  if the char is not a space and the char after it is a space or the end of sentence
            countOfWords++;
        }
    }
    if(countOfWords!=0)
        printf("%d words \n", countOfWords);// print how many word are in the String
}
void TheNumberOfLettersInEachWord(const char str[], char temp[], char *text) {// this method will cut the sentence into words and calculate how many letters are in them
    strcpy(temp, "");
    int counter = 0;
    int k = 0;// use k  to move on temp indexes
    int i;
    for (i = 0; str[i] != '\0'; i++) {// this loop will cut the sentence into words and calculate how many letters are in them
        if (str[i] != ' ') {// this condition will check if the char is not equal to space
            counter++;
            temp[k] = str[i];//put the char in temp
            k++;
        }
        if (str[i] != ' ' && (str[i + 1] == ' ' || str[i + 1] == '\0')) {// this condition checks  if the char is not a space and the char after it is a space or the end of sentence
            temp[k] = '\0';//will mark the end of a temp
            text = (char *) malloc(sizeof(char) * (counter + 1));// array there length is the char size * (the size of the temp+1('\0'))
            if (text == NULL) // condition If dynamic allocation failed
            {
                puts("The malloc is failed\n");
                exit(1);// exit the code
            }
            strcpy(text, temp);// copy from temp to word
            printf("%s : %d\n", temp, counter);// prints the word and the length
            counter = 0;
            k = 0;
            strcpy(temp, "");// rest
            free(text);// free memory
        }
    }
}
