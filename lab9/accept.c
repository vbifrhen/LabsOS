#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <signal.h>

#define FTOK_PATH "."

int semid; // Глобальная переменная для идентификатора семафора

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
    printf("Принимающая программа завершена. PID: %d\n", getpid());
    exit(0);
}

int main() {
    key_t sem_key;

    // Устанавливаем обработчики сигналов
    signal(SIGINT, cleanup);   // Ctrl+C
    signal(SIGTERM, cleanup);  // Команда kill
    signal(SIGQUIT, cleanup);  // Ctrl+"\""

    // Генерация уникального ключа для семафора
    sem_key = ftok(FTOK_PATH, 'A');
    if (sem_key == -1) {
        perror("Ошибка генерации ключа ftok для семафора");
        exit(EXIT_FAILURE);
    }

    // Получение идентификатора семафора
    semid = semget(sem_key, 1, 0666);
    if (semid == -1) {
        perror("semget failed");
        exit(EXIT_FAILURE);
    }

    printf("Принимающая программа запущена. PID: %d\n", getpid());

    // Основной цикл приёма данных
    while (1) {
        sem_lock(semid);

        // Текущее время принимающей программы
        time_t now = time(NULL);
        char *local_time = strtok(asctime(localtime(&now)), "\n");

        printf("Принято: Текущее время приёмника: %s (PID: %d)\n", local_time, getpid());

        sem_unlock(semid);
        sleep(1); // Ожидание для имитации обработки
    }

    return 0;
}