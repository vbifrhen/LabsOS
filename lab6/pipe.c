#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int main() {
    int pipefd[2];
    char buf[1024];
    pid_t pid;
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);
    printf("Принимающий процесс: PID: %d, Время: %s\n", getpid(), asctime(tm_info));

    // Создание pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();  // Создаем дочерний процесс
    switch(pid) {
    case -1:{
        perror("fork");
        exit(EXIT_FAILURE);
    }

    case 0:{  // Дочерний процесс
        tm_info = localtime(&now);
        char local_time[64];
        strftime(local_time, sizeof(local_time), "%Y-%m-%d %H:%M:%S", tm_info);
        printf("Дочерний процесс: Время: %s\n", asctime(tm_info));
        close(pipefd[1]);
        printf("Received: %s\n", buf);
        // Чтение данных из pipe
        int len = 0;
        while (len = read(pipefd[0], buf, sizeof(buf)) != 0) {
        read(2, buf, len);
        }
        close(pipefd[0]);
        break;
    } default: {  // Родительский процесс

        sleep(5);
        tm_info = localtime(&now);
        char local_time[64];
        strftime(local_time, sizeof(local_time), "%Y-%m-%d %H:%M:%S", tm_info);
        printf("Родительский процесс: Время: %s\n", asctime(tm_info));
        close(pipefd[0]);
        // Пишем данные в pipe
        write(pipefd[1], buf, strlen(buf) + 1);
        close(pipefd[1]);
        break;
    }
    }
    return 0;
}
