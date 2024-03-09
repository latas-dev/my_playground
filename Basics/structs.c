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
    rect1.length = 5;
    rect1.width = 10;

    /* C */
    // Rectangle rect1 = {5, 10};

    printf("The area of the rectangle is: %d", rect1.length * rect1.width);

}