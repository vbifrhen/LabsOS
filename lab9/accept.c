#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <signal.h>

#define FTOK_PATH "."
#define MAX_STR_SIZE 64

int semid; // Глобальная переменная для идентификатора семафора
char shared_data[MAX_STR_SIZE]; // Разделяемая строка для данных

// Операции над семафором
void sem_lock(int semid) {
    struct sembuf sb = {0, -1, 0};
    if (semop(semid, &sb, 1) == -1) {
        perror("semop lock failed");
        exit(EXIT_FAILURE);
    }
}

void sem_unlock(int semid) {
    struct sembuf sb = {0, 1, 0};
    if (semop(semid, &sb, 1) == -1) {
        perror("semop unlock failed");
        exit(EXIT_FAILURE);
    }
}

void cleanup() {
    printf("Принимающая программа завершает работу. PID: %d\n", getpid());
    exit(0);
}

int main() {
    key_t sem_key;

    // Устанавливаем обработчики сигналов
    signal(SIGINT, cleanup);   // Ctrl+C
    signal(SIGTERM, cleanup);  // Команда kill
    signal(SIGQUIT, cleanup);  // Ctrl+"\"

    // Генерация уникального ключа для семафора
    sem_key = ftok(FTOK_PATH, 'A');
    if (sem_key == -1) {
        perror("Ошибка генерации ключа ftok для семафора");
        exit(EXIT_FAILURE);
    }

    // Подключение к существующему семафору
    semid = semget(sem_key, 1, 0666);
    if (semid == -1) {
        perror("semget");
        fprintf(stderr, "Ошибка: передающая программа не запущена.\n");
        exit(EXIT_FAILURE);
    }

    printf("Принимающая программа запущена. PID: %d\n", getpid());

    // Основной цикл приёма данных
    while (1) {
        sem_lock(semid);

        // Имитация чтения данных из разделяемого ресурса
        time_t now = time(NULL);
        struct tm *tm_info = localtime(&now);
        snprintf(shared_data, sizeof(shared_data), asctime(tm_info), getpid());

        printf("Принято: %s\n", shared_data);

        sem_unlock(semid);
        sleep(1);
    }

    return 0;
}
