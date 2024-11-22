#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char buf[1024];
    struct tm *tm_info;

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
        time_t now = time(NULL);
        tm_info = localtime(&now);
        printf("Дочерний процесс: Время: %s\n", asctime(tm_info));
        close(pipefd[1]);
        // Чтение данных из pipe
        int len = 0;
        while ((len = read(pipefd[0], buf, sizeof(buf))) != 0) {
        write(2, buf, len);
        }
        close(pipefd[0]);
        break;
    } default: {  // Родительский процесс

        sleep(5);
        time_t now = time(NULL);    
        tm_info = localtime(&now);
        sprintf(buf,"Родительский процесс: Время: %s\nPID: %d\n", asctime(tm_info), getpid());
        close(pipefd[0]);
        // Пишем данные в pipe
        write(pipefd[1], buf, strlen(buf));
        close(pipefd[1]);
        break;
    }
    }
    return 0;
}
