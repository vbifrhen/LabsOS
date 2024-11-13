#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char buf[1024];
    struct timeval tv;
    gettimeofday(&tv, NULL);  // Текущее время в секундах и микросекундах
    snprintf(buf, sizeof(buf), "Time: %ld.%06ld, PID: %d", tv.tv_sec, tv.tv_usec, getpid());

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
        gettimeofday(&tv, NULL);
        printf("Child Process Time: %ld.%06ld\n", tv.tv_sec, tv.tv_usec);
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
