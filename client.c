#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_BUFFER 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <server_ip> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *server_ip = argv[1];
    int port = atoi(argv[2]);
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[MAX_BUFFER] = {0};

    // Создание сокета
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    // Настройка адреса сервера
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port); // Преобразование порта в сетевой порядок байтов

    // Преобразование IP-адреса из текстового формата в двоичный
    if (inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Подключение к серверу
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server %s on port %d\n", server_ip, port);

    // Основной цикл для отправки и получения данных
    while (1) {
        printf("Enter message: ");
        fgets(buffer, MAX_BUFFER, stdin);

        // Отправка сообщения на сервер
        send(sock, buffer, strlen(buffer), 0);

        // Получение ответа от сервера
        memset(buffer, 0, MAX_BUFFER); // Очистка буфера
        int valread = read(sock, buffer, MAX_BUFFER);
        printf("Server: %s\n", buffer);
    }

    // Закрытие сокета
    close(sock);
    return 0;
}
