# Producer_Consumer_Problem
Overview
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

