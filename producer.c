#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "shared_memory.h"

void producer() {
    while (1) {
        int item = rand() % 100;

        wait_semaphore(1);

        wait_semaphore(0);

        shm_ptr->buffer[shm_ptr->in] = item;
        shm_ptr->in = (shm_ptr->in + 1) % BUFFER_SIZE;
        shm_ptr->count++;
        printf("Producer produced item %d\n", item);

        signal_semaphore(1);

        signal_semaphore(0);

        sleep(rand() % 3);
    }
}

int main() {
    setup_shared_memory();

    if (fork() == 0) {
        execl("./consumer", "consumer", NULL);
    } else {
        producer();
    }

    cleanup_shared_memory();
    return 0;
}