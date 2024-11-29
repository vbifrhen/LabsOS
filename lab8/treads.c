#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_READERS 10
#define NUM_WRITERS 1
#define ARRAY_SIZE 50

// Общий массив для записи и чтения
char shared_array[ARRAY_SIZE];

// Мьютекс для синхронизации доступа к массиву
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Функция для пишущего потока
void* writer_thread(void* arg) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        pthread_mutex_lock(&mutex); // Захватываем мьютекс

        // Записываем в массив номер записи
        sprintf(shared_array + i, "%d", i + 1);

        printf("Writer: записал %d в индекс %d\n", i + 1, i);

        pthread_mutex_unlock(&mutex); // Освобождаем мьютекс

        usleep(100000); // Задержка для имитации работы
    }
    return NULL;
}

// Функция для читающих потоков
void* reader_thread(void* arg) {
    long tid = (long)arg;
    while (1) {
        pthread_mutex_lock(&mutex); // Захватываем мьютекс

        printf("Reader %ld: ", tid);
        for (int i = 0; i < ARRAY_SIZE; i++) {
            printf("%c ", shared_array[i] ? shared_array[i] : '.');
        }
        printf("\n");

        pthread_mutex_unlock(&mutex); // Освобождаем мьютекс

        usleep(100000); // Задержка для имитации работы
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

    // Ожидаем завершения работы всех потоков
    pthread_join(writer, NULL);
    for (int i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    // Завершаем работу
    pthread_mutex_destroy(&mutex);
    return 0;
}
