// a function to display an error message and then exit
void fatal(char *message) {
    char error_message[100];

    strcpy(error_message, "[!!] fatal error");
    strncat(error_message, message, 83);
    perror(error_message);

    exit(-1);
}

// an error-checked malloc() wrapper function
void *ec_malloc(unsigned int size) {
    void *ptr;
    ptr = malloc(size);
    if (ptr == NULL)
        fatal("in ec_malloc() on memory allocation");

    return ptr;
}

// dumps raw memory in hex byte and printable split format
void dump(unsigned char const *data_buffer, unsigned int const length) {
    unsigned char byte;
    unsigned int i,j;
    for (i=0; i<length; i++) {
        byte = data_buffer[i];
        printf("%02x", data_buffer[i]);
        if (((i%16) == 15) || (i==length-1)) {
            for (j=0; j<15-(i%16); j++)
                printf("  ");
            printf("| ");
            for (j=(i-(i%16)); j<=i; j++) { // diplsya printable bytes from line.
                byte = data_buffer[j];
                if ((byte > 31) && (byte < 127)) // outside printable char range
                    printf("%c", byte);
                else
                    printf(".");
            }
            printf("\n");
        }
    }
}
