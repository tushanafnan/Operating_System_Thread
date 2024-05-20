#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MSG_SIZE 80

int main() {
    int fd[2];
    char input_msg[MSG_SIZE];
    char output_msg[MSG_SIZE] = "Hello from child process!";
    pid_t pid;

    if (pipe(fd) == -1) {
        perror("Pipe failed");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) { // Parent process
        printf("Enter message to send to child process: ");
        fgets(input_msg, MSG_SIZE, stdin);
        close(fd[0]); // Close reading end of pipe in parent
        write(fd[1], input_msg, strlen(input_msg)+1);
        close(fd[1]); // Close writing end of pipe in parent
    } else { // Child process
        close(fd[1]); // Close writing end of pipe in child
        read(fd[0], output_msg, MSG_SIZE);
        printf("Message received in child process: %s\n", output_msg);
        close(fd[0]); // Close reading end of pipe in child
    }

    return 0;
}
