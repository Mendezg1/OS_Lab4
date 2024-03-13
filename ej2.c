#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define LEFT_FORK (philosopher_id + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS
#define RIGHT_FORK (philosopher_id + 1) % NUM_PHILOSOPHERS

sem_t forks[NUM_PHILOSOPHERS];
sem_t mutex;

void *philosopher(void *arg) {
    int philosopher_id = *((int *)arg);

    while (1) {
        printf("Philosopher %d is thinking\n", philosopher_id);

        sem_wait(&mutex);
        sem_wait(&forks[LEFT_FORK]);
        sem_wait(&forks[RIGHT_FORK]);
        sem_post(&mutex);

        // Eating
        printf("Philosopher %d is eating\n", philosopher_id);
        sleep(2); 

        sem_post(&forks[LEFT_FORK]);
        sem_post(&forks[RIGHT_FORK]);
    }
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    sem_init(&mutex, 0, 1);
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        sem_init(&forks[i], 0, 1);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_join(philosophers[i], NULL);
    }

    sem_destroy(&mutex);
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        sem_destroy(&forks[i]);
    }

    return 0;
}
