#include <stdio.h>
#include <stdlib.h> // malloc

typedef struct Promedio Promedio;
struct Promedio {
    char *name;
    int  value;
    Promedio *next;
};

Node *newPromedio(char *name, int value) {
    Promedio *new_promedio;
    new_promedio = (Promedio*)malloc(sizeof(Promedio));

    new_promedio->name  = name;
    new_promedio->value = value;
    new_promedio->next  = NULL;
    return new_promedio;
}

Node *addToFront(Promedio *list, Promedio new_promedio) {
    new_promedio->next = list;
    return new_promedio;
}

Node *addToBack(Promedio *list, Promedio new_promedio) {
    Promedio *current;

    if(list == NULL) return new_promedio;
    for(current = list; current != NULL; current = current->next) {
        ; // do nothing
    }
    current->next = new_promedio;
    return current;
}

int main(int argc, char* argv[]) {


    return 0;
}