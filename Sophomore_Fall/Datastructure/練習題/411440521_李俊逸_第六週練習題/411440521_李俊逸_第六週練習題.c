/********************************
 *	Author:	411440521 JoshLee	*
 *	Date:	2023/10/19			*
 ********************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int stack[SIZE];
int top = -1;

// Stack functions
int full() {
    return top == SIZE - 1;
}

int empty() {
    return top == -1;
}

void push(int val) {
    if(!full())
        stack[++top] = val;
    else {
        printf("Stack is full!");
        exit(1);
    }
}

int pop() {
    if(!empty())
        return stack[top--];
    printf("Stack is empty!");
    exit(2);
}

// Question
int p1();
int p2();
int p3();
int p4();
void p5();
void reset();
// 411440521 JoshLee
int main() {

    // initialize a random numbers sequence
    srand(time(NULL));
    int i, data[SIZE];
    for(i = 0; i < SIZE; i++)
        data[i] = rand() % 10;

    reset(data, SIZE);
    printf("k = %d \n", p1());

    reset(data, SIZE);
    printf("k = %d \n", p2());

    reset(data, SIZE);
    printf("k = %d \n", p3());

    reset(data, SIZE);
    printf("k = %d \n", p4());

    reset(data, SIZE);
    p5();

    return 0;
}
// 411440521 JoshLee
// 1. Assign integer k the 2nd element from the top of the stack
int p1() {
    int k;
    if(empty()) {
        printf("1-element stack");
        exit(1);
    }
    k = pop();
    k = pop();
    return k;
}

// 2. Assign integer k the 9th element from the top of the stack
int p2() {
    int k;
    int ele = 1;
    while(ele <= 9) {
        if(empty()) {
            printf("%d-element stack", ele);
            exit(2);
        }
        k = pop();
        ele++;
    }
    return k;
}

// 3. Assign integer k the bottom element of the stack
int p3() {
    int k;
    while(!empty()) {
        k = pop();
    }
    return k;
}

// 4. Assign integer k the 2nd element from the bottom of the stack
int p4() {
    int k;
    int bottom = pop();
    if(empty()) {
        printf("1-element stack");
        exit(4);
    }
    while(!empty()) {
        k = bottom;
        bottom = pop();
    }
    return k;
}

// 5. Print out each element of the stack (from the top to the bottom)
void p5() {
    while(!empty()) {
        printf("%d", pop());
    }
}
// 411440521 JoshLee
void reset(int *test_data, int data_len) {
    int i = 0;
    while(!empty()) {
        pop();
    }
    while(!full() && i < data_len) {
        int num = test_data[i++];
        push(num);
    }
}