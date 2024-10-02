/********************************
 *	Author:	411440521 JoshLee	*
 *	Date:	2023/12/08			*
 ********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // memcpy()
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
} LinearQueue;

void init_linear_queue(LinearQueue *q){
    q->front = -1;
    q->rear = -1;
}


// Linear Queue functions
int emptyq(LinearQueue *q) {
    return (q->front == -1) || (q->front > q->rear);
}

int fullq(LinearQueue *q) {
    return q->rear == SIZE - 1;
}

void addq(LinearQueue *q, int val) {
    if(fullq(q)) {
        printf("Queue is full!");
        exit(1);
    }
    if(emptyq(q))
        q->front = 0;
    q->data[++q->rear] = val;
}

int deleteq(LinearQueue *q) {
    int deleted_value;
    if(emptyq(q)) {
        printf("Queue is empty!");
        exit(1);
    } else {
        deleted_value = q->data[q->front++];
        
        // adjust data to the front
        if (q->front > 0) {
            int new_size = q->rear - q->front + 1;
            memcpy(q->data, &q->data[q->front], new_size * sizeof(int));
            q->front = 0;
            q->rear = new_size - 1;
        }

        return deleted_value;
    }
}

// 411440521 JoshLee
// Questions
void random_number_generator(LinearQueue* q, int range, int offset, int len) {
    srand(time(NULL));                      // use srand(time(NULL)) to set seed of random number generator as current time
    int i;
    while(!emptyq(q))
        deleteq(q);
    for(i = 0; i < len; i++)
        addq(q, rand() % range + offset);   // generate random number
}

void recover_elements(LinearQueue *ele_q, LinearQueue *deleted_ele_q) {
    while(!emptyq(ele_q)) {                 // deleted_ele_q = deleted_ele_q + ele_q
        addq(deleted_ele_q, deleteq(ele_q));
    }
    while(!emptyq(deleted_ele_q)) {         // ele_q = deleted_ele_q
        addq(ele_q, deleteq(deleted_ele_q));
    }
}

void printq(LinearQueue* ele_q, int ElementsInOneLine) {
    LinearQueue temp_q;
    init_linear_queue(&temp_q);
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

void reverse_queue(LinearQueue* q) {
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
int getElement(LinearQueue *q, Direction direction, int position, RecoveryOption recovery) {  // No Recover
    LinearQueue temp_q;
    init_linear_queue(&temp_q);
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
    LinearQueue q;
    init_linear_queue(&q);
    
    // p1: assign n the 3rd element from front
    random_number_generator(&q, 10, 0, 30);         // Use rand() % 10 + 0 to get 30 random numbers
    printq(&q, 10);                                 // 10 numbers in one line
    printf("p1: assign n the 3rd element from front\n");
    int n = getElement(&q, FROM_FRONT, 3, NO_RECOVER);
    printf("n = %d \n", n);
    printq(&q, 10);
    printf("\n");
    
    // p2: assign n the 10th element from front
    random_number_generator(&q, 10, 0, 30);
    printq(&q, 10);
    printf("p2: assign n the 10th element from front\n");
    n = getElement(&q, FROM_FRONT, 10, NO_RECOVER);
    printf("n = %d \n", n);
    printq(&q, 10);
    printf("\n");
    
    // p3: assign n the last element
    random_number_generator(&q, 10, 0, 30);
    printq(&q, 10);
    printf("p3: assign n the last element\n");
    n = getElement(&q, FROM_BACK, 1, NO_RECOVER);
    printf("n = %d \n", n);
    printq(&q, 10);
    printf("\n");
    
    // p4: assign n the 2nd element from back
    random_number_generator(&q, 10, 0, 30);
    printq(&q, 10);
    printf("p4: assign n the 2nd element from back\n");
    n = getElement(&q, FROM_BACK, 2, NO_RECOVER);
    printf("n = %d \n", n);
    printq(&q, 10);
    printf("\n");
    // 411440521 JoshLee
    return 0;
}