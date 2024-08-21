#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t wrt;
pthread_mutex_t mutex;
int shared_data = 0;
int reader_count = 0;

void *writer(void *arg) {
    int writer_id = *((int *)arg);

    sem_wait(&wrt);


    shared_data++;
    printf("Writer %d wrote data: %d\n", writer_id, shared_data);

    sem_post(&wrt);
    return NULL;
}

void *reader(void *arg) {
    int reader_id = *((int *)arg);

    pthread_mutex_lock(&mutex);
    reader_count++;
    if (reader_count == 1) {
        sem_wait(&wrt);
    }
    pthread_mutex_unlock(&mutex);

    printf("Reader %d read data: %d\n", reader_id, shared_data);

    pthread_mutex_lock(&mutex);
    reader_count--;
    if (reader_count == 0) {
        sem_post(&wrt);
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    pthread_t rtid[5], wtid[5];
    int ids[5] = {1, 2, 3, 4, 5};

    sem_init(&wrt, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    // Creating reader threads
    for (int i = 0; i < 5; i++) {
        pthread_create(&rtid[i], NULL, reader, &ids[i]);
    }

    // Creating writer threads
    for (int i = 0; i < 5; i++) {
        pthread_create(&wtid[i], NULL, writer, &ids[i]);
    }

    // Joining all threads
    for (int i = 0; i < 5; i++) {
        pthread_join(rtid[i], NULL);
        pthread_join(wtid[i], NULL);
    }

    // Destroying the semaphore and mutex
    sem_destroy(&wrt);
    pthread_mutex_destroy(&mutex);

    return 0;
}

