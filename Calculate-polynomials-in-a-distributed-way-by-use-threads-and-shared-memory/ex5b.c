#include <stdio.h>

#include <stdlib.h>

#include "string.h"

#include <sys/types.h>

#include <sys/ipc.h>

#include <sys/shm.h>

#include <unistd.h>

#include <sys/wait.h>

#define MAX 511 // length of the String
typedef struct Polynomial_data { // this struct save the string for each thread
    char * str;
}
        Polynomial_data;
char str[MAX];
char tmp[MAX];
int Val = 0;
void Fgets(); // this method will get from the user a polynomial and the value
int count_of_x(const char str_new[]); // this method counts the number of x's in the polynomial
int count_of_Plus(); // this method counts the number of plus's in the polynomial
char * TheVal(char str_new[], char c, char copy_new[]); // this method will get a string and the char and return the string is after the char
int ArrayToInt(char[]); // this method turn the String to int
char * selection(char[]); //this method will get first polynomial
int Factor(char[]); //this method returns coefficient of the polynomial
int Pow(int pow, int x, int y); // this method doing x^y
void ForSons(int how_Many_sons, Polynomial_data Polynomial[], int * shm_ptr, int how_Many_Plus, int * result); //this method will get the polynomial and place the val in it and save the result in the shared memory
void Free_Polynomial(Polynomial_data Polynomial[], int i); //free allocations
int Find_result(Polynomial_data * Polynomial) { // this method will calculate the polynomial and save it to the shared memory
    int factor = Factor(Polynomial -> str);
    int power = ArrayToInt(TheVal(Polynomial -> str, '^', tmp));
    int result = factor * Pow(1, Val, power);
    return result;
}
int main() {
    int i, how_Many_sons, count_how_Many_Plus, result;
    for (;;) {
        result = 0;
        Fgets();
        if (strlen(str) == 0) continue; //if user enter nothing
        if (strcmp(str, "done") == 0) { // if user entered done exit program
            exit(EXIT_SUCCESS);
        }
        Val = ArrayToInt(TheVal(str, ',', tmp));
        how_Many_sons = count_of_x(str);
        count_how_Many_Plus = count_of_Plus();
        if (how_Many_sons == 0) {
            result += ArrayToInt(selection(tmp));
            printf("The FinalResult is %d\n", result);
            continue;
        }
        Polynomial_data Polynomial[how_Many_sons]; // create struct array
        for (i = 0; i < how_Many_sons; i++) {
            selection(tmp);
            Polynomial[i].str = (char * ) malloc(sizeof(char) * (strlen(tmp) + 1));
            if (Polynomial[i].str == NULL) {
                fprintf(stderr, "malloc failed");
                Free_Polynomial(Polynomial, i);
                exit(EXIT_FAILURE);
            }
            strcpy(Polynomial[i].str, tmp);
            if (strchr(str, '+') != NULL) {
                memmove(str, strchr(str, '+') + 1, MAX);
            }
        }
        key_t key; // shared memory key
        if ((key = ftok("/tmp", 'y')) == -1) {
            perror("ftok() failed");
            exit(EXIT_FAILURE);
        }
        int shm_id; // shared memory id
        shm_id = shmget(key, how_Many_sons * (sizeof(int)), IPC_CREAT | IPC_EXCL | 0600);
        if (shm_id == -1) {
            perror("shmget failed");
            exit(EXIT_FAILURE);
        }
        int * shm_ptr; // shared memory pointer
        shm_ptr = (int * ) shmat(shm_id, NULL, 0);
        if (shm_ptr == (int * ) - 1) {
            perror("shmat failed");
            exit(EXIT_FAILURE);
        }
        ForSons(how_Many_sons, Polynomial, shm_ptr, count_how_Many_Plus, & result);
        for (i = 0; i < how_Many_sons; i++) { // sum  all results
            result += shm_ptr[i];
            free(Polynomial[i].str);
        }
        shmdt(shm_ptr); // delete shared memory
        if (shmctl(shm_id, IPC_RMID, NULL) == -1) {
            perror("shmctl failed");
            exit(EXIT_FAILURE);
        }
        printf("The Final Result is: %d\n", result);
        strcpy(str, "");
    }
    return 0;
}
void Fgets() { // this method will get from the user a polynomial and the value
    if (fgets(str, MAX, stdin) == NULL) { // we use fgets to enter the commands
        fprintf(stderr, "the fgets is failed\n"); // condition if the String we enter it was Null
        exit(1); // exit from the code
    }
    str[strlen(str) - 1] = '\0';
}
int count_of_x(const char str_new[]) { // this method counts the number of x's in the polynomial
    int i, counter_x = 0;
    for (i = 0; str_new[i] != '\0'; i++) {
        if (str_new[i] == 'x')
            counter_x++;
    }
    return counter_x;
}
int count_of_Plus() { // this method counts the number of plus's in the polynomial
    int i, counter_Plus = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] == '+')
            counter_Plus++;
    }
    return counter_Plus;
}
char * TheVal(char str_new[], char c, char copy_new[]) { // this method will get a string and the char and return the string is after the char
    strcpy(copy_new, "");
    if (strchr(str_new, c) == NULL && c == '^') {
        strcpy(copy_new, "1");
        return copy_new;
    }
    char * ret;
    ret = strchr(str_new, c);
    int i, j = 0;
    for (i = 1; ret[i] != '\0'; i++) {
        if (ret[i] >= '0' && ret[i] <= '9') {
            copy_new[j] = ret[i];
            j++;
        }
        if (ret[i] == ',') break;
    }
    copy_new[j] = '\0';
    return copy_new;
}
int ArrayToInt(char num[]) // this method turn the char to int
{
    int size = (int) strlen(num);
    int i, counter = 1, number = 0;
    for (i = size - 1; i >= 0; i--) {
        number += ((num[i] - '0') * counter);
        counter *= 10;
    }
    return number;
}
char * selection(char copy_new[]) { //this method will get first polynomial
    strcpy(copy_new, "");
    int i, j = 0;
    for (i = 0;; i++) {
        if (str[i] == '\0') {
            copy_new[j] = '\0';
            break;
        }
        if (str[i] == '+' || str[i] == ',' || str[i] == ' ') {
            copy_new[j] = '\0';
            break;
        }
        copy_new[j] = str[i];
        j++;
    }
    return copy_new;
}
int Factor(char copy_new[]) { //this method returns coefficient of the polynomial
    int i, j = 0;
    char factor[strlen(copy_new) + 1];
    if (copy_new[0] == 'x') return 1;
    for (i = 0;; i++) {
        if (copy_new[i] == '*' || copy_new[i] == 'x' || copy_new[i] == '\0') {
            factor[j] = '\0';
            break;
        }
        if (copy_new[i] >= '0' && copy_new[i] <= '9') {
            factor[j] = copy_new[i];
            j++;
        }
    }
    if (strlen(copy_new) == 0) return 1;
    return ArrayToInt(factor);
}
int Pow(int pow, int x, int y) { // this method doing x^y
    int i;
    pow = 1;
    for (i = 1; i <= y; i++)
        pow = pow * x;
    return pow;
}
void ForSons(int how_Many_sons, Polynomial_data Polynomial[], int * shm_ptr, int how_Many_Plus, int * result) { //this method will get the polynomial and place the val in it and save the result in the shared memory
    int i;
    pid_t child1;
    for (i = 0; i < how_Many_sons; i++) {
        child1 = fork();
        if (child1 < 0) {
            /* error occurred */
            perror("folk filed");
            exit(EXIT_FAILURE);
        } else if (child1 == 0) {
            /* child process */
            shm_ptr[i] = Find_result( & Polynomial[i]); //put in the shared memory the results from the sons
            Free_Polynomial(Polynomial, how_Many_sons);
            exit(EXIT_SUCCESS);
        }
    }
    for (i = 0; i < how_Many_sons; i++) {
        /* father process */
        wait(NULL);
    }
    if (how_Many_sons == how_Many_Plus) {
        ( * result) += ArrayToInt(selection(tmp));
    }
}
void Free_Polynomial(Polynomial_data Polynomial[], int i) { //free allocations
    int k;
    for (k = 0; k < i; k++) {
        free(Polynomial[k].str);
    }
}