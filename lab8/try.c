#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define THREAD_NUMBER 10
#define MAS_SIZE 10

pthread_mutex_t mtx; 
int mas[MAS_SIZE];
int count = 0;

void* write_func(void* arg) {
    usleep(1000);
    
    for (int i = 0; i < MAS_SIZE; ++i) {
        usleep(100000);
        pthread_mutex_lock(&mtx);
        count = i+1;
        mas[i] = count;
        pthread_mutex_unlock(&mtx);
    }
    //count += 1;
    
    pthread_exit(NULL);
}

void* read_func(void* arg) {
    usleep(100000);
    while (count < MAS_SIZE) {
        usleep(10000);
        pthread_mutex_lock(&mtx);
        printf("thread[%lx]\n", pthread_self());
        
        for (int i = 0; i < MAS_SIZE; ++i) {
            printf("%d ", mas[i]);
        }
        printf("\n");
        usleep(100000);
        pthread_mutex_unlock(&mtx);
    }
    
    pthread_exit(NULL);
}

int main() {
    pthread_mutex_init(&mtx, NULL);
    pthread_t read_thread[THREAD_NUMBER];
    pthread_t write_thread;
    pthread_create(&write_thread, NULL, write_func, NULL);
    for (int i = 0; i < THREAD_NUMBER; ++i) {
        int create_res = pthread_create(&read_thread[i], NULL, read_func, NULL);
        if(create_res != 0) {
			int err = errno;
			printf("ERROR IN CREATE: %s(%d)\n", strerror(err), err);
		}
    }

    for (int i = 0; i < THREAD_NUMBER; ++i) {
        void* res = NULL;
        int join_res = pthread_join(read_thread[i], &res);
        if (join_res != 0) {
            int err = errno;
            printf("ERROR IN JOIN:%s(%d)\n", strerror(err), err);
        }
    }
    void* res = NULL;
    int join_res = pthread_join(write_thread, &res);
    if (join_res != 0) {
        int err = errno;
        printf("ERROR IN JOIN:%s(%d)\n", strerror(err), err);
    }
    pthread_mutex_destroy(&mtx);
    return 0;
}