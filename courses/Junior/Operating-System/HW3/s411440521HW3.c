#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdint.h>  // 引入 intptr_t

// 定義 buffer 相關參數
#define BUFFER_SIZE 5
typedef int buffer_item;

buffer_item buffer[BUFFER_SIZE];
int insert_index = 0, remove_index = 0;

// 同步工具
sem_t empty, full;
pthread_mutex_t mutex;

// 插入資料到 buffer
int insert_item(buffer_item item) {
    sem_wait(&empty);               // 等待空槽位
    pthread_mutex_lock(&mutex);     // 獲取互斥鎖

    // 插入資料
    buffer[insert_index] = item;
    insert_index = (insert_index + 1) % BUFFER_SIZE;

    pthread_mutex_unlock(&mutex);   // 釋放互斥鎖
    sem_post(&full);                // 增加已滿槽位
    return 1;
}

// 從 buffer 移除資料
int remove_item(buffer_item *item) {
    sem_wait(&full);                // 等待有資料
    pthread_mutex_lock(&mutex);     // 獲取互斥鎖

    // 移除資料
    *item = buffer[remove_index];
    remove_index = (remove_index + 1) % BUFFER_SIZE;

    pthread_mutex_unlock(&mutex);   // 釋放互斥鎖
    sem_post(&empty);               // 增加空槽位
    return 1;
}

// Producer thread 函數
void *producer(void *param) {
    intptr_t thread_id = (intptr_t)param;  // 使用 intptr_t 來處理指標與整數的轉換

    while (1) {
        sleep(rand() % 3);  // 隨機休眠

        buffer_item item = rand() % 100 + 1; // 隨機產生資料
        if (insert_item(item)) {
            printf("Producer %ld produced %d\n", thread_id, item);
        } else {
            fprintf(stderr, "Producer %ld failed to produce.\n", thread_id);
        }
    }
}

// Consumer thread 函數
void *consumer(void *param) {
    intptr_t thread_id = (intptr_t)param;  // 使用 intptr_t 來處理指標與整數的轉換

    while (1) {
        sleep(rand() % 3);  // 隨機休眠

        buffer_item item;
        if (remove_item(&item)) {
            printf("Consumer %ld consumed %d\n", thread_id, item);
        } else {
            fprintf(stderr, "Consumer %ld failed to consume.\n", thread_id);
        }
    }
}

// 主程式
int main() {
    int sleep_time, num_producers, num_consumers;

    // 設定隨機數生成器種子
    srand(time(NULL));

    // 從 stdin 獲取參數
    printf("Enter the program duration (in seconds): ");
    scanf("%d", &sleep_time);
    printf("Enter the number of producer threads: ");
    scanf("%d", &num_producers);
    printf("Enter the number of consumer threads: ");
    scanf("%d", &num_consumers);

    // 初始化同步工具
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // 創建 producer 與 consumer threads
    pthread_t producers[num_producers];
    pthread_t consumers[num_consumers];

    for (int i = 0; i < num_producers; i++) {
        pthread_create(&producers[i], NULL, producer, (void *)(intptr_t)i);  // 使用 intptr_t
    }

    for (int i = 0; i < num_consumers; i++) {
        pthread_create(&consumers[i], NULL, consumer, (void *)(intptr_t)i);  // 使用 intptr_t
    }

    // 主程式休眠指定時間後結束
    sleep(sleep_time);

    printf("Main program exiting.\n");
    return 0;
}

