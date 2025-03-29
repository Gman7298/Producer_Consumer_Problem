#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>

#define BUFFER_SIZE 10

typedef struct {
    int buffer[BUFFER_SIZE];
    int in, out;
    sem_t full, empty, mutex;
} shared_data;

int main() {
    int shm_fd = shm_open("/shm_buffer", O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, sizeof(shared_data));
    shared_data *shm = mmap(NULL, sizeof(shared_data), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    sem_init(&shm->full, 1, 0);
    sem_init(&shm->empty, 1, BUFFER_SIZE);
    sem_init(&shm->mutex, 1, 1);
    shm->in = shm->out = 0;

    printf("Shared memory and semaphores initialized.\n");
    return 0;
}