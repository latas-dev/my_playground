#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

int main(int argc, char **argv) {

    char aString[] = "Hello!";

    printf("%s\n", aString);
    aString[5] = '?';
    printf("%s\n\n", aString);
    // aString = "Bye!";

    char *pString = "Hello!";
    printf("%s\n", pString);
    // pString[5] = ?;
    pString = "Bye!";
    printf("%s\n\n", pString);

    // array of strings through dynamic allocation

    char **strings;
    int total;

    printf("Enter number of strings: ");
    scanf("%d", &total);

    strings = malloc(total * sizeof(char *));

    char buffer[BUFFER_SIZE];
    int length;

    while(getchar() != '\n');

    printf("\n");
    for(int i = 0; i < total; i++) 
    {
        printf("Enter string[%d]: ", i);
        fgets(buffer, BUFFER_SIZE, stdin);
        length = strlen(buffer);
        buffer[length - 1] = '\0';

        strings[i] = malloc(length * sizeof(char));
        strcpy(strings[i], buffer);
    }

    printf("\nResulting strings inside the array\n\n");

    for(int i = 0; i < total; i++) 
    {
        printf("%s\n", strings[i]);
    }

    for(int i = 0; i < total; i++) 
    {
        free(strings[i]);
    }

    free(strings);

    return 0;
}