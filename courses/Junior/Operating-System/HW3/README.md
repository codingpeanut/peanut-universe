# Homework III: Producer-Consumer Problem

## Overview
- The producer and consumer will run as separate threads and move items to and from a buffer that is synchronized with semaphores and mutex locks.
- You need to use the Pthreads API to solve the problem.

## Requirements
1. **Define `buffer_item` data type (typedef) and operations**  
   - Define `buffer_item` in `buffer.h`.
   - Implement `insert_item` to insert data produced by the producer into the buffer.
   - Implement `remove_item` to remove data from the buffer and return it to the consumer.

2. **Producer Threads**
   - The producer threads will:
     - Sleep for a random amount of time.
     - Generate random data (you can define the data type).
     - Insert the data into the buffer.
     - If insertion is successful, print the produced data.
     - If insertion fails, print an error message.
   ```c
   while (true) {
       sleep(rand()); // Sleep for a random period
       item = produced(); // Generate random data item
       if (insert_item(item)) {
           printf("producer produced %x\n", item); // Insert item into synchronized buffer
       } else {
           fprintf("report error");
       }
   }
   ```

3. **Consumer Threads**
   - The consumer threads will:
     - Sleep for a random amount of time.
     - Remove data from the buffer and print the consumed data.
     - If removal is successful, print the consumed data.
     - If removal fails, print an error message.
   ```c
   while (true) {
       sleep(rand()); // Sleep for a random period
       if (remove_item(&item)) { // Get item from synchronized buffer
           printf("consumer consumed %x\n", item);
       } else {
           fprintf("report error");
       }
   }
   ```

4. **Pthread Creation and Synchronization**
   - Create threads using the Pthreads API.
   - Use mutex locks and semaphores to synchronize access to the buffer (i.e., control buffer access).

5. **Main Function Parameters**
   - The `main()` function should accept three parameters from the command line:
     1. How long the program should run before terminating.
     2. The number of producer threads.
     3. The number of consumer threads.

6. **Output Requirements**
   - When a producer produces data and inserts it into the buffer, output the data content and the producer's ID.
   - When a consumer consumes data, output the data content and the consumer's ID.

## Additional Requirements
- Use **pthread unnamed semaphores** and **pthread mutex locks** for synchronization.

- pthreads mutex Locks
```c
#include <pthread.h>

////create and init the mutex lock
pthread_mutex_t mutex;
pthread_mutex_init(&mutex, NULL);

//acquire the mutex lock
pthread_mutex_lock(&mutex);

/***********************

   Critical Section

************************/

//release the mutex lock
pthread_mutex_unlock(&mutex);
```

- pthread unnamed semaphores
```c
#include <semaphore.h>

//create and init the semaphore to 1 
sem_t sem; 
sem_init(&sem,0,1); 

//acquire the semaphore
sem_wait(&sem);

/***********************

   Critical Section

************************/

//release the mutex lock
sem_post(&mutex);
```

### Use `compile.sh` to compile HW3
1. run `chmod +x compile.sh`
2. run `./compile.sh`
3. run `./s411440521HW3 <sleep_time> <num_producers> <num_consumers>`

### Compile directly
1. run `gcc -o s411440521HW3 main.c lib/buffer.c -Iinclude -lpthread`
2. run `./s411440521HW3 <sleep_time> <num_producers> <num_consumers>`
