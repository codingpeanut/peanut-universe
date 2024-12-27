#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>  // 引入 intptr_t
#include <time.h>
#include "buffer.h"

// Producer thread 函數
void *producer(void *param) {
    intptr_t thread_id = (intptr_t)param;  // 使用 intptr_t 來處理指標與整數的轉換

    while (1) {
        sleep(rand() % 3);  // 隨機休眠

        buffer_item item = rand() % 100 + 1; // 隨機產生資料
        if (insert_item(item)) {
            printf("[+] [Producer %ld] Produced: %d\n", thread_id, item);
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
            printf("[-] [Consumer %ld] Consumed: %d\n", thread_id, item);
        } else {
            fprintf(stderr, "Consumer %ld failed to consume.\n", thread_id);
        }
    }
}

// 主程式
int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <sleep_time> <num_producers> <num_consumers>\n", argv[0]);
        return -1;
    }

    // 從命令列參數取得數值
    int sleep_time = atoi(argv[1]);
    int num_producers = atoi(argv[2]);
    int num_consumers = atoi(argv[3]);

    // 確認參數合法性
    if (sleep_time <= 0 || num_producers <= 0 || num_consumers <= 0) {
        fprintf(stderr, "Error: All arguments must be positive integers.\n");
        return -1;
    }

    // 設定隨機數生成器種子
    srand(time(NULL));

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
