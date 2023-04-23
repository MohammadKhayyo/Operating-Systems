
#include <sys/types.h>
#include <stdio.h>
#include "string.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pwd.h>
#define MAX 511// length of the String
void FreeIfFailed(int * How_Many_process,int * HowManyPipes);//method that makes both pointer free before the exit If the system call or dynamic assignment unsuccessful
void Prompt(int * How_Many_process,int * HowManyPipes);//this method will get the Prompt
int howManyQuotes(const char str[]);//method that calculates how many Quotes there are
int howManyWords(const char str[], int countOfWords); // the method will calculate how many words we entered through the string
void freeDynamicAllocation(char** Command,int countOfWords);// this method free's the memory of all alloc
void TheNumberOfLettersInEachWord(const char str[],char temp[],char ** Command,int * How_Many_process,int * HowManyPipes);// this method will cut the sentence into words and calculate how many letters are in them
int thePlaceOfOnePipes(const char str[]);//method that returns the first index of Pipes if any
int thePlaceOfSecondPipes(const char str[]);//method that returns the Second index of Pipes if any
void FreeMallocForOnePipes(char **FirstCommand, char **SecondCommand,char* theFirstArray,char* theSecondArray,int countOfWords,int countOfWords2);//method that frees pointers if the system call or dynamic assignment failed
void ProcessForOnePipes(char **FirstCommand, char **SecondCommand,char theFirstArray[],char theSecondArray[],int * How_Many_process,int * HowManyPipes,int countOfWords,int countOfWords2);//this method will take the Shell command and activate it if there is only one pipe
void FreeForString(char * theFirstArray,char * theSecondArray,char * theThirdArray);//Makes free for dynamic assignment of the strings we have created
void FillTheStringsForOnePipe(const char str[],char temp[],char * theFirstArray,char* theSecondArray);//method that fills two strings if there is only one pipe ,Before the pipe in the string and what is after it in another string
void TreatmentForOnePipe(char str[],char temp[],int * How_Many_process,int * HowManyPipes);//It makes two strings and sends them to the FillTheStringsForOnePipe function And the purpose of it is to check whether there is an empty command
void FillTheStringsForTwoPipes(const char str[],char temp[],char theFirstArray[],char theSecondArray[], char theThirdArray[]);//method that fills two strings if there are only two pipes, Before the pipe in the string and what is after the pipe up to the second pipe in the second string and what is after the second pipe in another string
void FreeMallocForTwoPipes(char **FirstCommand, char **SecondCommand,char ** ThirdCommand,char* theFirstArray,char* theSecondArray,char* theThirdArray,int countOfWords,int countOfWords2,int countOfWords3 );//method that frees pointers if the system call or dynamic assignment failed
void ProcessForTwoPipes(char **FirstCommand, char **SecondCommand,char ** ThirdCommand,char* theFirstArray,char* theSecondArray,char* theThirdArray,int * How_Many_process,int * HowManyPipes,int countOfWords,int countOfWords2,int countOfWords3);//this method will take the Shell command and activate it if there are only two pipes
void closePiPes( int pipe_fd[2],int pipe_fd2[2],char **FirstCommand, char **SecondCommand,char ** ThirdCommand,char* theFirstArray,char* theSecondArray,char* theThirdArray,int * How_Many_process,int * HowManyPipes,int countOfWords,int countOfWords2,int countOfWords3);//method that closes the open file descriptor entries
void TreatmentForTwoPipe(char str[],char temp[],int * How_Many_process,int * HowManyPipes);//It makes three strings and sends them to the FillTheStringsForTwoPipes function And the purpose of it is to check whether there is an empty command
void ProcessForNonePipes(char** Command,int * How_Many_process,int * HowManyPipes,int countOfWords);//this method will take the Shell command and activate it  if it did not have Pipes
int howManyPipes(const char str[]);//method that calculates how many Pipes there are
void ProcessingForCommand(char str[],char temp[],int * How_Many_process,int * HowManyPipes);//method that picks up a string from the user and according to the pipe number it will refer it to the appropriate method
int main()
{
    char str[MAX];// String we want to enter by use fgets
    char temp[MAX]; //temp string
    int * How_Many_process=(int *)malloc(sizeof(int));// to count Total pipes in all commands
    int * HowManyPipes=(int *)malloc(sizeof(int));// counter Num of commands
    if (How_Many_process == NULL||HowManyPipes== NULL) // condition If dynamic allocation failed
    {
        if(How_Many_process!=NULL) free(How_Many_process);//free it if succeeded
        if(HowManyPipes!=NULL) free(HowManyPipes);//free it if succeeded
        fprintf(stderr,"malloc failed");
        exit(EXIT_FAILURE);// exit the code
    }
    *How_Many_process=*HowManyPipes=0;
    ProcessingForCommand(str,temp,How_Many_process,HowManyPipes);
}
void FreeIfFailed(int * How_Many_process,int * HowManyPipes){//method that makes both pointer free before the exit If the system call or dynamic assignment unsuccessful
    free(HowManyPipes);
    free(How_Many_process);
    exit(EXIT_FAILURE);
}
void Prompt(int * How_Many_process,int * HowManyPipes){//this method will get the Prompt
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
        FreeIfFailed(How_Many_process,HowManyPipes);
    }
    if(check==-1)// if the user name is null
        printf("%s@%s>", "null",directory);
    else
        printf("%s@%s>", p->pw_name,directory);// print the Prompt
}
int howManyQuotes(const char str[]){//method that calculates how many Quotes there is
    int i, countOfQuotes=0;
    for (i=0; str[i] !='\0' ; i++) {
        if(str[i] == '"'){
            countOfQuotes++;
        }
    }
    return countOfQuotes;
}
int howManyWords(const char str[], int countOfWords) { //the method will calculate how many words we entered through the string
    int i,j;
    int countOfQuotes=howManyQuotes(str);
    for (i = 0; str[i] != '\0';) {// this Loop count how many words in the String
        if(countOfQuotes==2 && str[i]=='"') {// this condition if we have two ' " '
            for (j = i + 1; str[j] != '\0'; j++) {
                if (str[j] == '"') {
                    i = j;
                    break;
                }
            }
        }
        if (str[i] != ' ' && (str[i + 1] == ' ' || str[i+1] == '\0')  ){// in this condition we count how many words
            countOfWords++;
        }
        i++;
    }
    return countOfWords;
}
void freeDynamicAllocation(char** Command,int countOfWords){// this method free's the memory of all alloc
    int i;
    for(i=0;i<(countOfWords);i++){
        free(Command[i]);
    }
    free(Command);
}
void TheNumberOfLettersInEachWord(const char str[], char temp[], char ** Command,int * How_Many_process,int * HowManyPipes) {// this method will cut the sentence into words and calculate how many letters are in them
    strcpy(temp, "");
    int counter = 0;
    int Index=0;
    int k = 0;// use k  to move on temp indexes
    int i,j;
    int countOfQuotes=howManyQuotes(str);
    for (i = 0; str[i] != '\0'; i++) {// this loop will cut the sentence into words and calculate how many letters are in them
        if (str[i] != ' ') {// this condition will check if the char is not equal to space
            if(countOfQuotes==2 && str[i]=='"'){// this condition if we have two ' " '
                for(j=i+1;str[j]!='\0';j++){
                    if(str[j]=='"'){
                        i=j;
                        break;
                    }
                    counter++;
                    temp[k] = str[j];//put the char in temp
                    k++;
                }
            }
            else {
                counter++;
                temp[k] = str[i];//put the char in temp
                k++;
            }
        }
        if (str[i] != ' ' && (str[i + 1] == ' ' || str[i + 1] == '\0')) {// this condition checks  if the char is not a space and the char after it is a space or the end of sentence
            temp[k] = '\0';//will mark the end of a temp
            Command[Index] = (char *) malloc(sizeof(char) * (counter + 1));// array there length is the char size * (the size of the temp+1('\0'))
            if (Command[Index] == NULL) // condition If dynamic allocation failed
            {
                fprintf(stderr,"malloc failed");
                freeDynamicAllocation(Command,Index);
                FreeIfFailed(How_Many_process,HowManyPipes);
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
int thePlaceOfOnePipes(const char str[]){//method that returns the first index of Pipes if any
    int i,OnePipes=0;
    for(i=0;str[i]!='\0';i++){
        if(str[i]=='|'){
            OnePipes=i;
            break;
        }
    }
    return OnePipes;
}
int thePlaceOfSecondPipes(const char str[]){//method that returns the Second index of Pipes if any
    int i=thePlaceOfOnePipes(str)+1;//will save the index after the Pipe
    int SecondPipes=0;
    for(;str[i]!='\0';i++){
        if(str[i]=='|'){
            SecondPipes=i;
            break;
        }
    }
    return SecondPipes;
}
void FreeMallocForOnePipes(char **FirstCommand, char **SecondCommand,char* theFirstArray,char* theSecondArray,int countOfWords,int countOfWords2){//method that frees pointers if the system call or dynamic assignment failed
    freeDynamicAllocation(FirstCommand,countOfWords);
    freeDynamicAllocation(SecondCommand,countOfWords2);
    free(theFirstArray);
    free(theSecondArray);
}
void ProcessForOnePipes(char **FirstCommand, char **SecondCommand,char theFirstArray[],char theSecondArray[],int * How_Many_process,int * HowManyPipes,int countOfWords,int countOfWords2){//this method will take the Shell command and activate it if there is only one pipe
    int pipe_fd[2];
    pid_t BeforePipe, AfterPipe;//two children
    if (strcmp(FirstCommand[0], "cd") == 0 ||strcmp(SecondCommand[0], "cd") == 0 ) {//if user enter cd
        fprintf(stderr, "command not supported (Yet)\n");// print not support
        FreeMallocForOnePipes(FirstCommand,SecondCommand, theFirstArray, theSecondArray, countOfWords, countOfWords2);
    }
    else{
        if(pipe(pipe_fd)==-1){/* error occurred */
            perror("pipe field");
            FreeMallocForOnePipes(FirstCommand,SecondCommand, theFirstArray, theSecondArray, countOfWords, countOfWords2);
            FreeIfFailed(How_Many_process,HowManyPipes);
        }
        BeforePipe = fork();
        if(BeforePipe==-1){/* error occurred */
            perror("folk failed");
            FreeMallocForOnePipes(FirstCommand,SecondCommand, theFirstArray, theSecondArray, countOfWords, countOfWords2);
            FreeIfFailed(How_Many_process,HowManyPipes);
        }
        else if(BeforePipe==0){/* son process */
            if(dup2(pipe_fd[1], STDOUT_FILENO)==-1){// pipe_fd is the file descriptor of stdout
                fprintf(stderr,"dup2 failed\n");
                FreeMallocForOnePipes(FirstCommand,SecondCommand, theFirstArray, theSecondArray, countOfWords, countOfWords2);
                FreeIfFailed(How_Many_process,HowManyPipes);
            }
            if(close(pipe_fd[0])==-1||close(pipe_fd[1])==-1){// close the input // close the output
                perror("close field");
                FreeMallocForOnePipes(FirstCommand,SecondCommand, theFirstArray, theSecondArray, countOfWords, countOfWords2);
                FreeIfFailed(How_Many_process,HowManyPipes);
            }
            execvp(FirstCommand[0], FirstCommand);// send the command to system call to run then send it to output of to pipe
            perror("command not found");
            FreeMallocForOnePipes(FirstCommand,SecondCommand, theFirstArray, theSecondArray, countOfWords, countOfWords2);
            FreeIfFailed(How_Many_process,HowManyPipes);
        }
        else{
            AfterPipe=fork();
            if(AfterPipe==-1){/* error occurred */
                perror("folk failed");
                FreeMallocForOnePipes(FirstCommand,SecondCommand, theFirstArray, theSecondArray, countOfWords, countOfWords2);
                FreeIfFailed(How_Many_process,HowManyPipes);
            }
            else if(AfterPipe==0){/* son process */
                if(dup2(pipe_fd[0], STDIN_FILENO)==-1){// pipe_fd is the file descriptor of stdin
                    fprintf(stderr,"dup2 failed\n");
                    FreeMallocForOnePipes(FirstCommand,SecondCommand, theFirstArray, theSecondArray, countOfWords, countOfWords2);
                    FreeIfFailed(How_Many_process,HowManyPipes);
                }
                if(close(pipe_fd[0])==-1||close(pipe_fd[1])==-1){// close the input // close the output
                    perror("close field");
                    FreeMallocForOnePipes(FirstCommand,SecondCommand, theFirstArray, theSecondArray, countOfWords, countOfWords2);
                    FreeIfFailed(How_Many_process,HowManyPipes);
                }
                execvp(SecondCommand[0], SecondCommand);// receive the input from Pipe then sent it to system call to run
                perror("command not found");
                FreeMallocForOnePipes(FirstCommand,SecondCommand, theFirstArray, theSecondArray, countOfWords, countOfWords2);
                FreeIfFailed(How_Many_process,HowManyPipes);
            }
            else{
                if(close(pipe_fd[0])==-1||close(pipe_fd[1])==-1){// close the input // close the output
                    perror("close field");
                    FreeMallocForOnePipes(FirstCommand,SecondCommand, theFirstArray, theSecondArray, countOfWords, countOfWords2);
                    FreeIfFailed(How_Many_process,HowManyPipes);
                }
                wait(NULL);
                wait(NULL);// wait for the two sons process
                FreeMallocForOnePipes(FirstCommand,SecondCommand, theFirstArray, theSecondArray, countOfWords, countOfWords2);
            }
        }
    }
}
void FreeForString(char * theFirstArray,char * theSecondArray,char * theThirdArray){//Makes free for dynamic assignment of the strings we have created
    if(theFirstArray!=NULL) free(theFirstArray);
    if(theSecondArray!=NULL) free(theSecondArray);
    if(theThirdArray!=NULL) free(theThirdArray);
}
void FillTheStringsForOnePipe(const char str[],char temp[],char * theFirstArray,char* theSecondArray){//method that fills two strings if there is only one pipe ,Before the pipe in the string and what is after it in another string
    int i;
    int savePipe=0;
    int j=0;
    strcpy(temp,"");
    for(i=0;str[i]!='\0';i++){
        if(str[i]=='|') {
            savePipe=i;
            break;
        }
        temp[j]=str[i];//put the char in temp
        j++;
    }
    temp[j]='\0';
    strcpy(theFirstArray,temp);
    strcpy(temp,"");
    j=0;
    for(i=savePipe+1;str[i]!='\0';i++){
        temp[j]=str[i];//put the char in temp
        j++;
    }
    temp[j]='\0';
    strcpy(theSecondArray,temp);
    strcpy(temp,"");
}
void TreatmentForOnePipe(char str[],char temp[],int * How_Many_process,int * HowManyPipes){//It makes two strings and sends them to the FillTheStringsForOnePipe function And the purpose of it is to check whether there is an empty command
    int countOfWords, countOfWords2;
    char* theFirstArray;
    char* theSecondArray;
    int thePlaceOfTheFirstPipe=thePlaceOfOnePipes(str);//save the first index of the Pipes
    theFirstArray = (char *) malloc(sizeof(char) * (thePlaceOfTheFirstPipe+1));// malloc
    if(theFirstArray==NULL) {//malloc filed
        fprintf(stderr,"malloc failed");
        FreeIfFailed(How_Many_process,HowManyPipes);
    }
    theSecondArray = (char *) malloc(sizeof(char) * (strlen(str)-thePlaceOfTheFirstPipe));//malloc
    if(theSecondArray==NULL) {//malloc filed
        fprintf(stderr,"malloc failed");
        FreeForString(theFirstArray,NULL,NULL);
        FreeIfFailed(How_Many_process,HowManyPipes);
    }
    FillTheStringsForOnePipe(str, temp, theFirstArray, theSecondArray);
    countOfWords = howManyWords(theFirstArray, 0);//save how many word in theFirstArray
    if(countOfWords==0) {// if count of word in theFirstArray is zero
        (*How_Many_process)--;
        (*HowManyPipes)=(*HowManyPipes)-1;
        fprintf(stderr, "syntax error near unexpected token\n");
        FreeForString(theFirstArray,theSecondArray,NULL);
        return;
    }
    char **FirstCommand;
    FirstCommand = malloc((countOfWords + 1) * sizeof(char *));//malloc
    if(FirstCommand==NULL){//malloc filed
        fprintf(stderr,"malloc failed");
        FreeForString(theFirstArray,theSecondArray,NULL);
        FreeIfFailed(How_Many_process,HowManyPipes);
    }
    TheNumberOfLettersInEachWord(theFirstArray,temp, FirstCommand,How_Many_process,HowManyPipes);
    countOfWords2 = howManyWords(theSecondArray, 0);
    if(countOfWords2==0) {// if count of word in theSecondArray is zero
        (*How_Many_process)--;
        (*HowManyPipes)=(*HowManyPipes)-1;
        FreeForString(theFirstArray,theSecondArray,NULL);
        freeDynamicAllocation(FirstCommand,countOfWords);
        return;
    }
    char **SecondCommand;
    SecondCommand = malloc((countOfWords2 + 1) * sizeof(char *));//malloc
    if(SecondCommand==NULL){//malloc filed
        fprintf(stderr,"malloc failed");
        FreeForString(theFirstArray,theSecondArray,NULL);
        freeDynamicAllocation(FirstCommand,countOfWords);
        FreeIfFailed(How_Many_process,HowManyPipes);
    }
    TheNumberOfLettersInEachWord(theSecondArray,temp, SecondCommand,How_Many_process,HowManyPipes);
    ProcessForOnePipes(FirstCommand,SecondCommand,theFirstArray,theSecondArray,How_Many_process,HowManyPipes,countOfWords,countOfWords2);
}
void FillTheStringsForTwoPipes(const char str[],char temp[],char theFirstArray[],char theSecondArray[], char theThirdArray[]){//method that fills two strings if there are only two pipes, Before the pipe in the string and what is after the pipe up to the second pipe in the second string and what is after the second pipe in another string
    int i;
    int savePipe=0;
    int j=0;
    strcpy(temp,"");
    for(i=0;str[i]!='\0';i++){
        if(str[i]=='|') {
            break;
        }
        temp[j]=str[i];//put the char in temp
        j++;
    }
    temp[j]='\0';
    strcpy(theFirstArray,temp);
    strcpy(temp,"");
    j=0;
    char *ret;
    ret = strchr(str,  '|');
    for(i=1;ret[i]!='\0';i++){
        if(ret[i]=='|') {
            savePipe=i;
            break;
        }
        temp[j]=ret[i];//put the char in temp
        j++;
    }
    temp[j]='\0';
    strcpy(theSecondArray,temp);
    strcpy(temp,"");
    j=0;
    for(i=savePipe+1;ret[i]!='\0';i++){
        temp[j]=ret[i];//put the char in temp
        j++;
    }
    temp[j]='\0';
    strcpy(theThirdArray,temp);
    strcpy(temp,"");
}
void FreeMallocForTwoPipes(char **FirstCommand, char **SecondCommand,char ** ThirdCommand,char* theFirstArray,char* theSecondArray,char* theThirdArray,int countOfWords,int countOfWords2,int countOfWords3 ){//method that frees pointers if the system call or dynamic assignment failed
    freeDynamicAllocation(FirstCommand,countOfWords);
    freeDynamicAllocation(SecondCommand,countOfWords2);
    freeDynamicAllocation(ThirdCommand,countOfWords3);
    free(theFirstArray);
    free(theSecondArray);
    free(theThirdArray);
}
void ProcessForTwoPipes(char **FirstCommand, char **SecondCommand,char ** ThirdCommand,char* theFirstArray,char* theSecondArray,char* theThirdArray,int * How_Many_process,int * HowManyPipes,int countOfWords,int countOfWords2,int countOfWords3){//this method will take the Shell command and activate it if there are only two pipes
    int pipe_fd[2],pipe_fd2[2];// two pipes
    pid_t BeforePipe, AfterPipe,AfterSecondPipe;//three children
    if (strcmp(FirstCommand[0], "cd") == 0 ||strcmp(SecondCommand[0], "cd") == 0 ||strcmp(ThirdCommand[0], "cd") == 0 ) {//if user enter cd
        fprintf(stderr, "command not supported (Yet)\n");// print not support
        FreeMallocForTwoPipes(FirstCommand, SecondCommand,ThirdCommand,theFirstArray,theSecondArray,theThirdArray,countOfWords,countOfWords2,countOfWords3 );
    }
    else{
        if (pipe(pipe_fd) ==-1){/* error occurred */
            perror("pipe field");
            FreeMallocForTwoPipes(FirstCommand, SecondCommand,ThirdCommand,theFirstArray,theSecondArray,theThirdArray,countOfWords,countOfWords2,countOfWords3 );
            FreeIfFailed(How_Many_process,HowManyPipes);
        }
        if (pipe(pipe_fd2) ==-1){/* error occurred */
            perror("pipe field");
            FreeMallocForTwoPipes(FirstCommand, SecondCommand,ThirdCommand,theFirstArray,theSecondArray,theThirdArray,countOfWords,countOfWords2,countOfWords3 );
            FreeIfFailed(How_Many_process,HowManyPipes);
        }
        BeforePipe = fork();
        if(BeforePipe==-1){/* error occurred */
            perror("folk failed");
            FreeMallocForTwoPipes(FirstCommand, SecondCommand,ThirdCommand,theFirstArray,theSecondArray,theThirdArray,countOfWords,countOfWords2,countOfWords3 );
            FreeIfFailed(How_Many_process,HowManyPipes);
        }
        else if(BeforePipe==0){/* son process */
            if(dup2(pipe_fd[1], STDOUT_FILENO)==-1){// pipe_fd is the file descriptor of stdout
                fprintf(stderr,"dup2 failed\n");
                FreeMallocForTwoPipes(FirstCommand, SecondCommand,ThirdCommand,theFirstArray,theSecondArray,theThirdArray,countOfWords,countOfWords2,countOfWords3 );
                FreeIfFailed(How_Many_process,HowManyPipes);
            }
            closePiPes( pipe_fd,pipe_fd2,FirstCommand,SecondCommand,ThirdCommand, theFirstArray, theSecondArray, theThirdArray, How_Many_process,HowManyPipes,countOfWords,countOfWords2,countOfWords3);
            execvp(FirstCommand[0], FirstCommand);// send the command to system call to run then send it to output of to pipe
            perror("command not found");
            FreeMallocForTwoPipes(FirstCommand, SecondCommand,ThirdCommand,theFirstArray,theSecondArray,theThirdArray,countOfWords,countOfWords2,countOfWords3 );
            FreeIfFailed(How_Many_process,HowManyPipes);
        }
        else{
            AfterPipe=fork();
            if(AfterPipe==-1){/* error occurred */
                perror("folk failed");
                FreeMallocForTwoPipes(FirstCommand, SecondCommand,ThirdCommand,theFirstArray,theSecondArray,theThirdArray,countOfWords,countOfWords2,countOfWords3 );
                FreeIfFailed(How_Many_process,HowManyPipes);
            }
            else if(AfterPipe==0){/* son process */
                if(dup2(pipe_fd[0], STDIN_FILENO)==-1){// pipe_fd is the file descriptor of stdin
                    fprintf(stderr,"dup2 failed\n");
                    FreeMallocForTwoPipes(FirstCommand, SecondCommand,ThirdCommand,theFirstArray,theSecondArray,theThirdArray,countOfWords,countOfWords2,countOfWords3 );
                    FreeIfFailed(How_Many_process,HowManyPipes);
                }
                if(dup2(pipe_fd2[1], STDOUT_FILENO)==-1){// pipe_fd2 is the file descriptor of stdout
                    fprintf(stderr,"dup2 failed\n");
                    FreeMallocForTwoPipes(FirstCommand, SecondCommand,ThirdCommand,theFirstArray,theSecondArray,theThirdArray,countOfWords,countOfWords2,countOfWords3 );
                    FreeIfFailed(How_Many_process,HowManyPipes);
                }
                closePiPes( pipe_fd,pipe_fd2,FirstCommand,SecondCommand,ThirdCommand, theFirstArray, theSecondArray, theThirdArray, How_Many_process,HowManyPipes,countOfWords,countOfWords2,countOfWords3);
                execvp(SecondCommand[0], SecondCommand);// receive the input from Pipe then sent it to system call to run then send it to output of pipe
                perror("command not found");
                FreeMallocForTwoPipes(FirstCommand, SecondCommand,ThirdCommand,theFirstArray,theSecondArray,theThirdArray,countOfWords,countOfWords2,countOfWords3 );
                FreeIfFailed(How_Many_process,HowManyPipes);
            }
            else{
                AfterSecondPipe=fork();
                if(AfterSecondPipe==-1){/* error occurred */
                    perror("folk failed");
                    FreeMallocForTwoPipes(FirstCommand, SecondCommand,ThirdCommand,theFirstArray,theSecondArray,theThirdArray,countOfWords,countOfWords2,countOfWords3 );
                    FreeIfFailed(How_Many_process,HowManyPipes);
                }
                else if(AfterSecondPipe==0){/* son process */
                    if(dup2(pipe_fd2[0], STDIN_FILENO)==-1){
                        fprintf(stderr,"dup2 failed\n");
                        FreeMallocForTwoPipes(FirstCommand, SecondCommand,ThirdCommand,theFirstArray,theSecondArray,theThirdArray,countOfWords,countOfWords2,countOfWords3 );
                        FreeIfFailed(How_Many_process,HowManyPipes);
                    }
                    closePiPes( pipe_fd,pipe_fd2,FirstCommand,SecondCommand,ThirdCommand, theFirstArray, theSecondArray, theThirdArray, How_Many_process,HowManyPipes,countOfWords,countOfWords2,countOfWords3);
                    execvp(ThirdCommand[0], ThirdCommand);
                    perror("command not found");
                    FreeMallocForTwoPipes(FirstCommand, SecondCommand,ThirdCommand,theFirstArray,theSecondArray,theThirdArray,countOfWords,countOfWords2,countOfWords3 );
                    FreeIfFailed(How_Many_process,HowManyPipes);
                }
                else{
                    closePiPes( pipe_fd,pipe_fd2,FirstCommand,SecondCommand,ThirdCommand, theFirstArray, theSecondArray, theThirdArray, How_Many_process,HowManyPipes,countOfWords,countOfWords2,countOfWords3);
                    wait(NULL);
                    wait(NULL);
                    wait(NULL);
                    FreeMallocForTwoPipes(FirstCommand, SecondCommand,ThirdCommand,theFirstArray,theSecondArray,theThirdArray,countOfWords,countOfWords2,countOfWords3 );
                }
            }
        }
    }
}
void closePiPes( int pipe_fd[2],int pipe_fd2[2],char **FirstCommand, char **SecondCommand,char ** ThirdCommand,char* theFirstArray,char* theSecondArray,char* theThirdArray,int * How_Many_process,int * HowManyPipes,int countOfWords,int countOfWords2,int countOfWords3){//method that closes the open file descriptor entries
    if(close(pipe_fd[0])==-1||close(pipe_fd[1])==-1||close(pipe_fd2[0])==-1||close(pipe_fd2[1])==-1){/* error occurred */
        perror("close field");
        FreeMallocForTwoPipes(FirstCommand, SecondCommand,ThirdCommand,theFirstArray,theSecondArray,theThirdArray,countOfWords,countOfWords2,countOfWords3 );
        FreeIfFailed(How_Many_process,HowManyPipes);
    }
}
void TreatmentForTwoPipe(char str[],char temp[],int * How_Many_process,int * HowManyPipes)//It makes three strings and sends them to the FillTheStringsForTwoPipes function And the purpose of it is to check whether there is an empty command
{
    int countOfWords, countOfWords2,countOfWords3;
    char* theFirstArray;
    char* theSecondArray;
    char* theThirdArray;
    theFirstArray = (char *) malloc(sizeof(char) * (thePlaceOfOnePipes(str)+1));//malloc
    if(theFirstArray==NULL) {//malloc filed
        fprintf(stderr,"malloc failed");
        FreeIfFailed(How_Many_process,HowManyPipes);
    }
    theSecondArray = (char *) malloc(sizeof(char) * (thePlaceOfSecondPipes(str)-thePlaceOfOnePipes(str)));//malloc
    if(theSecondArray==NULL) {//malloc filed
        fprintf(stderr,"malloc failed");
        FreeForString(theFirstArray,NULL,NULL);
        FreeIfFailed(How_Many_process,HowManyPipes);
    }
    theThirdArray = (char *) malloc(sizeof(char) * (strlen(str)-thePlaceOfSecondPipes(str)));//malloc
    if(theThirdArray==NULL){//malloc filed
        fprintf(stderr,"malloc failed");
        FreeForString(theFirstArray,theSecondArray,NULL);
        FreeIfFailed(How_Many_process,HowManyPipes);
    }
    FillTheStringsForTwoPipes(str, temp, theFirstArray, theSecondArray, theThirdArray);
    countOfWords = howManyWords(theFirstArray, 0);
    if(countOfWords==0) {// if count of word in theFirstArray is zero
        (*How_Many_process)--;
        (*HowManyPipes)=(*HowManyPipes)-2;
        fprintf(stderr, "syntax error near unexpected token\n");
        FreeForString(theFirstArray,theSecondArray,theThirdArray);
        return;
    }
    char **FirstCommand;
    FirstCommand = malloc((countOfWords + 1) * sizeof(char *));//malloc
    if(FirstCommand==NULL){//malloc filed
        fprintf(stderr,"malloc failed");
        FreeForString(theFirstArray,theSecondArray,theThirdArray);
        FreeIfFailed(How_Many_process,HowManyPipes);
    }
    TheNumberOfLettersInEachWord(theFirstArray,temp, FirstCommand,How_Many_process,HowManyPipes);
    countOfWords2 = howManyWords(theSecondArray, 0);
    if(countOfWords2==0) {// if count of word in theSecondArray is zero
        (*How_Many_process)--;
        (*HowManyPipes)=(*HowManyPipes)-2;
        FreeForString(theFirstArray,theSecondArray,theThirdArray);
        freeDynamicAllocation(FirstCommand,countOfWords);
        return;
    }
    char **SecondCommand;
    SecondCommand = malloc((countOfWords2 + 1) * sizeof(char *));//malloc
    if(SecondCommand==NULL){//malloc filed
        fprintf(stderr,"malloc failed");
        FreeForString(theFirstArray,theSecondArray,theThirdArray);
        freeDynamicAllocation(FirstCommand,countOfWords);
        FreeIfFailed(How_Many_process,HowManyPipes);
    }
    TheNumberOfLettersInEachWord(theSecondArray,temp, SecondCommand,How_Many_process,HowManyPipes);
    countOfWords3 = howManyWords(theThirdArray, 0);
    if(countOfWords3==0) {// if count of word in theThirdArray is zero
        (*How_Many_process)--;
        (*HowManyPipes)=(*HowManyPipes)-2;
        FreeForString(theFirstArray,theSecondArray,theThirdArray);
        freeDynamicAllocation(FirstCommand,countOfWords);
        freeDynamicAllocation(SecondCommand,countOfWords2);
        return;
    }
    char **ThirdCommand;
    ThirdCommand = malloc((countOfWords3 + 1) * sizeof(char *));//malloc
    if(ThirdCommand==NULL){//malloc filed
        fprintf(stderr,"malloc failed");
        FreeForString(theFirstArray,theSecondArray,theThirdArray);
        freeDynamicAllocation(FirstCommand,countOfWords);
        freeDynamicAllocation(SecondCommand,countOfWords2);
        FreeIfFailed(How_Many_process,HowManyPipes);
    }
    TheNumberOfLettersInEachWord(theThirdArray,temp, ThirdCommand,How_Many_process,HowManyPipes);
    ProcessForTwoPipes(FirstCommand,SecondCommand, ThirdCommand, theFirstArray, theSecondArray, theThirdArray, How_Many_process, HowManyPipes, countOfWords,countOfWords2,countOfWords3);
}
void  ProcessForNonePipes(char** Command,int * How_Many_process,int * HowManyPipes,int countOfWords){//this method will take the Shell command and activate it  if it did not have Pipes
    pid_t child1;
    child1 = fork();/* fork another process */
    if (child1 < 0) { /* error occurred */
        perror("folk filed");
        exit(EXIT_FAILURE);
    } else if (child1 == 0) { /* child process */
        execvp(Command[0], Command);//does the function in the Command String
        perror("command not found");
        freeDynamicAllocation(Command, countOfWords);
        FreeIfFailed(How_Many_process,HowManyPipes);
    } else { /* parent process */
        wait(NULL);/* parent will wait for the child */
        freeDynamicAllocation(Command,countOfWords);
    }
}
int howManyPipes(const char str[]){//method that calculates how many Pipes there are
    int i,counter=0;
    for(i=0;str[i]!='\0';i++)
        if(str[i]=='|')
            counter++;

    return counter;
}
void ProcessingForCommand(char str[],char temp[],int * How_Many_process,int * HowManyPipes){//method that picks up a string from the user and according to the pipe number it will refer it to the appropriate method
    int countOfWords,numberOfPipes;
    for(;;) {//takes command from the user
        Prompt(How_Many_process, HowManyPipes);
        if (fgets(str, MAX, stdin) == NULL) {// Checks if the String we enter it was NULL
            fprintf(stderr, "the fgets is failed\n");
            continue;
        }
        str[strlen(str) - 1] = '\0';
        (*How_Many_process)++;
        numberOfPipes = howManyPipes(str);//save the number of Pipes
        *(HowManyPipes)=*(HowManyPipes)+numberOfPipes;//Increase the number of Pipes according to the amount of Pipes we received
        if (numberOfPipes == 1) {//If the number of the Pipe in the string we received is equal to one
            TreatmentForOnePipe(str, temp,How_Many_process,HowManyPipes);
        } else if (numberOfPipes == 2) {//If the number of the Pipe in the string we received is equal to two
            TreatmentForTwoPipe(str,temp,How_Many_process,HowManyPipes);
        }else if(numberOfPipes>=3){//If the number of the Pipe in the string we received is equal or greater than three
            (*How_Many_process)--;
            *(HowManyPipes)=*(HowManyPipes)-numberOfPipes;
            fprintf(stderr, "command not supported (Yet)\n");
            continue;
        }else {//If we did not have any Pipe in the string we received we would perform the Exercise 2 code
            countOfWords = howManyWords(str, 0);
            if (countOfWords == 0){//if count of word in str is zero
                (*How_Many_process)--;
                continue;
            }
            char **Command;
            Command = malloc((countOfWords + 1) * sizeof(char *));//malloc
            if (Command == NULL) {// condition If dynamic allocation failed
                fprintf(stderr, "malloc failed");
                FreeIfFailed(How_Many_process,HowManyPipes);
            }
            TheNumberOfLettersInEachWord(str, temp, Command, How_Many_process, HowManyPipes);
            if ((strcmp(Command[0], "done") == 0) && (countOfWords ==1)) {//if the user enter the word done ,the program will exit and show how many process, count of letters , Average length of all commands,and the massage
                (*How_Many_process)--;
                printf("Number of commands: %d\n", *How_Many_process);
                printf("Number of pipes: %d\n", *HowManyPipes);
                printf("See you Next time !");
                freeDynamicAllocation(Command, countOfWords);
                free(How_Many_process);
                free(HowManyPipes);
                exit(0);
            }
            if (strcmp(Command[0], "cd") == 0) {//if the user enter the word cd this will show and continue
                fprintf(stderr, "command not supported (Yet)\n");
                freeDynamicAllocation(Command, countOfWords);
                continue;
            }
            ProcessForNonePipes(Command, How_Many_process, HowManyPipes, countOfWords);
        }
    }
}
