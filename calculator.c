#include "calculator.h"

int sign = POSITIVE;

STATUS create_list(Dlist* list, char* str)
{
    int i=0;

    while(str[i] != '\0')
    {
        if(str[i] < '0' || str[i] > '9'){       // Validate that character is from 0-9
            printf("Error: Invalid number, Only digits 0-9 are allowed.\n\n");
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
        
        case 'x': return multiplication(num1,num2,result);

        case '/': return division(num1,num2,result);

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

            if(insert_at_first(result,digit) == e_failure){
                printf("Error: Failed to insert digit during addition\n");
                return e_failure;
            }

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

        if(insert_at_first(result,diff) == e_failure){
            printf("Error: Failed to insert digit during subtraction\n");
            return e_failure;
        }
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

STATUS multiplication(Dlist* num1, Dlist* num2, Dlist* result)
{
    Dlist result1 = {NULL,NULL};
    Dlist result2 = {NULL,NULL};

    calculator* temp1;
    calculator* temp2 = num2->tail;

    int carry = 0;
    int count = 0;
    int product;
    int digit;

    while(temp2)
    {
        temp1 = num1->tail;
        carry = 0;

        // Multiply every digit of num1 by one digit of num2
        while(temp1)
        {
            product = temp2->data * temp1->data + carry;

            carry = product / 10;
            digit = product % 10;

            if(count == 0){
                if(insert_at_first(&result1,digit) == e_failure){
                    printf("Error: Failed to insert digit into result1\n");
                    return e_failure;
                }
            }
            else{
                if(insert_at_first(&result2,digit) == e_failure){
                    printf("Error: Failed to insert digit into result2\n");
                    return e_failure;
                }
            }

            temp1 = temp1->prev;
        }

        // Store leftover carry
        if(carry){
            if(count == 0){
                if(insert_at_first(&result1,digit) == e_failure){
                    printf("Error: Failed to insert carry into result1\n");
                    return e_failure;
                }
            }
            else{
                if(insert_at_first(&result2,digit) == e_failure){
                    printf("Error: Failed to insert carry into result2\n");
                    return e_failure;
                }
            }
        }

        if(count == 0){
            temp2 = temp2->prev;
            count++;
            continue;
        }

        // Adding 0s in the last of the current partial product
        for(int i=0;i<count;i++){
            if(insert_at_last(&result2,0) == e_failure){
                printf("Error: Failed to insert 0 to result2\n");
                return e_failure;
            }
        }

        // Add result1 and result2 into result
        if(addition(&result1,&result2,result) == e_failure){
            printf("Error: Failed to add partial products\n");
            return e_failure;
        }

        // Free the nodes of result1 
        while(result1.head)
        {
            calculator* temp = result1.head;
            result1.head = result1.head->next;
            free(temp);
        }
        result1.tail = NULL;

        //Free the nodes of result2
        while(result2.head)
        {
            calculator* temp = result2.head;
            result2.head = result2.head->next;
            free(temp);
        }
        result2.tail = NULL;


        result1.head = result->head;
        result1.tail = result->tail;

        result->head = NULL;
        result->tail = NULL;

        temp2 = temp2->prev;
        count++;
    }

    // Copying the answer to result from result1
    result->head = result1.head;
    result->tail = result1.tail;

    result1.head = NULL;
    result1.tail = NULL;

    return e_success;
}

void remove_leading_zeroes(Dlist* list)
{
    while(list->head && 
          list->head != list->tail &&       // False if only 1 node is present
          list->head->data == 0)
    {
        calculator* temp = list->head;

        list->head = list->head->next;
        list->head->prev = NULL;

        free(temp);
    }
}

void clear_list(Dlist* list)
{
    // Deleting all nodes of list
    while(list->head)
    {
        calculator* temp = list->head;

        list->head = list->head->next;

        free(temp);
    }

    list->tail = NULL;
}

STATUS division(Dlist* num1, Dlist* num2, Dlist* result)
{
    Dlist current = {NULL,NULL};        // list to store digits of num1 partially
    Dlist sub_result = {NULL,NULL};     // list to store substraction result

    calculator* temp1 = num1->head;
    calculator* temp2 = num2->head;

    int count = 0;

    //Validating division by 0
    while(temp2 && temp2->data == 0)
        temp2 = temp2->next;
    

    if(temp2 == NULL){
        printf("Error: Division by zero is not allowed\n");
        return e_failure;
    }

    /* Take digits from num1 one by one */
    while(temp1)
    {
        if(insert_at_last(&current,temp1->data) == e_failure){
            printf("Error: Failed to insert digit into current\n");
            return e_failure;
        }

        // Removing leading zeroes from current
        remove_leading_zeroes(&current);        

        count = 0;

        // Repeating subtraction while current >= num2
        while(list_compare(&current,num2) == NOSWAP)
        {
            if(subtraction(&current,num2,&sub_result) == e_failure){
                printf("Error: Failed to do the subtraction in division\n");
                return e_failure;
            }

            clear_list(&current);               // to do

            // Update current with sub_result
            current.head = sub_result.head;
            current.tail = sub_result.tail;

            remove_leading_zeroes(&current);

            // Reset sub_result
            sub_result.head = NULL;
            sub_result.tail = NULL;

            count++;
        }

        // Store quotient(count) to result
        if(insert_at_last(result,count) == e_failure){
            printf("Error: Failed to insert quotient in division\n");
            return e_failure;
        }

        temp1 = temp1->next;
    }


    // Removing leading zeroes from quotient
    remove_leading_zeroes(result);

    clear_list(&current);
    clear_list(&sub_result);

    sign = POSITIVE;
    return e_success;
}