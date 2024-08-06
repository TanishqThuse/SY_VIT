#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

// Shared buffer and semaphores
int buffer[BUFFER_SIZE];
int in = 0, out = 0;
sem_t empty, full, mutex;

// Producer thread function
void* producer(void* arg) {
    for (int i = 0; i < 10; i++) {
        sem_wait(&empty);  // Wait for empty slot
        sem_wait(&mutex);  // Enter critical section

        buffer[in] = i;    // Produce an item
        printf("Produced: %d\n", i);
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex);  // Exit critical section
        sem_post(&full);   // Signal that buffer has an item
    }
    return NULL;
}

// Consumer thread function
void* consumer(void* arg) {
    for (int i = 0; i < 10; i++) {
        sem_wait(&full);   // Wait for an item
        sem_wait(&mutex);  // Enter critical section

        int item = buffer[out];  // Consume an item
        printf("Consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex);  // Exit critical section
        sem_post(&empty);  // Signal that buffer has an empty slot
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);  // Buffer starts empty
    sem_init(&full, 0, 0);             // Buffer starts with no items
    sem_init(&mutex, 0, 1);            // Mutex for critical section

    // Create producer and consumer threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}

