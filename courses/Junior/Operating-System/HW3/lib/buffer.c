#include "buffer.h"

// 初始化全域變數
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
