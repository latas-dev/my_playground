#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* add_hello(char *string, int size);

int main(int argc, char *argv[]) {
    
    char *my_string = "World";

    char *new_string =  
    printf("%s\n", my_string);

    free(new_string);

    return 0;
}

char* add_hello(char *string, int size) {
    char *new_string;
    new_string = (char *)malloc(size + 1);

    


}