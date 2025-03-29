#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 10

typedef struct {
    int buffer[BUFFER_SIZE];
    int in, out, count;
} SharedData;

int shm_id;
SharedData *shm_ptr;
int sem_id;

void setup_shared_memory() {
    shm_id = shmget(IPC_PRIVATE, sizeof(SharedData), IPC_CREAT | 0666);
    if (shm_id == -1) {
        perror("shmget failed");
        exit(1);
    }

    shm_ptr = (SharedData *)shmat(shm_id, NULL, 0);
    if (shm_ptr == (SharedData *)-1) {
        perror("shmat failed");
        exit(1);
    }

    shm_ptr->in = 0;
    shm_ptr->out = 0;
    shm_ptr->count = 0;

    sem_id = semget(IPC_PRIVATE, 2, IPC_CREAT | 0666);
    if (sem_id == -1) {
        perror("semget failed");
        exit(1);
    }

    semctl(sem_id, 0, SETVAL, 1);
    semctl(sem_id, 1, SETVAL, BUFFER_SIZE);
}

void cleanup_shared_memory() {
    if (shmdt(shm_ptr) == -1) {
        perror("shmdt failed");
    }

    if (shmctl(shm_id, IPC_RMID, NULL) == -1) {
        perror("shmctl failed");
    }

    if (semctl(sem_id, 0, IPC_RMID) == -1) {
        perror("semctl failed");
    }
}

void wait_semaphore(int sem_num) {
    struct sembuf sb = {sem_num, -1, 0};
    semop(sem_id, &sb, 1);
}

void signal_semaphore(int sem_num) {
    struct sembuf sb = {sem_num, 1, 0};
    semop(sem_id, &sb, 1);
}

#endif
