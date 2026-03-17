#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 10
#define PRODUCERS 3
#define CONSUMERS 4

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

// Semaphores
sem_t empty, full, mutex;

// Function to display buffer
void display_buffer() {
    printf("Buffer: ");
    for(int i = 0; i < BUFFER_SIZE; i++) {
        if(buffer[i] == 1)
            printf("1 ");
        else
            printf("_ ");
    }
    printf("\n");
}

// Producer function
void* producer(void* arg) {
    int id = *((int*)arg);

    while(1) {
        sleep(1); // simulate order creation delay

        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = 1;  // produce item
        printf("Order Taker %d produced order at position %d\n", id, in);

        in = (in + 1) % BUFFER_SIZE;

        display_buffer();

        sem_post(&mutex);
        sem_post(&full);
    }
}

// Consumer function
void* consumer(void* arg) {
    int id = *((int*)arg);

    while(1) {
        sleep(2); // simulate cooking time

        sem_wait(&full);
        sem_wait(&mutex);

        buffer[out] = 0;  // consume item
        printf("Chef %d consumed order from position %d\n", id, out);

        out = (out + 1) % BUFFER_SIZE;

        display_buffer();

        sem_post(&mutex);
        sem_post(&empty);

        printf("Chef %d is preparing the order\n", id);
    }
}

int main() {
    pthread_t prod[PRODUCERS], cons[CONSUMERS];
    int prod_id[PRODUCERS], cons_id[CONSUMERS];

    // Initialize buffer (0 = empty)
    for(int i = 0; i < BUFFER_SIZE; i++)
        buffer[i] = 0;

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    // Create producer threads
    for(int i = 0; i < PRODUCERS; i++) {
        prod_id[i] = i + 1;
        pthread_create(&prod[i], NULL, producer, &prod_id[i]);
    }

    // Create consumer threads
    for(int i = 0; i < CONSUMERS; i++) {
        cons_id[i] = i + 1;
        pthread_create(&cons[i], NULL, consumer, &cons_id[i]);
    }

    // Join threads
    for(int i = 0; i < PRODUCERS; i++)
        pthread_join(prod[i], NULL);

    for(int i = 0; i < CONSUMERS; i++)
        pthread_join(cons[i], NULL);

    return 0;
}
