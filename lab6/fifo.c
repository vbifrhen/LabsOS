#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    const char *fifo_name = "/tmp/my_fifo";
    pid_t pid;
    char buf[1024];
    struct timeval tv;
    gettimeofday(&tv, NULL);  // Текущее время в секундах и микросекундах
    snprintf(buf, sizeof(buf), "Time: %ld.%06ld, PID: %d", tv.tv_sec, tv.tv_usec, getpid());

    // Создание FIFO
    if (mkfifo(fifo_name, 0666) == -1) {
        perror("mkfifo");
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

        // Открытие FIFO для чтения
        int fd = open(fifo_name, O_RDONLY);
        if (fd == -1) {
            perror("open fifo");
            exit(EXIT_FAILURE);
        }

        // Чтение данных из FIFO
        read(fd, buf, sizeof(buf));
        gettimeofday(&tv, NULL);
        printf("Child Process Time: %ld.%06ld\n", tv.tv_sec, tv.tv_usec);
        printf("Received: %s\n", buf);

        close(fd);
        unlink(fifo_name);  // Удаляем FIFO
    } else {  // Родительский процесс
        // Открытие FIFO для записи
        int fd = open(fifo_name, O_WRONLY);
        if (fd == -1) {
            perror("open fifo");
            exit(EXIT_FAILURE);
        }

        // Пишем данные в FIFO
        write(fd, buf, strlen(buf) + 1);
        close(fd);
    }

    return 0;
}
