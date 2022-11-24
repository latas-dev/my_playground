#include <stdio.h>

struct Rectangle {
    int length;
    int width;
};

/* C */
// typedef struct Rectangle {
//     int length;
//     int width;
// } Rectangle;

int main() {

    struct Rectangle rect1;
    rect1.length = 10;
    rect1.width = 20;

    /* C */
    // Rectangle rect1 = {10, 20};


    printf("%d, %d", rect1.length, rect1.width);

}