/********************************
 *	Author:	411440521 JoshLee	*
 *	Date:	2023/12/08			*
 ********************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>  // use time() to get current time

#define SIZE 100

// Enumeration for flags
typedef enum {
    FROM_TOP,
    FROM_BOTTOM
} Direction;

typedef enum {
    RECOVER,
    NO_RECOVER
} RecoveryOption;

typedef struct {
    int data[SIZE];
    int top;
} Stack;

void init_stack(Stack *s) {
    s->top = -1;
}

// Stack functions
int fulls(Stack *s) {
    return s->top == SIZE - 1;
}

int emptys(Stack *s) {
    return s->top == -1;
}

void pushs(Stack *s, int val) {
    if(!fulls(s))
        s->data[++(s->top)] = val;
    else {
        printf("Stack is fulls!");
        exit(1);
    }
}

int pops(Stack *s) {
    if(!emptys(s))
        return s->data[(s->top)--];
    printf("Stack is empty!");
    exit(2);
}
// 411440521 JoshLee
// Questions
void random_number_generator(Stack *s, int range, int offset, int len) {
    srand(time(NULL));          // use srand(time(NULL)) to set seed of random number generator as current time
    int i;
    while(!emptys(s))
        pops(s);
    for(i = 0; i < len; i++)
        pushs(s, rand() % range + offset);  // generate random number
}

void recover_elements(Stack *s, Stack *temp_s) {
    while (!emptys(temp_s)) {
        pushs(s, pops(temp_s));
    }
}

void prints(Stack *ele_s, int ElementsInOneLine) {
    Stack temp_popped;
    init_stack(&temp_popped);
    int ElementsInCurrentLine = 0;
    
    while(!emptys(ele_s)) {
        int popped_value = pops(ele_s);
        printf("%d ", popped_value);
        pushs(&temp_popped, popped_value);
        if(++ElementsInCurrentLine >= ElementsInOneLine) {
            printf("\n");
            ElementsInCurrentLine = 0;
        }
    }
    recover_elements(ele_s, &temp_popped);
    printf(ElementsInCurrentLine ? "\n" : "");
}

void reverse_stack(Stack *s) {
    Stack s1;
    Stack s2;
    init_stack(&s1);
    init_stack(&s2);
    while(!emptys(s)) {
        pushs(&s1, pops(s));
    }
    while(!emptys(&s1)) {
        pushs(&s2, pops(&s1));
    }
    while(!emptys(&s2)) {
        pushs(s, pops(&s2));
    }
}
// 411440521 JoshLee
int getElement(Stack *s, Direction direction, int position, RecoveryOption recovery) {
    Stack temp_s;
    init_stack(&temp_s);
    int i, popped_value;

    if (direction == FROM_TOP) {
        for (i = 0; i < position; i++) {
            popped_value = pops(s);
            pushs(&temp_s, popped_value);
        }
        if (recovery == RECOVER)
            recover_elements(s, &temp_s);
    } else {
        reverse_stack(s);
        for (i = 0; i < position; i++) {
            popped_value = pops(s);
            pushs(&temp_s, popped_value);
        }
        if (recovery == RECOVER)
            recover_elements(s, &temp_s);
        reverse_stack(s);
    }
    return popped_value;
}
// 411440521 JoshLee
int main() {
    Stack s;
    init_stack(&s);
	
	// p1: assign m the 3rd element from the top
    random_number_generator(&s, 10, 0, 30);  // Use rand() % 10 + 0 to get 30 random numbers
    prints(&s, 10);                          // 10 numbers per line
	printf("p1: assign m the 3rd element from the top \n");
	int m = getElement(&s, FROM_TOP, 3, NO_RECOVER);
	printf("m = %d \n", m);
    prints(&s, 10);
    printf("\n");
    
    // p2: assign m the 3rd element from the top without changing the stack
    random_number_generator(&s, 10, 0, 30);
    prints(&s, 10);
	printf("p2: assign m the 3rd element from the top without changing the stack \n");
	m = getElement(&s, FROM_TOP, 3, RECOVER);
	printf("m = %d \n", m);
    prints(&s, 10);
    printf("\n");
    
    // p3: assign m the 10th element from the top
    random_number_generator(&s, 10, 0, 30);
    prints(&s, 10);
	printf("p3: assign m the 10th element from the top \n");
	m = getElement(&s, FROM_TOP, 10, NO_RECOVER);
	printf("m = %d \n", m);
    prints(&s, 10);
    printf("\n");
    
    // p4: assign m the 10th element from the top without changing the stack
    random_number_generator(&s, 10, 0, 30);
    prints(&s, 10);
	printf("p4: assign m the 10th element from the top without changing the stack \n");
	m = getElement(&s, FROM_TOP, 10, RECOVER);
	printf("m = %d \n", m);
    prints(&s, 10);
    printf("\n");
    // 411440521 JoshLee
    // p5: assign m the bottom element
    random_number_generator(&s, 10, 0, 30);
    prints(&s, 10);
    printf("p5: assign m the bottom element \n");
	m = getElement(&s, FROM_BOTTOM, 1, NO_RECOVER);
	printf("m = %d \n", m);
    prints(&s, 10);
    printf("\n");
    
    // p6: assign m the bottom element without changing the stack
    random_number_generator(&s, 10, 0, 30);
    prints(&s, 10);
	printf("p6: assign m the bottom element without changing the stack \n");
	m = getElement(&s, FROM_BOTTOM, 1, RECOVER);
	printf("m = %d \n", m);
    prints(&s, 10);
    printf("\n");
    
    // p7: assign m the 2nd element from the bottom
    random_number_generator(&s, 10, 0, 30);
    prints(&s, 10);
	printf("p7: assign m the 2nd element from the bottom \n");
	m = getElement(&s, FROM_BOTTOM, 2, NO_RECOVER);
	printf("m = %d \n", m);
    prints(&s, 10);
    printf("\n");
    
    // p8: assign m the 2nd element from the bottom without changing the stack
    random_number_generator(&s, 10, 0, 30);
    prints(&s, 10);
	printf("p8: assign m the 2nd element from the bottom without changing the stack \n");
	m = getElement(&s, FROM_BOTTOM, 2, RECOVER);
	printf("m = %d \n", m);
    prints(&s, 10);
    printf("\n");
    
    // p9: assign m the 3rd element from the bottom
    random_number_generator(&s, 10, 0, 30);
    prints(&s, 10);
	printf("p9: assign m the 3rd element from the bottom \n");
	m = getElement(&s, FROM_BOTTOM, 3, NO_RECOVER);
	printf("m = %d \n", m);
    prints(&s, 10);
    printf("\n");
    
    // p10: assign m the 3rd element from the bottom without changing the stack
    random_number_generator(&s, 10, 0, 30);
    prints(&s, 10);
	printf("p10: assign m the 3rd element from the bottom without changing the stack \n");
	m = getElement(&s, FROM_BOTTOM, 3, RECOVER);
	printf("m = %d \n", m);
    prints(&s, 10);
    printf("\n");
    
    // p11: assign m the 4th element from the bottom
    random_number_generator(&s, 10, 0, 30);
    prints(&s, 10);
	printf("p11: assign m the 4th element from the bottom \n");
	m = getElement(&s, FROM_BOTTOM, 4, NO_RECOVER);
	printf("m = %d \n", m);
    prints(&s, 10);
    printf("\n");
    
    // p12: assign m the 4th element from the bottom without changing the stack
    random_number_generator(&s, 10, 0, 30);
    prints(&s, 10);
	printf("p12: assign m the 4th element from the bottom without changing the stack \n");
	m = getElement(&s, FROM_BOTTOM, 4, RECOVER);
	printf("m = %d \n", m);
    prints(&s, 10);
    printf("\n");
    // 411440521 JoshLee
	return 0;
}