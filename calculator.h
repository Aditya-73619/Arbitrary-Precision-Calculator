#ifndef CALCULATOR_H
#define CALCULATOR_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define SWAP 1
#define NOSWAP 0
#define NEGATIVE -1
#define POSITIVE 2
#define LASTDIGIT 3

typedef enum{
    e_success,
    e_failure
}STATUS;

typedef struct calculator{
    int data;
    struct calculator* next;
    struct calculator* prev;
}calculator;


typedef struct{
    calculator* head;
    calculator* tail;
}Dlist;

/* To create the list for numbers */

/* To create the list for numbers */
STATUS create_list(Dlist* list, char* str);

/* Insert the element in the last pos */
STATUS insert_at_last(Dlist* list,int digit);

/* Insert the element in the first pos */
STATUS insert_at_first(Dlist* list,int digit);

/* Print the list */
void print_list(calculator* head);

/* To decide which operation to be performed */
STATUS perform_operation(Dlist* num1, Dlist* num2, Dlist* result, char* operator);

/* Addition operation */
STATUS addition(Dlist* num1, Dlist* num2, Dlist* result);

/* Substraction operation */
STATUS subtraction(Dlist* num1, Dlist* num2, Dlist* result);

/* Compare 2 numbers to tell which one is greater */
int list_compare(Dlist* num1,Dlist* num2);

/* Multiplication operation */
STATUS multiplication(Dlist* num1, Dlist* num2, Dlist* result);

/* Removes leading zeroes of number */
void remove_leading_zeroes(Dlist* list);

/* Delete all nodes of the list */
void clear_list(Dlist* list);

/* Division operation */
STATUS division(Dlist* num1, Dlist* num2, Dlist* result);




#endif