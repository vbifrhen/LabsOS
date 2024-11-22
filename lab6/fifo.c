#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_NAME "/tmp/my_fifo"

int main() {
    pid_t pid;
    char buf[1024];
    struct tm *tm_info;

    // Создание именованного канала (FIFO)
    if (mkfifo(FIFO_NAME, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    pid = fork();  // Создаем дочерний процесс
    switch (pid) {
    case -1: {
        perror("fork");
        unlink(FIFO_NAME);  // Удаляем FIFO при ошибке
        exit(EXIT_FAILURE);
    }

    case 0: {  // Дочерний процесс

        // Получение текущего времени
        time_t now = time(NULL);
        tm_info = localtime(&now);
        printf("Дочерний процесс: Время: %s\n", asctime(tm_info));

        // Открытие FIFO на чтение
        int fd = open(FIFO_NAME, O_RDONLY);
        if (fd == -1) {
            perror("open (child)");
            unlink(FIFO_NAME);  // Удаляем FIFO
            exit(EXIT_FAILURE);
        }

        // Чтение данных из FIFO
        int len = 0;
        while ((len = read(fd, buf, sizeof(buf))) > 0) {
            write(STDOUT_FILENO, buf, len);  // Выводим данные на экран
        }

        close(fd);
        unlink(FIFO_NAME);  // Удаляем FIFO
        break;
    }

    default: {  // Родительский процесс
        // Открытие FIFO на запись
        int fd = open(FIFO_NAME, O_WRONLY);
        if (fd == -1) {
            perror("open (parent)");
            unlink(FIFO_NAME);  // Удаляем FIFO
            exit(EXIT_FAILURE);
        }
        sleep(5); // Задержка для разницы во времени
        // Получение текущего времени
        time_t now = time(NULL);
        tm_info = localtime(&now);

        sprintf(buf, "Родительский процесс: Время: %s\nPID: %d\n", asctime(tm_info), getpid());



        // Запись данных в FIFO
        write(fd, buf, strlen(buf));
        close(fd);
        break;
    }
    }

    return 0;
}
