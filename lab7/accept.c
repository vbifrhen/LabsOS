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

    // Подключаемся к существующему сегменту разделяемой памяти
    shmid = shmget(SHM_KEY, SHM_SIZE, 0666);
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

    printf("Принимающая программа запущена. PID: %d\n", getpid());

    // Бесконечный цикл чтения данных
    while (1) {
        time_t now = time(NULL);
        struct tm *tm_info = localtime(&now);
        char local_time[64];
        strftime(local_time, sizeof(local_time), "%Y-%m-%d %H:%M:%S", tm_info);

        printf("Принимающий процесс: PID: %d, Время: %s\n", getpid(), local_time);
        printf("Принято от PID: %d, Время: %s\n", data->pid, data->time_str);

        sleep(1);
    }

    return 0;
}
