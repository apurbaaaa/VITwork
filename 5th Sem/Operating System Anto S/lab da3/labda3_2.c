#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define NUM_PHILOSOPHERS 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (id + 4) % NUM_PHILOSOPHERS
#define RIGHT (id + 1) % NUM_PHILOSOPHERS

int status[NUM_PHILOSOPHERS];
int philosopherID[NUM_PHILOSOPHERS] = { 0, 1, 2, 3, 4 };

sem_t accessLock;
sem_t sync[NUM_PHILOSOPHERS];

void check(int id) {
    if (status[id] == HUNGRY && status[LEFT] != EATING && status[RIGHT] != EATING) {
        status[id] = EATING;
        sleep(2);
        printf("Philosopher %d picks up forks %d and %d\n", id + 1, LEFT + 1, id + 1);
        printf("Philosopher %d is Eating\n", id + 1);
        sem_post(&sync[id]);
    }
}

void pickFork(int id) {
    sem_wait(&accessLock);
    status[id] = HUNGRY;
    printf("Philosopher %d is Hungry\n", id + 1);
    check(id);
    sem_post(&accessLock);
    sem_wait(&sync[id]);
    sleep(1);
}

void releaseFork(int id) {
    sem_wait(&accessLock);
    status[id] = THINKING;
    printf("Philosopher %d puts down forks %d and %d\n", id + 1, LEFT + 1, id + 1);
    printf("Philosopher %d is thinking\n", id + 1);
    check(LEFT);
    check(RIGHT);
    sem_post(&accessLock);
}

void* philosopher(void* num) {
    while (1) {
        int* id = num;
        sleep(1);
        pickFork(*id);
        sleep(0);
        releaseFork(*id);
    }
}

int main() {
    printf("22BCE0232 Siddharthh\n");
    int i;
    pthread_t thread_id[NUM_PHILOSOPHERS];
    sem_init(&accessLock, 0, 1);
    for (i = 0; i < NUM_PHILOSOPHERS; i++)
        sem_init(&sync[i], 0, 0);
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&thread_id[i], NULL, philosopher, &philosopherID[i]);
        printf("Philosopher %d is thinking\n", i + 1);
    }
    for (i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_join(thread_id[i], NULL);
}
