/********************************
 *	Author:	411440521 JoshLee	*
 *	Date:	2023/12/08			*
 ********************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 100

// Enumeration for flags
typedef enum {
    FROM_FRONT,
    FROM_BACK
} Direction;

typedef enum {
    RECOVER,
    NO_RECOVER
} RecoveryOption;

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
// Questions
void random_number_generator(CircularQueue* q, int range, int offset, int len) {
    srand(time(NULL));          // use srand(time(NULL)) to set seed of random number generator as current time
    int i;
    while(!emptyq(q))
        deleteq(q);
    for(i = 0; i < len; i++)
        addq(q, rand() % range + offset);  // generate random number
}

void recover_elements(CircularQueue *ele_q, CircularQueue *deleted_ele_q) {
    while(!emptyq(ele_q)) {           // deleted_ele_q = deleted_ele_q + ele_q
        addq(deleted_ele_q, deleteq(ele_q));
    }
    while(!emptyq(deleted_ele_q)) {         // ele_q = deleted_ele_q
        addq(ele_q, deleteq(deleted_ele_q));
    }
}

void printq(CircularQueue* ele_q, int ElementsInOneLine) {
    CircularQueue temp_q;
    init_circular_queue(&temp_q);
    int ElementsInCurrentLine = 0;

    while(!emptyq(ele_q)) {
        int deleted_value = deleteq(ele_q); addq(&temp_q, deleted_value);
        printf("%d ", deleted_value);
        if(++ElementsInCurrentLine >= ElementsInOneLine) {
            printf("\n");
            ElementsInCurrentLine = 0;
        }
    }
    recover_elements(ele_q, &temp_q);
    printf(ElementsInCurrentLine ? "\n" : "");
}

void reverse_queue(CircularQueue *q) {
    // base case
    if (emptyq(q))
        return;
    // store front(first element) of queue, and remove front
    int fr = deleteq(q);
 
    // asking recursion to reverse the leftover queue
    reverse_queue(q);
 
    // placing first element at its correct position
    addq(q, fr);
}
// 411440521 JoshLee
int getElement(CircularQueue *q, Direction direction, int position, RecoveryOption recovery) {  // No Recover
    CircularQueue temp_q;
    init_circular_queue(&temp_q);
    int i, deleted_value;

    if(direction == FROM_FRONT) {
        for(i = 0; i < position; i++) {
            deleted_value = deleteq(q);
            addq(&temp_q, deleted_value);
        }
        if(recovery == RECOVER) recover_elements(q, &temp_q);
    } else {
        reverse_queue(q);
        for(i = 0; i < position; i++) {
            deleted_value = deleteq(q);
            addq(&temp_q, deleted_value);
        }
        if(recovery == RECOVER) recover_elements(q, &temp_q);
        reverse_queue(q);
    }
    return deleted_value;
}

// 411440521 JoshLee
int main() {
    CircularQueue q;
    init_circular_queue(&q);
    
    // p1: assign k the 3rd from the back
    random_number_generator(&q, 10, 0, 30);         // Use rand() % 10 + 0 to get 30 random numbers
    printq(&q, 10);                                 // 10 numbers in one line
    printf("p1: assign k the 3rd from the back\n");
    int k = getElement(&q, FROM_BACK, 3, NO_RECOVER);
    printf("k = %d \n", k);
    printq(&q, 10);
    printf("\n");
    
    // p2: assign k the 3rd from the back without changing the queue
    random_number_generator(&q, 10, 0, 30);
    printq(&q, 10);
    printf("p2: assign k the 3rd from the back without changing the queue\n");
    k = getElement(&q, FROM_BACK, 3, RECOVER);
    printf("k = %d \n", k);
    printq(&q, 10);
    printf("\n");
    
    // p3: assign k the 4th element from back
    random_number_generator(&q, 10, 0, 30);
    printq(&q, 10);
    printf("p3: assign k the 4th element from back\n");
    k = getElement(&q, FROM_BACK, 4, NO_RECOVER);
    printf("k = %d \n", k);
    printq(&q, 10);
    printf("\n");
    
    // p4: assign k the 4th element from back without changing the queue
    random_number_generator(&q, 10, 0, 30);
    printq(&q, 10);
    printf("p4: assign k the 4th element from back without changing the queue\n");
    k = getElement(&q, FROM_BACK, 4, RECOVER);
    printf("k = %d \n", k);
    printq(&q, 10);
    printf("\n");
	// 411440521 JoshLee
    return 0;
}