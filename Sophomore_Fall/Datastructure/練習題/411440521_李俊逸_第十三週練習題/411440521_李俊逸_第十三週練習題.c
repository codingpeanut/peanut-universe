/********************************
 *	Author:	411440521 JoshLee	*
 *	Date:	2023/12/2			*
 ********************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Enumeration for flags
typedef enum {
    FROM_TOP,
    FROM_BOTTOM
} Direction;

typedef enum {
    RECOVER,
    NO_RECOVER
} RecoveryOption;

// Define ListNode
typedef struct _ListNode *NodePtr;
typedef struct _ListNode {
    int data;
    NodePtr link;
} Node;

// Define LinkedStack
typedef struct _LinkedStack {
    NodePtr top;
} LinkedStack;

// LinkedStack functions
int emptys(LinkedStack *s) {
    return s->top == NULL;
}

void pushs(LinkedStack *s, int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = data;
    new_node->link = s->top;

    s->top = new_node;
}

NodePtr pops(LinkedStack *s) {
    if (emptys(s)) {
        printf("Stack is emptys!\n");
        exit(1);
    }

    NodePtr top = s->top;
    s->top = top->link;

    return top;
}

LinkedStack create_stack() {
    LinkedStack ls;
    ls.top = NULL;
    return ls;
}

void prints(LinkedStack *s, int ElementsInOneLine) {
    NodePtr current = s->top;
    int ElementsInCurrentLine = 0;

    while (current != NULL) {
        printf("%d ", current->data);
        current = current->link;

        if (++ElementsInCurrentLine >= ElementsInOneLine) {
            printf("\n");
            ElementsInCurrentLine = 0;
        }
    }
    printf(ElementsInCurrentLine ? "\n" : "");
}
// 411440521 JoshLee
// LinkedQueue functions (Using LinkedStack Functions)
LinkedStack create_queue() {
    return create_stack();
}

int emptyq(LinkedStack *s) {
    return emptys(s);
}

void addq(LinkedStack *s, int data) {
    LinkedStack tempStack = create_stack();

    // Reverse the order of elements in the stack
    while (!emptys(s)) {
        NodePtr popped = pops(s);
        pushs(&tempStack, popped->data);
        free(popped);
    }

    // Add the new element at the top
    pushs(s, data);

    // Restore the original order of elements
    while (!emptys(&tempStack)) {
        NodePtr popped = pops(&tempStack);
        pushs(s, popped->data);
        free(popped);
    }
}

NodePtr deleteq(LinkedStack *s) {
    if (emptys(s)) {
        printf("Queue is empty!\n");
        exit(1);
    }

    return pops(s);
}

void printq(LinkedStack *s, int ElementsInOneLine) {
    prints(s, ElementsInOneLine);
}
// 411440521 JoshLee
// Question
void random_number_generator(LinkedStack *s, int range, int offset, int len) {
    srand(time(NULL)); // use srand(time(NULL)) to set seed of random number generator as current time
    int i;
    while (!emptys(s))
        pops(s);
    for (i = 0; i < len; i++)
        pushs(s, rand() % range + offset); // generate random number
}

// Helper function to reverse the stack
void reverse_stack(LinkedStack *s) {
    LinkedStack q = create_queue();

    // Enqueue all elements from the stack into the queue
    while (!emptys(s)) {
        NodePtr popped = pops(s);
        addq(&q, popped->data);
        free(popped);
    }

    // Dequeue all elements from the queue and push them back into the stack
    while (!emptyq(&q)) {
        NodePtr deleted = deleteq(&q);
        pushs(s, deleted->data);
        free(deleted);
    }
}

// Helper function to recover elements to the original stack
void recover_elements(LinkedStack *s, LinkedStack *temp_s) {
    while (!emptys(temp_s)) {
        NodePtr popped = pops(temp_s);
        pushs(s, popped->data);
        free(popped);
    }
}

// Helper function to get an element from the stack
int getElement(LinkedStack *s, Direction direction, int position, RecoveryOption recovery) {
    LinkedStack temp_s = create_stack();
    int i, popped_value;

    if (direction == FROM_TOP) {
        for (i = 0; i < position; i++) {
            NodePtr popped = pops(s);
            pushs(&temp_s, popped->data);
            popped_value = popped->data;
        }
        if (recovery == RECOVER) recover_elements(s, &temp_s);
    } else {
        reverse_stack(s); // reverse s to pop the bottom n-th element
        for (i = 0; i < position; i++) {
            NodePtr popped = pops(s);
            pushs(&temp_s, popped->data);
            popped_value = popped->data;
        }
        if (recovery == RECOVER) recover_elements(s, &temp_s);
        reverse_stack(s); // reverse s to recover_elements to the original direction
    }

    return popped_value;
}
// 411440521 JoshLee
int main() {
    LinkedStack s = create_stack();
    int i, m;

    // Question 1: assign m the top element without changing the stack
    random_number_generator(&s, 10, 0, 30); // Use rand() % 10 + 0 to get 30 random numbers
    prints(&s, 10);                         // 10 numbers per line
    printf("p1: assign m the top element without changing the stack\n");
    m = getElement(&s, FROM_TOP, 1, RECOVER);
    printf("m = %d\n", m);
    prints(&s, 10);
    printf("\n");

    // Question 2: assign m the third element from the top without changing the stack
    random_number_generator(&s, 10, 0, 30);
    prints(&s, 10);
    printf("p2: assign m the third element from the top without changing the stack\n");
    m = getElement(&s, FROM_TOP, 3, RECOVER);
    printf("m = %d\n", m);
    prints(&s, 10);
    printf("\n");

    // Question 3: assign m the bottom element without changing the stack
    random_number_generator(&s, 10, 0, 30);
    prints(&s, 10);
    printf("p3: assign m the bottom element without changing the stack\n");
    m = getElement(&s, FROM_BOTTOM, 1, RECOVER);
    printf("m = %d\n", m);
    prints(&s, 10);
    printf("\n");

    // Question 4: assign m the tenth element from the bottom without changing the stack
    random_number_generator(&s, 10, 0, 30);
    prints(&s, 10);
    printf("p4: assign m the tenth element from the bottom without changing the stack\n");
    m = getElement(&s, FROM_BOTTOM, 10, RECOVER);
    printf("m = %d\n", m);
    prints(&s, 10);
    printf("\n");
	// 411440521 JoshLee
    return 0;
}