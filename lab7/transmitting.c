#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <signal.h>

#define SHM_SIZE 1024
#define FTOK_PATH "."

typedef struct {
    pid_t pid;
    char time_str[64];
} shared_data;

int shmid; // Глобальная переменная для хранения идентификатора разделяемой памяти

void cleanup() {
    // Удаляем сегмент разделяемой памяти
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
    } else {
        printf("Сегмент разделяемой памяти успешно удален. Завершение программы.\n");
    }
    exit(0);
}

int main() {
    key_t shm_key;
    shared_data *data;

    // Устанавливаем обработчики сигналов
    signal(SIGINT, cleanup);   // Ctrl+C
    signal(SIGTERM, cleanup);  // Команда kill
    signal(SIGQUIT, cleanup);  // Ctrl+"\""

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

    // Автоматическое удаление сегмента после отсоединения всех процессов
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
    }

    // Присоединяем разделяемую память
    data = (shared_data *)shmat(shmid, NULL, 0);
    if (data == (void *)-1) {
        perror("shmat");
        cleanup(0); // Удаляем сегмент, если ошибка в `shmat`
    }

    printf("Передающая программа запущена. PID: %d, SHM_KEY: %d\n", getpid(), shm_key);

    // Бесконечный цикл передачи данных
    while (1) {
        time_t now = time(NULL);
        struct tm *tm_info = localtime(&now);
        strncpy(data->time_str, asctime(tm_info), sizeof(data->time_str) - 1);
        data->time_str[sizeof(data->time_str) - 1] = '\0'; // Удаляем лишние символы
        data->pid = getpid();

        sleep(3);
    }

    return 0;
}
