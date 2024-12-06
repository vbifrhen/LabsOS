#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define SHM_SIZE 1024
#define FTOK_PATH "."

typedef struct {
    pid_t pid;
    char time_str[64];
} shared_data;

int main() {
    int shmid;
    key_t shm_key;
    shared_data *data;

    // Генерация уникального ключа
    shm_key = ftok(FTOK_PATH, 'A');
    if (shm_key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Подключаемся к существующему сегменту разделяемой памяти
    shmid = shmget(shm_key, SHM_SIZE, 0666);
    if (shmid == -1) {
        perror("shmget");
        printf("Ошибка: разделяемая память не создана.\n");
        exit(EXIT_FAILURE);
    }

    // Присоединяем разделяемую память
    data = (shared_data *)shmat(shmid, NULL, 0);
    if (data == (void *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    printf("Принимающая программа запущена. PID: %d, SHM_KEY: %d\n", getpid(), shm_key);

    // Бесконечный цикл чтения данных
    while (1) {
        time_t now = time(NULL);
        char *local_time = strtok(asctime(localtime(&now)), "\n");
        
        printf("Принимающий процесс: PID: %d, Время: %s | Принято от PID: %d, Время: %s", getpid(), local_time, data->pid, data->time_str);
        sleep(1);
    }

    if (shmdt(shared_memory) == -1) {
        perror("shmdt failed");
    } else {
        printf("Принимающая программа: сегмент памяти успешно отсоединён.\n");
    }

    return 0;
}
