#include <stdio.h>

#define print_type_size(type)\
    printf("the "#type " data type is\t\t %d bytes\n", sizeof(type))

int main() {
    print_type_size(int);
    print_type_size(unsigned int);
    print_type_size(short int);
    print_type_size(long int);
    print_type_size(long long int);
    print_type_size(float);
    print_type_size(char);
}
