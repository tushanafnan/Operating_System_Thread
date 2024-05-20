#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// Define a structure for the message
struct msg_buffer {
    long msg_type;
    char msg_text[100];
} message;

int main() {
    key_t key;
    int msgid;

    // ftok to generate unique key
    key = ftok("progfile", 65);

    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);

    // message to be sent
    message.msg_type = 1;
    printf("Write Data : ");
    fgets(message.msg_text, 100, stdin);

    // msgsnd to send message
    msgsnd(msgid, &message, sizeof(message), 0);

    // display the message
    printf("Data send is : %s \n", message.msg_text);

    return 0;
}
