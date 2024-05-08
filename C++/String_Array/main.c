#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char **argv)
{
    int size;

    printf("Ingrese la cantidad de 'strings' que quiere: ");
    scanf("%d", &size);

    char **strings = (char **)malloc(size * sizeof(char *));

    int c;
    while((c = getchar()) != '\n' && c != EOF);

    char buffer[BUFFER_SIZE];
    int len;

    for(int i = 0; i < size; i++)
    {
        printf("Ingrese el primer string: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        len = strlen(buffer);
        strings[i] = (char *)malloc(len * sizeof(char));
        strcpy(strings[i], buffer);
    }

    printf("\n");
    for(int i = 0; i < size; i++)
    {
        printf("%d: %s", i, strings[i]);
        free(strings[i]);
    }

    free(strings);

    return 0;
}