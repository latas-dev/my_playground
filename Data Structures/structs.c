#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

typedef struct 
{
    char *sender;
    char *receiver;

    char *message;
} Message;

typedef struct 
{
    char *name;

    Message *messageList;
} User;

int main(void)
{


    return 0;
}

Message *sendMessage(User *sender, User *receiver)
{
    char buffer[BUFFER_SIZE];

    printf("Enter your message: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    arr[i];
    i[arr];

    *(i + arr);
    *(arr + i);
}