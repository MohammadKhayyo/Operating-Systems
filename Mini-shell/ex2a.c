
#include <sys/types.h>
#include <stdio.h>
#include "string.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pwd.h>
#define MAX 511// length of the String
int howManyWords(const char str[],int * How_Many_process,int *countOfLetter,int countOfWords); // the method will calculate how many words we entered through the string
void TheNumberOfLettersInEachWord(const char str[],char temp[],char ** Command,int * How_Many_process,int * countOfLetter);// this method will cut the sentence into words and calculate how many letters are in them
void freeDynamicAllocation(char** Command,int countOfWords);// this method free's the memory of all alloc
void Process(char** Command,int * How_Many_process,int * countOfLetter,int countOfWords);// this method will take the Shell command and activate it
void Prompt(int * How_Many_process,int * countOfLetter);//this method will get the Prompt
int main()
{
    char str[MAX];// String we want to enter by use fgets
    char temp[MAX]; //temp string
    char sched[MAX+2];
    int * How_Many_process=(int *)malloc(sizeof(int));
    int * countOfLetter=(int *)malloc(sizeof(int));
    if (How_Many_process == NULL||countOfLetter== NULL) // condition If dynamic allocation failed
    {
        if(How_Many_process!=NULL) free(How_Many_process);//free it if succeeded
        if(countOfLetter!=NULL) free(countOfLetter);//free it if succeeded
        fprintf(stderr,"malloc failed");
        exit(1);// exit the code
    }
    *How_Many_process=*countOfLetter=0;
    int countOfWords;
    for(;;) {//takes command from the user
        Prompt(How_Many_process,countOfLetter);
        if(fgets(str, MAX, stdin)==NULL) {// Checks if the String we enter it was NULL
            fprintf(stderr,"the fgets is failed\n");
            continue;
        }
        str[strlen(str) - 1] = '\0';
        countOfWords=howManyWords(str,How_Many_process,countOfLetter,0);
        if(countOfWords==0) continue;
        char** Command;
        Command= malloc((countOfWords+1)*sizeof(char*));
        if(Command==NULL){// condition If dynamic allocation failed
            free(How_Many_process);
            free(countOfLetter);
            fprintf(stderr,"malloc failed");
            exit(1);// exit the code
        }
        TheNumberOfLettersInEachWord(str, temp, Command, How_Many_process, countOfLetter);
        if ((strcmp(Command[0], "done") == 0) && (countOfWords == 1)) {//if the user enter the word done ,the program will exit and show how many process, count of letters , Average length of all commands,and the massage
            printf("Num of command: %d\n", *How_Many_process);
            printf("Total length of all commands: %d\n", *countOfLetter);
            printf("Average length of all commands: %lf\n", (double) (*countOfLetter) / (*How_Many_process));
            printf("See you Next time !");
            freeDynamicAllocation(Command, countOfWords);
            free(How_Many_process);
            free(countOfLetter);
            exit(0);
        }
        if (strcmp(Command[0], "cd") == 0) {//if the user enter the word cd this will show and continue
            fprintf(stderr, "command not supported (Yet)\n");
            freeDynamicAllocation(Command, countOfWords);
            continue;
        }
        Process(Command,How_Many_process,countOfLetter,countOfWords);
        strcpy(sched, "");
    }
}
int howManyWords(const char str[],int * How_Many_process,int *countOfLetter,int countOfWords) { // the method will calculate how many words we entered through the string
    int i;
    (*How_Many_process)++;
    for (i = 0; str[i] != '\0'; i++) {// this Loop count how many words in the String
        if (str[i] != ' ' && (str[i+1] == ' ' || str[i+ 1] == '\0')) {// this condition checks  if the char is not a space and the char after it is a space or the end of sentence
            countOfWords++;
        }
        if(str[i]!='\0')
            (*countOfLetter)++;
    }
    return countOfWords;
}
void TheNumberOfLettersInEachWord(const char str[], char temp[], char ** Command,int * How_Many_process,int * countOfLetter) {// this method will cut the sentence into words and calculate how many letters are in them
    strcpy(temp, "");
    int counter = 0;
    int Index=0;
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
            Command[Index] = (char *) malloc(sizeof(char) * (counter + 1));// array there length is the char size * (the size of the temp+1('\0'))
            if (Command[Index] == NULL) // condition If dynamic allocation failed
            {
                fprintf(stderr,"malloc failed");
                freeDynamicAllocation(Command,Index);
                free(How_Many_process);
                free(countOfLetter);
                exit(1);// exit the code
            }
            strcpy(Command[Index], temp);// copy from temp to word
            counter = 0;
            k = 0;
            Index++;
            strcpy(temp, "");// rest
        }
    }
    Command[Index]=NULL;
}
void freeDynamicAllocation(char** Command,int countOfWords){// this method free's the memory of all alloc
    int i;
    for(i=0;i<(countOfWords);i++){
        free(Command[i]);
    }
    free(Command);
}
void  Process(char** Command,int * How_Many_process,int * countOfLetter,int countOfWords){// this method will take the Shell command and activate it
    pid_t child1;
    child1 = fork();/* fork another process */
    if (child1 < 0) { /* error occurred */
        perror("folk filed");
        exit(1);
    } else if (child1 == 0) { /* child process */
            execvp(Command[0], Command);//does the function in the Command String
            perror("command not found");
            freeDynamicAllocation(Command, countOfWords);
            free(How_Many_process);
            free(countOfLetter);
            exit(1);
    } else { /* parent process */
        wait(NULL);/* parent will wait for the child */
        freeDynamicAllocation(Command,countOfWords);
    }
}
void Prompt(int * How_Many_process,int * countOfLetter){//this method will get the Prompt
    struct passwd *p;
    uid_t  uid=0;
    char  directory [MAX+2];
    int check;
    check=1;
    if ((p = getpwuid(uid)) == NULL) {// this method get the user name and check if not NULL
        check=-1;
    }
    if (getcwd(directory , sizeof(directory)) == NULL) {//this method get the root(directory) and check if not NULL
        perror("getcwd() error");
        free(How_Many_process);
        free(countOfLetter);
        exit(1);
    }
    if(check==-1)// if the user name is null
        printf("%s@%s>", "null",directory);
    else
        printf("%s@%s>", p->pw_name,directory);// print the Prompt
}
