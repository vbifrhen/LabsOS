#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

// Обработчик выхода программы
void exit_handler() {
    printf("[AtExit] Программа завершила работу (ID: %d)\n", getpid());
}

// Обработчик сигнала SIGINT
void sigint_handler(int sig) {
    printf("[SIGINT] Получен сигнал (ID: %d)\n", sig);
}

// Обработчик сигнала SIGTERM
void sigterm_handler(int sig) {
    printf("[SIGTERM] Получен сигнал (ID: %d)\n", sig);
    exit(0);  // Корректное завершение родительского процесса
}

int main() {
    // Регистрация обработчика выхода
    if (atexit(exit_handler) != 0) {
        perror("Ошибка при установке обработчика выхода");
        return 1;
    }

    // Установка обработчика сигнала SIGINT
    if (signal(SIGINT, sigint_handler) == SIG_ERR) {
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

    pid_t child_pid = fork();

    if (child_pid < 0) {
        // Ошибка при вызове fork()
        perror("Ошибка при вызове fork()");
        exit(1);
    } else if (child_pid == 0) {
        // Дочерний процесс
        printf("Дочерний процесс. child_pid: %d\n", getpid());
        sleep(10);  // Дочерний процесс ждёт 5 секунд
        printf("Дочерний процесс завершен.\n");
        exit(0);
    } else {
        // Родительский процесс
        printf("Родительский процесс. child_pid: %d, дочерний child_pid: %d\n", getpid(), child_pid);
        waitpid(child_pid, NULL, 0);  // Ожидание завершения конкретного дочернего процесса
        printf("Родительский процесс после дочернего.\n");
    }

    return 0;
}
