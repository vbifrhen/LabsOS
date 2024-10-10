#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>


// Обработка выхода проги
void exit_handler() {
    printf("Прога завершила работу\n");
}

// Обработка сигнала SIGNIT
void signal_handler(int sig) {
    printf("Получен сигнал SIGINT (ID: %d)\n", sig);
}

// Обработка сигнала SIGTERM
void sigterm_handler(int sig) {
    printf("Получен сигнал SIGINT (ID: %d)\n", sig);
}

int main() {
    // Установка обработчика выхода
    if (atexit(exit_handler) != 0) {
        perror("Ошибка при установке обработчика выхода");
        return 1;
    }

    // Установка сигнала SIGINT
    if (signal(SIGINT, signal_handler) == SIG_ERR) {
        perror("Ошибка при установке обработчика SIGINT");
        return 1;
    }

    // Установка обработчика сигнала SIGTERM через sigaction
    struct sigaction sa;
    sa.sa_handler = sigterm_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGTERM, &sa, NULL) == -1) {
        perror("Ошибка при установке обработчика SIGTERM");
        return 1;
    }
    
    pid_t pid = fork();

    if (pid < 0) {
        // Ошибка при вызове fork()
        perror("Ошибка при вызове fork()");
        exit(1);
    } else if (pid == 0) {
        // Дочерний процесс
        printf("Дочерний процесс. PID: %d\n", getpid());
        sleep(5); // Дочерний процесс ждет 5 секунд
        printf("Дочерний процесс завершен.\n");
        exit(0);
    } else {
        // Родительский процесс
        printf("Родительский процесс. PID: %d, дочерний PID: %d\n", getpid(), pid);
        wait(NULL); // Ожидание завершения дочернего процесса
        printf("Дочерний процесс завершился.\n");
    }

    return 0;
}