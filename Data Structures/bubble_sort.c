#include <stdio.h>

#define ARRAY_LEN(a) (sizeof(a) / sizeof(int))

void swap(int *a, int *b);
void bubble_sort(int *arr, int len);
void print_list(int *arr, int len);

int main(int argc, char* argv[]) {
    int my_array[10] = {3,10,2,1,9,5,6,4,8,7};
    int len = ARRAY_LEN(my_array);

    bubble_sort(my_array, len);
    print_list(my_array, len);

    return 0;
}

void swap(int *a, int *b) {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(int *arr, int len) {
    for(int i = 0; i < len - 1; i++) {
        for(int j = i + 1; j < len; j++) {
            if(arr[i] > arr[j]) swap(&arr[i], &arr[j]); 
        }
    }
}

void print_list(int *arr, int len)  {
    for(int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
}