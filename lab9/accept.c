#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>

#define SHM_KEY 0x1234
#define SEM_KEY 0x5678
#define MAX_LEN 256

struct shared_data {
    char message[MAX_LEN];
    pid_t sender_pid;
};

// Semaphore operations
void sem_lock(int sem_id) {
    struct sembuf sb = {0, -1, 0};
    semop(sem_id, &sb, 1);
}

void sem_unlock(int sem_id) {
    struct sembuf sb = {0, 1, 0};
    semop(sem_id, &sb, 1);
}

int main() {
    int sem_id = semget(SEM_KEY, 1, 0666);
    if (sem_id == -1) {
        perror("Failed to access semaphore");
        exit(1);
    }

    printf("Receiver started. PID: %d\\n", getpid());

    while (1) {
        sem_lock(sem_id);

        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        printf("Receiver PID: %d, Current time: %02d:%02d:%02d, Received: %s (from PID: %d)\\n",
               getpid(), t->tm_hour, t->tm_min, t->tm_sec, data->message, data->sender_pid);

        sem_unlock(sem_id);
        sleep(1);
    }

    return 0;
}
