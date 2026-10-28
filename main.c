#include "calculator.h"

int main(int argc, char * argv[])
{
    Dlist num1 = {NULL,NULL};
    Dlist num2 = {NULL,NULL};
    Dlist result = {NULL,NULL};

    // CLA validation
    if(argc != 4){
        printf("Usage: ./a.out num1 operator num2\n");
        return e_failure;
    }

    /* Create List 1 */
    if(create_list(&num1,argv[1]) == e_failure){
        printf("Error: Unable to create List 1\n");
        return e_failure;
    }

    /* Create List 2 */
    if(create_list(&num2,argv[3]) == e_failure){
        printf("Error: Unable to create List 2\n");
        return e_failure;
    }

    print_list(num1.head);
    print_list(num2.head);

    if(perform_operation(&num1,&num2,&result,argv[2]) == e_success){
        print_list(result.head);
    }
    else{
        printf("Error: Unable to perform operation\n");
        return e_failure;
    }




    return 0;
}