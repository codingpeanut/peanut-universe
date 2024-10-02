/********************************
 *	Author:	411440521 JoshLee	*
 *	Date:	2023/11/30			*
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
// Questions
void random_number_generator(CircularQueue* q, int range, int offset, int len) {
    srand(time(NULL));          // use srand(time(NULL)) to set seed of random number generator as current time
    int i;
    for(i = 0; i < len; i++)
        addq(q, rand() % range + offset);  // generate random number
}

void recover_elements(CircularQueue *element_q, CircularQueue *deleted_element_q) {
    while(!emptyq(element_q)) {                  // deleted_element_q = deleted_element_q + element_q
        addq(deleted_element_q, deleteq(element_q));
    }
    while(!emptyq(deleted_element_q)) {          // element_q = deleted_element_q
        addq(element_q, deleteq(deleted_element_q));
    }
}

void print_queue(CircularQueue* element_q, int ElementsInOneLine) {
    CircularQueue temp_q;
    init_circular_queue(&temp_q);
    int ElementsInCurrentLine = 0;

    while(!emptyq(element_q)) {
        int deleted_value = deleteq(element_q);
        printf("%d ", deleted_value);
        addq(&temp_q, deleted_value);
        if(++ElementsInCurrentLine >= ElementsInOneLine) {
            printf("\n");
            ElementsInCurrentLine = 0;
        }
    }
    
    recover_elements(element_q, &temp_q);
    printf(ElementsInCurrentLine ? "\n\n" : "\n");
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
int getElement(CircularQueue *q, int fromFront, int n, int recover) {    // 1 is fromFront, 0 is fromBack    1 does recover, 0 doesn't recover
    CircularQueue temp_q;
    init_circular_queue(&temp_q);
    int i, deleted_value;
    
    if(fromFront) {
        for(i = 0; i < n; i++) {
            deleted_value = deleteq(q);
            addq(&temp_q, deleted_value);
        }
        if(recover) recover_elements(q, &temp_q);
    } else {
        reverse_queue(q);
        for(i = 0; i < n; i++) {
            deleted_value = deleteq(q);
            addq(&temp_q, deleted_value);
        }
        if(recover) recover_elements(q, &temp_q);
        reverse_queue(q);
    }
    return deleted_value;
}

// 411440521 JoshLee
int main() {
    CircularQueue q;
    init_circular_queue(&q);

    // p1 Use rand()%100+1 to get 18 random numbers, output thenumbers (one by one, one space in between, and 9 numbers in one line) 
    //    and add the numbers into a created queue(struct queue Q) one by one
    random_number_generator(&q, 100, 1, 18);  // Use rand()%100+1 to get 18 random numbers
    print_queue(&q, 9);                       // 9 numbers in one line

    // p2 Assign and output integer x the 12th element from the head of Q
    int x = getElement(&q, 1, 12, 0);
    printf("x = %d \n\n", x);

    // p3 Output the numbers from the head to the tail of Q (one byone, one space in between, and 9 numbers in one line),
    //    leaving Q unchanged
    print_queue(&q, 9);                       // 9 numbers in one line

    // p4 Assign and output integer y the 8th element from the head of Q
    int y = getElement(&q, 1, 8, 0);
    printf("y = %d \n\n", y);

    return 0;
}