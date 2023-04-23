#include <stdio.h>

#include <stdlib.h>

#include <pthread.h>

#include "string.h"

#include <sys/types.h>

#define MAX 511 // length of the String
typedef struct Polynomial_data { // this struct save the string for each threads and there result
    char * str;
    int result;
}
        Polynomial_data;
char str[MAX];
char tmp[MAX];
int Val = 0;
void Fgets(); // this method will get from the user a polynomial and the value
int count_of_x(const char str_new[]); // this method counts the number of x's in the polynomial
int count_of_Plus(); // this method counts the number of plus's in the polynomial
char * TheVal(char str_new[], char c, char copy[]); // this method will get a string and the char and return the string is after the char
int ArrayToInt(char[]); // this method convert the String to int
char * selection(char[]); //this method will get first polynomial
int Factor(char[]); //this method returns coefficient of the polynomial
int Pow(int pow, int x, int y); // this method doing x^y
void Free_Polynomial(Polynomial_data Polynomial[], int i); //free allocations
void * thread(void * arg) { //this method will get the polynomial and place the val in it and save the result in the struct
    Polynomial_data * Polynomial = (Polynomial_data * ) arg;
    int factor = Factor(Polynomial -> str); // find the factor
    int power = ArrayToInt(TheVal(Polynomial -> str, '^', tmp)); // find the power
    Polynomial -> result = factor * Pow(1, Val, power); // calculate

    return NULL;
}
int main() {
    int i, status, how_Many_threads, count_how_Many_Plus, result;
    for (;;) {
        result = 0;
        Fgets();
        if (strlen(str) == 0) continue; //if user enter nothing
        if (strcmp(str, "done") == 0) { // if user entered done exit program
            exit(EXIT_SUCCESS);
        }
        Val = ArrayToInt(TheVal(str, ',', tmp));
        how_Many_threads = count_of_x(str);
        count_how_Many_Plus = count_of_Plus();
        Polynomial_data Polynomial[how_Many_threads]; // create struct array
        for (i = 0; i < how_Many_threads; i++) { // for loop
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
        pthread_t thread_data[how_Many_threads];
        for (i = 0; i < how_Many_threads; i++) { //for loop
            status = pthread_create( & thread_data[i], NULL, thread, (void * ) & Polynomial[i]);
            if (status != 0) {
                fprintf(stderr, "pthread create failed");
                exit(EXIT_FAILURE);
            }
        }
        for (i = 0; i < how_Many_threads; i++) { // join threads
            pthread_join(thread_data[i], NULL);
        }
        if (how_Many_threads == count_how_Many_Plus) {
            result += ArrayToInt(selection(tmp));
        }
        for (i = 0; i < how_Many_threads; i++) { // sum  all results
            result += Polynomial[i].result;
            free(Polynomial[i].str);
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
char * TheVal(char str_new[], char c, char copy[]) { // this method will get a string and the char and return the string is after the char
    strcpy(copy, "");
    if (strchr(str_new, c) == NULL && c == '^') {
        strcpy(copy, "1");
        return copy;
    }
    char * ret;
    ret = strchr(str_new, c);
    int i, j = 0;
    for (i = 1; ret[i] != '\0'; i++) {
        if (ret[i] >= '0' && ret[i] <= '9') {
            copy[j] = ret[i];
            j++;
        }
        if (ret[i] == ',') break;
    }
    copy[j] = '\0';
    return copy;
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
char * selection(char copy[]) { //this method will get first polynomial
    strcpy(copy, "");
    int i, j = 0;
    for (i = 0;; i++) {
        if (str[i] == '\0') {
            copy[j] = '\0';
            break;
        }
        if (str[i] == '+' || str[i] == ',' || str[i] == ' ') {
            copy[j] = '\0';
            break;
        }
        copy[j] = str[i];
        j++;
    }
    return copy;
}
int Factor(char copy[]) { //this method returns coefficient of the polynomial
    int i, j = 0;
    char factor[strlen(copy) + 1];
    if (copy[0] == 'x') return 1;
    for (i = 0;; i++) {
        if (copy[i] == '*' || copy[i] == 'x' || copy[i] == '\0') {
            factor[j] = '\0';
            break;
        }
        if (copy[i] >= '0' && copy[i] <= '9') {
            factor[j] = copy[i];
            j++;
        }
    }
    if (strlen(copy) == 0) return 1;
    return ArrayToInt(factor);
}
int Pow(int pow, int x, int y) { // this method doing x^y
    int i;
    pow = 1;
    for (i = 1; i <= y; i++)
        pow = pow * x;
    return pow;
}
void Free_Polynomial(Polynomial_data Polynomial[], int i) { //free allocations
    int k;
    for (k = 0; k < i; k++) {
        free(Polynomial[k].str);
    }
}