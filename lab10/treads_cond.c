#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define NUM_READERS 10
#define ARRAY_SIZE 20

char shared_array[ARRAY_SIZE];
int write_index = 0;
int data_available = 0;
int current_reader = 0;
int stop_readers = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condvar = PTHREAD_COND_INITIALIZER;

void* writer_thread() {
    for (int i = 1; i <= ARRAY_SIZE; i++) {
        pthread_mutex_lock(&mutex);

        int written = snprintf(shared_array + write_index, ARRAY_SIZE - write_index, "%d ", i);
        if (written < 0 || write_index + written >= ARRAY_SIZE) {
            printf("Writer: недостаточно места в массиве\n");
            pthread_mutex_unlock(&mutex);
            break;
        }

        printf("Writer: записал %d в массив (индекс %d)\n", i, write_index);
        write_index += written;
        data_available = 1; //Флаг данных

        pthread_cond_broadcast(&condvar);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    //Когда кончилось место освобождаем Readers
    pthread_mutex_lock(&mutex);
    stop_readers = 1;
    // Уведомляем читающие потоки
    pthread_cond_broadcast(&condvar);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void* reader_thread(void* arg) {
    long tid = (long)arg;

    while (1) {
        pthread_mutex_lock(&mutex);
        //Проверка по пишущему потоку
        while (!data_available && !stop_readers) {
            pthread_cond_wait(&condvar, &mutex);
        }

        if (stop_readers) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        if (current_reader == tid) {
            printf("Reader %ld: %s\n", tid, shared_array);
            current_reader = (current_reader + 1) % NUM_READERS;

            if (current_reader == 0) {
                data_available = 0;
            }

            pthread_cond_broadcast(&condvar);
        }

        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS];
    pthread_t writer;

    pthread_create(&writer, NULL, writer_thread, NULL);

    for (long i = 0; i < NUM_READERS; i++) {
        pthread_create(&readers[i], NULL, reader_thread, (void*)i);
    }

    pthread_join(writer, NULL);

    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    return 0;
}
