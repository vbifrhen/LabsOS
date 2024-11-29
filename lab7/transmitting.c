#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define SHM_SIZE 1024
#define FTOK_PATH "/tmp"

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

    // Создание разделяемой памяти
    shmid = shmget(shm_key, SHM_SIZE, IPC_CREAT | IPC_EXCL | 0666);
    if (shmid == -1) {
        perror("shmget");
        printf("Передающая программа уже запущена. Завершение.\n");
        exit(EXIT_FAILURE);
    }

    // Присоединяем разделяемую память
    data = (shared_data *)shmat(shmid, NULL, 0);
    if (data == (void *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    printf("Передающая программа запущена. PID: %d, SHM_KEY: %d\n", getpid(), shm_key);

    // Бесконечный цикл передачи данных
    while (1) {
        time_t now = time(NULL);
        struct tm *tm_info = localtime(&now);
        strncpy(data->time_str, asctime(tm_info), sizeof(data->time_str) - 1);
        data->time_str[sizeof(data->time_str) - 1] = '\0'; // Удаляем лишние символы
        data->pid = getpid();

        sleep(1);
    }

    return 0;
}
