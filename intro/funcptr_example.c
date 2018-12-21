#include <stdio.h>

int func_one() {
    printf("this is a function one\n");
    return 1;
}

int func_two() {
    printf("this is a function two\n");
    return 2;
}

int main() {
    int value;
    // declare a variable of a type: pointer to a function
    int (*function_ptr) ();

    function_ptr = func_one;
    printf("function_ptr is 0x%08x\n", function_ptr);
    value = function_ptr();
    printf("value returned was %d\n", value);

    function_ptr = func_two;
    printf("function_ptr is 0x%08x\n", function_ptr);
    value = function_ptr();
    printf("value returned was %d\n", value);

    return 0;
}
