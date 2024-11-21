#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#define SHM_KEY 0x1234
#define SHM_SIZE 1024

typedef struct {
    pid_t pid;
    char time_str[64];
} shared_data;

int main() {
    int shmid;
    shared_data *data;

    // Попытка создания разделяемой памяти
    shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | IPC_EXCL | 0666);
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

    printf("Передающая программа запущена. PID: %d\n", getpid());

    // Бесконечный цикл передачи данных
    while (1) {
        time_t now = time(NULL);
        struct tm *tm_info = localtime(&now);
        strftime(data->time_str, sizeof(data->time_str), "%Y-%m-%d %H:%M:%S", tm_info);
        data->pid = getpid();

        sleep(1);
    }

    return 0;
}
