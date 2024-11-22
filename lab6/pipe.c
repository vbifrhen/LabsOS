#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char buf[1024];
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    char local_time[64];
    strftime(local_time, sizeof(local_time), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("Принимающий процесс: PID: %d, Время: %s\n", getpid(), local_time);

    // Создание pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();  // Создаем дочерний процесс

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Дочерний процесс
        // Задержка, чтобы время отличалось на хотя бы 5 секунд
        sleep(5);

        // Чтение данных из pipe
        read(pipefd[0], buf, sizeof(buf));
        tm_info = localtime(&now);
        char local_time[64];
        strftime(local_time, sizeof(local_time), "%Y-%m-%d %H:%M:%S", tm_info);
        printf("Принимающий процесс: PID: %d, Время: %s\n", getpid(), local_time);
        printf("Received: %s\n", buf);

        close(pipefd[0]);
        close(pipefd[1]);
    } else {  // Родительский процесс
        // Пишем данные в pipe
        write(pipefd[1], buf, strlen(buf) + 1);
        close(pipefd[0]);
        close(pipefd[1]);
    }

    return 0;
}
