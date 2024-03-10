#include <stdio.h>
#include <string.h>    // strcmp
#include <stdlib.h>     // malloc

typedef struct Promedio Promedio;
struct Promedio {
    char *name;
    int  value;
    Promedio *next;
};
// Promedio methods 
Promedio *newPromedio(char *name, int value);
Promedio *addToFront(Promedio *list, Promedio *new_promedio);
Promedio *addToBack(Promedio *list, Promedio *new_promedio);
void lookupPromedio(Promedio *list, char *name);
int listLength(Promedio *list);
void deleteList(Promedio *list);
// void map(Promedio *list, void (*fn)(Promedio *, void*), void *arg);
// void printPromedio(Promedio *promedio, void *arg);

int main(int argc, char* argv[]) {
    Promedio *clase = newPromedio("Pedro", 98);
    clase = addToFront(clase, newPromedio("Andres", 90));
    clase = addToBack(clase, newPromedio("Miguel", 70));


    lookupPromedio(clase, "Juan");

    Promedio *temp = clase;
    for(; temp != NULL; temp = temp->next) {
        printf("%s: %d", temp->name, temp->value);
    }

    deleteList(clase);
    
    return 0;
}

Promedio *newPromedio(char *name, int value) {
    Promedio *new_promedio;
    new_promedio = (Promedio*)malloc(sizeof(Promedio));

    new_promedio->name  = name;
    new_promedio->value = value;
    new_promedio->next  = NULL;
    return new_promedio;
}

Promedio *addToFront(Promedio *list, Promedio *new_promedio) {
    new_promedio->next = list;
    return new_promedio;
}

Promedio *addToBack(Promedio *list, Promedio *new_promedio) {
    Promedio *current;

    if(list == NULL) return new_promedio;
    for(current = list; current != NULL; current = current->next) {
        ; // do nothing
    }
    current->next = new_promedio;
    return current;
}

void lookupPromedio(Promedio *list, char *name) {
    for(; list != NULL; list = list->next) {
        if(!strcmp(name, list->name)) printf("%s: %d\n", list->name, list->value);
    }
    printf("Item not found\n");
}

int listLength(Promedio *list) {
    int i = 0;

    for(; list != NULL; list = list->next) {
        i++;
    }
    return i;
}

void deleteList(Promedio *list) {
    Promedio *next;
    for(; list != NULL; list = next) {
        next = list->next;
        free(list);
    }
}


// void map(Promedio *list, void (*fn)(Promedio *, void*), void *arg) {
//     for(; list != NULL; list = list->next) {
//         (*fn)(list, arg);
//     }
// }