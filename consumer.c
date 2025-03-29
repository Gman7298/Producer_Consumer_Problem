#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shared_memory.h"

void consumer() {
    while (1) {
        wait_semaphore(1);

        wait_semaphore(0);

        int item = shm_ptr->buffer[shm_ptr->out];
        shm_ptr->out = (shm_ptr->out + 1) % BUFFER_SIZE;
        shm_ptr->count--;
        printf("Consumer consumed item %d\n", item);

        signal_semaphore(1);

        signal_semaphore(0);

        sleep(rand() % 3);
    }
}

int main() {
    setup_shared_memory();

    consumer();

    cleanup_shared_memory();
    return 0;
}