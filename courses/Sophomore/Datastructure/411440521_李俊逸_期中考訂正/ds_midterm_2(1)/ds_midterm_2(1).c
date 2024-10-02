/********************************
 *	Author:	411440521 JoshLee	*
 *	Date:	2023/11/30			*
 ********************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>   // use time() to get current time

#define SIZE 100


typedef struct {
    int data[SIZE];
    int top;
} Stack;

void init_stack(Stack *s) {
    s->top = -1;
}


// Stack functions
int full(Stack *s) {
    return s->top == SIZE - 1;
}

int empty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, int val) {
    if(!full(s))
        s->data[++(s->top)] = val;
    else {
        printf("Stack is full!");
        exit(1);
    }
}

int pop(Stack *s) {
    if(!empty(s))
        return s->data[(s->top)--];
    printf("Stack is empty!");
    exit(2);
}

// 411440521 JoshLee
// Questions
void random_number_generator(Stack* s, int range, int offset, int len) {
    srand(time(NULL));                     // use srand(time(NULL)) to set seed of random number generator as current time
    int i;
    for(i = 0; i < len; i++)
        push(s, rand() % range + offset);  // generate random number
}

void recover_elements(Stack *element_s, Stack *temp_s) {
    while(!empty(temp_s)) {
        push(element_s, pop(temp_s));
    }
}

void print_stack(Stack* element_s, int ElementsInOneLine) {
    Stack temp_s;
    init_stack(&temp_s);
    int ElementsInCurrentLine = 0;
    
    while(!empty(element_s)) {
        int popped_value = pop(element_s);
        printf("%d ", popped_value);
        push(&temp_s, popped_value);
        if(++ElementsInCurrentLine >= ElementsInOneLine) {
            printf("\n");
            ElementsInCurrentLine = 0;
        }
    }
    
    recover_elements(element_s, &temp_s);
    printf(ElementsInCurrentLine ? "\n\n" : "\n");
}
// 411440521 JoshLee
void reverse_stack(Stack *element_s) {
    Stack s1;
    Stack s2;
    init_stack(&s1);
    init_stack(&s2);
    while(!empty(element_s)) {
        push(&s1, pop(element_s));
    }
    while(!empty(&s1)) {
        push(&s2, pop(&s1));
    }
    while(!empty(&s2)) {
        push(element_s, pop(&s2));
    }
}
// 411440521 JoshLee
int getElement(Stack *s, int fromTop, int n, int recover) {    // 1 is fromTop, 0 is fromBottom    1 does recover, 0 doesn't recover
    Stack temp_s;
    init_stack(&temp_s);
    int i, popped_value;
    
    if(fromTop) {
        for(i = 0; i < n; i++) {
            popped_value = pop(s);
            push(&temp_s, popped_value);
        }
        if(recover) recover_elements(s, &temp_s);
    } else {
        reverse_stack(s);                                      // reverse s to pop the bottom n-th element
        for(i = 0; i < n; i++) {
            popped_value = pop(s);
            push(&temp_s, popped_value);
        }
        if(recover) recover_elements(s, &temp_s);              // recover_elements s
        reverse_stack(s);                                      // reverse s to recover_elements to origional directon
    }
    return popped_value;
}


int main() {
    Stack s;
    init_stack(&s);

    // p1
    random_number_generator(&s, 100, 1, 18);  // Use rand()%100+1 to get 18 random numbers
    print_stack(&s, 9);                       // 9 numbers in one line

    // p2 Assign and output integer i the bottom element from the top of S, leaving S unchanged
    int i = getElement(&s, 0, 1, 1);          // get the 1st element from bottom with recover
    printf("i = %d \n\n", i);

    // p3 Assign and output integer j the 2nd element from the bottom of S,leaving S unchanged
    int j = getElement(&s, 0, 2, 1);
    printf("j = %d \n\n", j);

    // p4 Assign and output integer k the 3rd element from the bottom of S,leaving S unchanged.
    int k = getElement(&s, 0, 3, 1);
    printf("k = %d \n\n", k);

    // p5 Output the numbers from the top to the bottom of S (one by one,one space in between, and 9 numbers in one line), leaving S unchanged
    print_stack(&s, 9);                       // 9 numbers in one line

    // p6 Assign and output integer m the 4th element from the bottom of S
    int m = getElement(&s, 0, 4, 0);          // get the 4th element from bottom without recover
    printf("m = %d \n", m);
    
    return 0;
}