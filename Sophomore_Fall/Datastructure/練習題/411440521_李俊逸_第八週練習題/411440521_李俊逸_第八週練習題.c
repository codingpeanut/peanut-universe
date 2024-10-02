/********************************
 *	Author:	411440521 JoshLee	*
 *	Date:	2023/11/2			*
 ********************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100

typedef struct {
    int data[SIZE];
    int front;
    int rear;
} CircularQueue;

void init_circular_queue(CircularQueue *q){
    q->front = -1;
    q->rear = -1;
}

// Circular Queue functions
int emptyq(CircularQueue *q) {
    return q->front == -1;
}

int fullq(CircularQueue *q) {
    return (q->rear + 1) % SIZE == q->front;
}

void addq(CircularQueue *q, int val) {
    if(fullq(q)) {
        printf("Queue is full!");
        exit(1);
    } else {
        if(emptyq(q))
            q->front = 0;
        q->rear = (q->rear + 1) % SIZE;
        q->data[q->rear] = val;
    }
}

int deleteq(CircularQueue *q) {
    if(emptyq(q)) {
        printf("Queue is empty!");
        exit(1);
    } else {
        int deletedValue = q->data[q->front];
        if(q->front == q->rear) {              // queue is empty
            q->front = -1;                     // set front and rear to -1 to symbolize empty state of CircularQueue
            q->rear = -1;
        } else {
            q->front = ++(q->front) % SIZE;    // use % SIZE to prevent overflow and memory waste
        }
        return deletedValue;
    }
}
// 411440521 JoshLee
void printq(CircularQueue *q) {
    if(emptyq(q)) {
        printf("Queue is empty!");
        exit(2);
    }
    int it;
    for(it = q->front; it != q->rear + 1; it = (++it) % SIZE) {
        printf("%d ", q->data[it]);
    }
}

// Question
int p1(CircularQueue*);
int p2(CircularQueue*);
int p3(CircularQueue*);
int p4(CircularQueue*);
void p5(CircularQueue*);
void restore(CircularQueue*, CircularQueue*);
// 411440521 JoshLee
int main() {
    CircularQueue q;
    init_circular_queue(&q);

    // initialize a random numbers test sequence
    srand(time(NULL));  // use srand(time(NULL)) to set seed of random number generator as current time
    int i, len = 100;
    for(i = 0; i < len; i++)
        addq(&q, rand() % 10);  // generate random number

    printf("k = %d \n", p1(&q));

    printf("k = %d \n", p2(&q));

    printf("k = %d \n", p3(&q));

    printf("k = %d \n", p4(&q));

    p5(&q);

    return 0;
}
// 411440521 JoshLee
// 1. Assign integer k the 2nd element from the front of the queue
int p1(CircularQueue *ele_q) {
    int k;
    CircularQueue temp_q;
    init_circular_queue(&temp_q);

    k = deleteq(ele_q); addq(&temp_q, k);
    k = deleteq(ele_q); addq(&temp_q, k);

    // restore ele_stack
    restore(ele_q, &temp_q);
    return k;
}

// 2. Assign integer k the 9th element from the front of the queue
int p2(CircularQueue *ele_q) {
    int k;
    CircularQueue temp_q;
    init_circular_queue(&temp_q);

    int ele = 1;
    while(ele <= 9) {
        k = deleteq(ele_q); addq(&temp_q, k);
        ele++;
    }

    // restore ele_queue
    restore(ele_q, &temp_q);
    return k;
}
// 411440521 JoshLee
// 3. Assign integer k the back element of the queue
int p3(CircularQueue *ele_q) {
    int k;
    CircularQueue temp_q;
    init_circular_queue(&temp_q);

    k = deleteq(ele_q); addq(&temp_q, k);
    while(!emptyq(ele_q)) {
        k = deleteq(ele_q); addq(&temp_q, k);
    }

    // restore ele_queue
    restore(ele_q, &temp_q);
    return k;
}

// 4. Assign integer k the 2nd element from the back of the queue
int p4(CircularQueue *ele_q) {
    int k, back;
    CircularQueue temp_q;
    init_circular_queue(&temp_q);

	back = deleteq(ele_q); addq(&temp_q, back);
    if(emptyq(ele_q)) {
        printf("1-element stack");
        exit(4);
    }
    while(!emptyq(ele_q)) {
        k = back;
        back = deleteq(ele_q); addq(&temp_q, back);
    }
    // restore ele_queue
    restore(ele_q, &temp_q);
    return k;
}

// 5. Print out each element of the queue (from the top to the bottom)
void p5(CircularQueue *ele_q) {
    while(!emptyq(ele_q)) {
        printf("%d", deleteq(ele_q));
    }
}
// 411440521 JoshLee
void restore(CircularQueue *ele_q, CircularQueue *deleted_ele_q) {
    CircularQueue temp_q;
    init_circular_queue(&temp_q);

    while(!emptyq(ele_q)) {  // temp_q = ele_q
        addq(&temp_q, deleteq(ele_q));
    }
    while(!emptyq(deleted_ele_q)) {  // ele_q = deleted_q
        addq(ele_q, deleteq(deleted_ele_q));
    }
    while(!emptyq(&temp_q)) {  // ele_q = deleted_q + temp_q
        addq(ele_q, deleteq(&temp_q));
    }
}