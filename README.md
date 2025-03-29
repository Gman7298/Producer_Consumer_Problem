# Producer_Consumer_Problem
Readme:
Overview: 
This project implements the Producer-Consumer Problem using shared memory (shm) and semaphores (sem) in C. The producer process generates items and stores them in a shared buffer, while the consumer retrieves them.
Requirements
•	Linux environment
•	GCC compiler
•	Shared memory and semaphores
Compilation & Execution
# Compile producer and consumer
gcc producer.c -pthread -lrt -o producer
gcc consumer.c -pthread -lrt -o consumer

# Run the producer and consumer
./producer & ./consumer &
Expected Output
The producer generates items and the consumer consumes them, ensuring synchronization using semaphores.

Documentation:
Producer-Consumer Implementation Details
Introduction
The Producer-Consumer problem demonstrates inter-process communication (IPC) using shared memory and semaphores.
Key Concepts
•	Shared Memory: Used for storing items between processes.
•	Semaphores: Used for synchronization to prevent race conditions.
•	Fork(): Used to create a separate process for consumer.
Implementation Details
1.	Shared Memory Setup
o	shm_open() is used to create shared memory.
o	mmap() maps memory for IPC.
2.	Semaphores for Synchronization
o	sem_init() initializes semaphores.
o	sem_wait() and sem_post() manage buffer access.
3.	Forking Process
o	fork() is used to create consumer process.
Cleanup
•	Use shm_unlink() to remove shared memory.
•	Use sem_destroy() to clean up semaphores.

