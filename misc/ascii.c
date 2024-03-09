#include <stdio.h>

int main() {
    int len = 256;
    for(int i = 0; i < len; ++i) {
        printf("%i - %c\n", i, i);
    }
}