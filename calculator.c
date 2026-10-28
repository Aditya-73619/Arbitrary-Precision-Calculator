#include "calculator.h"

int sign = POSITIVE;

STATUS create_list(Dlist* list, char* str)
{
    int i=0;

    while(str[i] != '\0')
    {
        if(str[i] < '0' || str[i] > '9'){       // Validate that character is from 0-9
            printf("Error: Invalid Num1\n");
            return e_failure;
        }

        int digit = str[i] - '0';       // Char to int conversion

        if(insert_at_last(list,digit) == e_failure){
            printf("Error: Unable to insert num1 in list 1\n");
            return e_failure;
        }

        i++;
    }

    return e_success;
}


STATUS insert_at_last(Dlist* list,int digit)
{
    // Creating the new node
    calculator* new_node = malloc(sizeof(calculator));

    if(new_node == NULL){
        printf("Error: Memory not allocated\n");
        return e_failure;
    }

    //Initializing the new node
    new_node->data = digit;
    new_node->prev = NULL;
    new_node->next = NULL;

    if(list->head == NULL){
        list->head = new_node;
        list->tail = new_node;

        return e_success;
    }

    new_node->prev = list->tail;
    list->tail->next = new_node;
    list->tail = new_node;

    return e_success;
}

STATUS insert_at_first(Dlist* list,int digit)
{
    calculator* new_node = malloc(sizeof(calculator));

    if(new_node == NULL){
        printf("Error: Memory not allocated\n");
        return e_failure;
    }

    //Initializing the new node
    new_node->data = digit;
    new_node->prev = NULL;
    new_node->next = NULL;

    if(list->head == NULL){
        list->head = new_node;
        list->tail = new_node;

        return e_success;
    }

    new_node->next = list->head;
    list->head->prev = new_node;
    list->head = new_node;

    return e_success;
}

void print_list(calculator* head)
{
    if(head == NULL){
        printf("Info: List is empty\n");
        return;
    }

    if(sign == NEGATIVE)
        printf("-");

    while(head)
    {
        printf("%d",head->data);

        head = head->next;
    }
    printf("\n");
}

STATUS perform_operation(Dlist* num1, Dlist* num2, Dlist* result, char* operator)
{
    switch(operator[0])
    {
        case '+': return addition(num1,num2,result);

        case '-':   if(list_compare(num1,num2) == NOSWAP){
                        sign = POSITIVE;
                        return subtraction(num1,num2,result);
                    }
                    else{
                        sign = NEGATIVE;
                        return subtraction(num2,num1,result);
                    }
        
        // case '*': return multiplication(num1,num2,result);
        // case '/': return division(num1,num2,result);
        default : printf("Error: Invalid operator\n");
                  return e_failure;
    }
}

STATUS addition(Dlist* num1, Dlist* num2, Dlist* result)
{
    // Creating temp pointers for both num1 and num2
    calculator* temp1 = num1->tail;
    calculator* temp2 = num2->tail;

    int carry = 0;
    int sum = 0;
    int digit;

    while(temp1 || temp2)
    {
        if(temp1 && temp2)
        {
            sum = temp1->data + temp2->data + carry;

            carry = sum / 10;
            digit = sum % 10;

            insert_at_first(result,digit);

            temp1 = temp1->prev;
            temp2 = temp2->prev;
        }

        else if(temp1 && (temp2 == NULL))
        {
            sum = temp1->data + carry;

            carry = sum / 10;
            digit = sum % 10;

            insert_at_first(result,digit);

            temp1 = temp1->prev;
        }
        else if((temp1 == NULL) && temp2)
        {
            sum = temp2->data + carry;

            carry = sum / 10;
            digit = sum % 10;

            insert_at_first(result,digit);

            temp2 = temp2->prev;
        }
    }

    if(carry){
        insert_at_first(result,carry);
        carry = 0;
    }

    return e_success;
}

STATUS subtraction(Dlist* num1, Dlist* num2, Dlist* result)
{       
    calculator* temp1 = num1->tail;
    calculator* temp2 = num2->tail;

    int borrow = 0;
    int diff = 0;
    int digit;

    while(temp1 || temp2)
    {
        // When both num1 and num2 are valid
        if(temp1 && temp2)
        {
            diff = temp1->data - temp2->data - borrow;
            temp1 = temp1->prev;
            temp2 = temp2->prev;
        }

        // When num2 have less digits
        else if(temp1 && (temp2 == NULL))
        {
            diff = temp1->data - borrow;
            temp1 = temp1->prev;
        }

        if(diff < 0){
            diff += 10;
            borrow = 1;
        }
        else
            borrow = 0;

        insert_at_first(result,diff);
    }

    return e_success;
}

int list_compare(Dlist* num1,Dlist* num2)
{
    calculator* temp1 = num1->head;
    calculator* temp2 = num2->head;

    int count1 = 0;
    int count2 = 0;

    // Counting digits of num1
    while(temp1)
    {
        count1++;
        temp1 = temp1->next;
    }

    // Counting digits of num2
    while(temp2)
    {
        count2++;
        temp2 = temp2->next;
    }


    temp1 = num1->head;
    temp2 = num2->head;

    // Checking which num is greater
    if(count1 < count2){
        sign = NEGATIVE;
        return SWAP;
    }

    else if(count1 > count2){
        sign = POSITIVE;
        return NOSWAP;
    }

    else if(count1 == count2)
    {
        /* Digit comparison */
        while(temp1 && temp2)
        {
            if(temp1->data < temp2->data){
                sign = NEGATIVE;
                return SWAP;
            }
            
            temp1 = temp1->next;
            temp2 = temp2->next;
        }

        sign = POSITIVE;
        return NOSWAP;
    }

    return NOSWAP;
}