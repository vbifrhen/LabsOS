#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define NUM_READERS 10
#define ARRAY_SIZE 20

// Общий массив для записи и чтения
char shared_array[ARRAY_SIZE];
int write_index = 0;

// rwlock для синхронизации доступа
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

// Функция для пишущего потока
void* writer_thread() {
    for (int i = 1; i <= ARRAY_SIZE; i++) {
        // Блокировка для записи
        pthread_rwlock_wrlock(&rwlock);

        // Записываем число в массив
        int written = snprintf(shared_array + write_index, ARRAY_SIZE - write_index, "%d ", i);
        if (written < 0 || write_index + written >= ARRAY_SIZE) {
            printf("Writer: недостаточно места в массиве\n");
            pthread_rwlock_unlock(&rwlock);
            break;
        }

        printf("Writer: записал %d в массив (индекс %d)\n", i, write_index);
        write_index += written;


        sleep(1);
        // Освобождаем блокировку записи
        pthread_rwlock_unlock(&rwlock);


    }

    return NULL;
}

// Функция для читающих потоков
void* reader_thread(void* arg) {
    long tid = (long)arg;

    while (1) {
        // Блокировка для чтения
        pthread_rwlock_rdlock(&rwlock);

        // Выводим содержимое массива
        printf("Reader %ld: %s\n", tid, shared_array);

        // Освобождаем блокировку чтения
        pthread_rwlock_unlock(&rwlock);

        usleep(100000);
    }

    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS];
    pthread_t writer;

    // Создаем пишущий поток
    pthread_create(&writer, NULL, writer_thread, NULL);

    // Создаем читающие потоки
    for (long i = 0; i < NUM_READERS; i++) {
        pthread_create(&readers[i], NULL, reader_thread, (void*)i);
    }

    // Ожидаем завершения работы пишущего потока
    pthread_join(writer, NULL);

    // Завершаем чтение (неблокируемо, просто прерываем потоки)
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_cancel(readers[i]);
        pthread_join(readers[i], NULL);
    }

    return 0;
}
