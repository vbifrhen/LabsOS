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
int data_available = 0; // Флаг для проверки обновления данных

// Мьютекс и условная переменная для синхронизации
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condvar = PTHREAD_COND_INITIALIZER;

// Функция для пишущего потока
void* writer_thread() {
    for (int i = 1; i <= ARRAY_SIZE; i++) {
        pthread_mutex_lock(&mutex);

        // Записываем число в массив
        int written = snprintf(shared_array + write_index, ARRAY_SIZE - write_index, "%d ", i);
        if (written < 0 || write_index + written >= ARRAY_SIZE) {
            printf("Writer: недостаточно места в массиве\n");
            pthread_mutex_unlock(&mutex);
            break;
        }

        printf("Writer: записал %d в массив (индекс %d)\n", i, write_index);
        write_index += written;
        data_available = 1; // Устанавливаем флаг наличия новых данных

        // Уведомляем читающие потоки
        pthread_cond_broadcast(&condvar);

        pthread_mutex_unlock(&mutex);
        sleep(1);
    }

    return NULL;
}

// Функция для читающих потоков
void* reader_thread(void* arg) {
    long tid = (long)arg;

    while (1) {
        pthread_mutex_lock(&mutex);

        // Ждем сигнала от пишущего потока
        while (!data_available) {
            pthread_cond_wait(&condvar, &mutex);
        }

        // Выводим содержимое массива
        printf("Reader %ld: %s\n", tid, shared_array);

        pthread_mutex_unlock(&mutex);

        //sleep(1);
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

    // Освобождаем ресурсы
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condvar);

    return 0;
}
