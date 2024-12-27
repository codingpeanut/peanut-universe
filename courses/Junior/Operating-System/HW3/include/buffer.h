#ifndef BUFFER_H
#define BUFFER_H

#include <pthread.h>
#include <semaphore.h>

// 定義 buffer 相關參數
#define BUFFER_SIZE 5
typedef int buffer_item;

// 外部變數
extern buffer_item buffer[BUFFER_SIZE];
extern int insert_index, remove_index;
extern sem_t empty, full;
extern pthread_mutex_t mutex;

// 函數宣告
int insert_item(buffer_item item);
int remove_item(buffer_item *item);

#endif // BUFFER_H

