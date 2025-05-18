#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define MAX_BUFFER 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int port = atoi(argv[1]);
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[MAX_BUFFER] = {0};

    // Создание сокета
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Привязка сокета к порту
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Прослушивание входящих соединений
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", port);

    while (1) {
        // Принятие соединения
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        // Генерация случайного числа
        srand(time(NULL));
        int number_to_guess = rand() % 100 + 1;
        int guess = 0;

        printf("Client connected: %s:%d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));

        while (1) {
            memset(buffer, 0, MAX_BUFFER);
            read(new_socket, buffer, MAX_BUFFER);
            guess = atoi(buffer);
            printf("Client guessed: %d\n", guess);

            if (guess < number_to_guess) {
                send(new_socket, "Higher!\n", strlen("Higher!\n"), 0);
            } else if (guess > number_to_guess) {
                send(new_socket, "Lower!\n", strlen("Lower!\n"), 0);
            } else {
                send(new_socket, "Correct!\n", strlen("Correct!\n"), 0);
                break;
            }
        }

        printf("Client disconnected: %s:%d\n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));
        close(new_socket);
    }

    close(server_fd);
    return 0;
}
