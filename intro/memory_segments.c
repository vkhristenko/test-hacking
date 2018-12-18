#include <stdio.h>

int global_var;

int global_intialized_var = 5;

void function() {
    int stack_var;
    printf("the function's stack_var is at address 0x%08x\n", &stack_var);
}

int main() {
    int stack_var;
    static int static_initialized_var = 5;
    static int static_var;
    int *heap_var_ptr;

    heap_var_ptr = (int*) malloc(4);

    // in data segment
    printf("global_initialized_var is at address 0x%08x\n", &global_intialized_var);
    printf("static_initialized_var is at address 0x%08x\n\n", &static_initialized_var);

    // in bss segment
    printf("static_var is at address 0x%08x\n", &static_var);
    printf("global_var is at address 0x%08x\n\n", &global_var);

    // on heap
    printf("heap_var is at address 0x%08x\n\n", heap_var_ptr);

    // stack segment
    printf("stack_var is at address 0x%08x\n", &stack_var);
    function();

    // function itself
    printf("function is at address 0x%08x\n", function);
    printf("function is at address 0x%08x\n", ((char*)function) + 1);
}
