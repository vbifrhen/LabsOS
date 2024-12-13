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
typedef struct {
    pid_t pid;
    char time_str[MAX_STR_SIZE];
} shared_data;

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
        strncpy(data->time_str, asctime(tm_info), sizeof(data->time_str) - 1);
        data->time_str[sizeof(data->time_str) - 1] = '\0'; // Удаляем лишние символы
        data->pid = getpid();

        sem_unlock(semid);#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <signal.h>

#define FTOK_PATH "."
#define MAX_STR_SIZE 64

int semid, shmid; // Идентификаторы семафора и разделяемой памяти
typedef struct {
    pid_t pid;
    char time_str[MAX_STR_SIZE];
} shared_data;

shared_data *data; // Указатель на структуру в разделяемой памяти

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

    // Удаляем разделяемую память
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl IPC_RMID failed");
    } else {
        printf("Передающая программа: разделяемая память удалена.\n");
    }
    exit(0);
}

int main() {
    key_t key;

    // Устанавливаем обработчики сигналов
    signal(SIGINT, cleanup);   // Ctrl+C
    signal(SIGTERM, cleanup);  // Команда kill
    signal(SIGQUIT, cleanup);  // Ctrl+"\"

    // Генерация уникального ключа
    key = ftok(FTOK_PATH, 'A');
    if (key == -1) {
        perror("Ошибка генерации ключа ftok");
        exit(EXIT_FAILURE);
    }

    // Создание семафора
    semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0666);
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

    // Создание разделяемой памяти
    shmid = shmget(key, sizeof(shared_data), IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        semctl(semid, 0, IPC_RMID);
        exit(EXIT_FAILURE);
    }

    // Привязка разделяемой памяти
    data = (shared_data *)shmat(shmid, NULL, 0);
    if (data == (void *)-1) {
        perror("shmat");
        shmctl(shmid, IPC_RMID, NULL);
        semctl(semid, 0, IPC_RMID);
        exit(EXIT_FAILURE);
    }

    printf("Передающая программа запущена. PID: %d\n", getpid());

    // Основной цикл передачи данных
    while (1) {
        sem_lock(semid);

        // Запись текущего времени в разделяемую память
        time_t now = time(NULL);
        struct tm *tm_info = localtime(&now);
        strncpy(data->time_str, asctime(tm_info), sizeof(data->time_str) - 1);
        data->time_str[sizeof(data->time_str) - 1] = '\0'; // Удаляем лишние символы
        data->pid = getpid();

        sem_unlock(semid);
        sleep(3);
    }

    return 0;
}

        sleep(3);
    }

    return 0;
}
