#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdint.h>

#define BUFFER_SIZE 5
typedef int buffer_item;

buffer_item buffer[BUFFER_SIZE];
int insert_index = 0, remove_index = 0;

sem_t empty, full;
pthread_mutex_t mutex;

int insert_item(buffer_item item) {
    sem_wait(&empty);               
    pthread_mutex_lock(&mutex);     

    buffer[insert_index] = item;
    insert_index = (insert_index + 1) % BUFFER_SIZE;

    pthread_mutex_unlock(&mutex);   
    sem_post(&full);                
    return 1;
}

int remove_item(buffer_item *item) {
    sem_wait(&full);                
    pthread_mutex_lock(&mutex);     

    *item = buffer[remove_index];
    remove_index = (remove_index + 1) % BUFFER_SIZE;

    pthread_mutex_unlock(&mutex);   
    sem_post(&empty);               
    return 1;
}

void *producer(void *param) {
    intptr_t thread_id = (intptr_t)param;

    while (1) {
        sleep(rand() % 3);  

        // 產生隨機數，確保不是 0
        buffer_item item = rand() % 100 + 1;  // 保證資料不為 0

        if (insert_item(item)) {
            printf("Producer %ld produced %d\n", thread_id, item);
        } else {
            fprintf(stderr, "Producer %ld failed to produce.\n", thread_id);
        }
    }
}

void *consumer(void *param) {
    intptr_t thread_id = (intptr_t)param;

    while (1) {
        sleep(rand() % 3);  

        buffer_item item;
        if (remove_item(&item)) {
            printf("Consumer %ld consumed %d\n", thread_id, item);
        } else {
            fprintf(stderr, "Consumer %ld failed to consume.\n", thread_id);
        }
    }
}

int main() {
    int sleep_time, num_producers, num_consumers;

    // 設置隨機數生成器種子
    srand(time(NULL));

    printf("Enter the program duration (in seconds): ");
    scanf("%d", &sleep_time);
    printf("Enter the number of producer threads: ");
    scanf("%d", &num_producers);
    printf("Enter the number of consumer threads: ");
    scanf("%d", &num_consumers);

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_t producers[num_producers];
    pthread_t consumers[num_consumers];

    for (int i = 0; i < num_producers; i++) {
        pthread_create(&producers[i], NULL, producer, (void *)(intptr_t)i);
    }

    for (int i = 0; i < num_consumers; i++) {
        pthread_create(&consumers[i], NULL, consumer, (void *)(intptr_t)i);
    }

    sleep(sleep_time);

    printf("Main program exiting.\n");
    return 0;
}

