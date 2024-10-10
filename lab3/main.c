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
