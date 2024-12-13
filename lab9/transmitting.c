#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    // Удаляем семафор
    if (semctl(semid, 0, IPC_RMID) == -1) {
        perror("semctl IPC_RMID failed");
    } else {
        printf("Передающая программа: семафор удалён.\n");
    }
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

    // Создание семафора
    semid = semget(sem_key, 1, IPC_CREAT | IPC_EXCL | 0666);
    if (semid == -1) {
        perror("semget");
        fprintf(stderr, "Ошибка: передающая программа уже запущена.\n");
        exit(EXIT_FAILURE);
    }

    // Инициализация семафора значением 1
    if (semctl(semid, 0, SETVAL, 1) == -1) {
        perror("semctl SETVAL failed");
        semctl(semid, 0, IPC_RMID);
        exit(EXIT_FAILURE);
    }

    printf("Передающая программа запущена. PID: %d\n", getpid());

    // Основной цикл передачи данных
    while (1) {
        sem_lock(semid);

        // Запись текущего времени в общий буфер
        time_t now = time(NULL);
        struct tm *tm_info = localtime(&now);
        snprintf(shared_data, sizeof(shared_data), asctime(tm_info), getpid());

        sem_unlock(semid);
        sleep(3);
    }

    return 0;
}
