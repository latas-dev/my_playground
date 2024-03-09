#include <stdio.h>
#include <string.h>

#define NELEMS(a) (sizeof(a)/sizeof(a[0]))
typedef struct Nameval Nameval;
struct Nameval {
    char    *name;
    int     value;
};

int blookup(char *name, Nameval tab[], int ntab);
// int llookup(char *word, char *array[]);

int main(int argc, char *argv) 
{
    // char *flab[] = {
    //     "perro",
    //     "gato",
    //     "estreno",
    //     "formato",
    //     "pronto",
    //     NULL
    // };

    // char *target = "estreno";
    // printf("La palabra %s se encuentra en el arreglo: %d.", target, lookup(target, flab));
    // printf("\nEl arreglo contiene %d elementos.", NELEMS(flab));

    Nameval htmlchars[] = {
        "AElig",    0x00c6,
        "Aacute",   0x00c1,
        "Acirc",    0x00c2,
        "frac12",   0x00c3,
        "zeta",     0x03b6,
    };

    int half;

    half = blookup("frac12", htmlchars, NELEMS(htmlchars));
    printf("El index de frac12 es: %d", half);

    return 0;
}

//lookup: Búsqueda binaria de name en tab; devuelve el índice.
int blookup(char *name, Nameval tab[], int ntab)
{
    int low, high, mid, cmp;

    low = 0;
    high = ntab - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        cmp = strcmp(name, tab[mid].name);
        if (cmp < 0)
            high = mid - 1;
        else if (cmp > 0)
            low = mid + 1;
        else    // ha sido encontrado.
            return mid;
    }
    return -1;  // No ha sido encontrado.
}

// llookup: Búsqueda lineal de una palabra en un arreglo
// int lookup(char *word, char *array[])
// {
//     int i;
//     for (i = 0; array[i] != NULL; i++) 
//         if (strcmp(word, array[i]) == 0)
//             return 1;
//     return -1;
// }

