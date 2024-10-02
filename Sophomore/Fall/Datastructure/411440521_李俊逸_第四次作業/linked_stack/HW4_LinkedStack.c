/********************************
 *	Author:	411440521 JoshLee	*
 *	Date:	2023/12/16			*
 ********************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Enumeration for flags
typedef enum { FROM_TOP, FROM_BOTTOM } Direction;

typedef enum { RECOVER, NO_RECOVER } RecoveryOption;

// Define ListNode
typedef struct _ListNode *NodePtr;
typedef struct _ListNode {
    int data;
    NodePtr link;
} Node;

// LinkedStack functions
int emptys(NodePtr top) { return top == NULL; }

void pushs(NodePtr *top, int data) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->link = *top;

    *top = new_node;
}

NodePtr pops(NodePtr *top) {
    if (emptys(*top)) {
        printf("Stack is empty!\n");
        exit(EXIT_FAILURE);
    }

    NodePtr temp = *top;
    *top = temp->link;
    return temp;
}

NodePtr create_stack() { return NULL; }

void prints(NodePtr top, int elements_in_one_line) {
    NodePtr current = top;
    int elements_in_current_line = 0;

    while (current != NULL) {
        printf("%d ", current->data);
        current = current->link;

        if (++elements_in_current_line >= elements_in_one_line) {
            printf("\n");
            elements_in_current_line = 0;
        }
    }
    printf(elements_in_current_line ? "\n" : "");
}
// 411440521 JoshLee
// Question
void random_number_generator(NodePtr *top, int range, int offset, int len) {
    srand(time(NULL));
    while (!emptys(*top)) pops(top);
    for (int i = 0; i < len; i++) pushs(top, rand() % range + offset);
}

// Helper function to reverse the stack
void reverse_stack(NodePtr *top) {
    NodePtr s1 = create_stack();
    NodePtr s2 = create_stack();

    // Move elements from the original stack to s1
    while (!emptys(*top)) {
        NodePtr popped = pops(top);
        pushs(&s1, popped->data);
        free(popped);
    }

    // Move elements from s1 to s2
    while (!emptys(s1)) {
        NodePtr popped = pops(&s1);
        pushs(&s2, popped->data);
        free(popped);
    }

    // Move elements from s2 back to the original stack
    while (!emptys(s2)) {
        NodePtr popped = pops(&s2);
        pushs(top, popped->data);
        free(popped);
    }
}

// Helper function to recover elements to the original stack
void recover_elements(NodePtr *top, NodePtr *temp_s) {
    while (!emptys(*temp_s)) {
        NodePtr popped = pops(temp_s);
        pushs(top, popped->data);
        free(popped);
    }
}
// 411440521 JoshLee
// Helper function to get an element from the stack
int getElement(NodePtr *top, Direction direction, int position,
               RecoveryOption recovery) {
    NodePtr temp_s = create_stack();
    int popped_value;

    if (direction == FROM_TOP) {
        for (int i = 0; i < position; i++) {
            NodePtr popped = pops(top);
            pushs(&temp_s, popped->data);
            popped_value = popped->data;
            free(popped);
        }
        if (recovery == RECOVER) recover_elements(top, &temp_s);
    } else {
        reverse_stack(top);  // reverse s to pop the bottom n-th element
        for (int i = 0; i < position; i++) {
            NodePtr popped = pops(top);
            pushs(&temp_s, popped->data);
            popped_value = popped->data;
            free(popped);
        }
        if (recovery == RECOVER) recover_elements(top, &temp_s);
        reverse_stack(
            top);  // reverse s to recover_elements to the original direction
    }

    return popped_value;
}
// 411440521 JoshLee
int main() {
    NodePtr s = create_stack();
    int m;

    // Question 1: assign m the top element without changing the stack
    random_number_generator(&s, 10, 0, 50);
    prints(s, 10);  // 10 numbers per line
    printf("p1: assign m the 3rd element without changing the stack\n");
    m = getElement(&s, FROM_TOP, 3, RECOVER);
    printf("m = %d\n", m);
    prints(s, 10);
    printf("\n");

    // Question 2: assign m the 12th element from the top without changing the
    // stack
    random_number_generator(&s, 10, 0, 50);
    prints(s, 10);
    printf(
        "p2: assign m the 12th element from the top without changing the "
        "stack\n");
    m = getElement(&s, FROM_TOP, 12, RECOVER);
    printf("m = %d\n", m);
    prints(s, 10);
    printf("\n");

    // Question 3: assign m the bottom element without changing the stack
    random_number_generator(&s, 10, 0, 50);
    prints(s, 10);
    printf("p3: assign m the bottom element without changing the stack\n");
    m = getElement(&s, FROM_BOTTOM, 1, RECOVER);
    printf("m = %d\n", m);
    prints(s, 10);
    printf("\n");

    // Question 4: assign m the 2nd element from the bottom without changing
    // the stack
    random_number_generator(&s, 10, 0, 50);
    prints(s, 10);
    printf(
        "p4: assign m the 2nd element from the bottom without changing the "
        "stack\n");
    m = getElement(&s, FROM_BOTTOM, 2, RECOVER);
    printf("m = %d\n", m);
    prints(s, 10);
    printf("\n");

    // Question 5: assign m the 3rd element from the bottom without changing
    // the stack
    random_number_generator(&s, 10, 0, 50);
    prints(s, 10);
    printf(
        "p5: assign m the 3rd element from the bottom without changing the "
        "stack\n");
    m = getElement(&s, FROM_BOTTOM, 3, RECOVER);
    printf("m = %d\n", m);
    prints(s, 10);
    printf("\n");

    // Question 6: assign m the 4th element from the bottom without changing
    // the stack
    random_number_generator(&s, 10, 0, 50);
    prints(s, 10);
    printf(
        "p6: assign m the 4th element from the bottom without changing the "
        "stack\n");
    m = getElement(&s, FROM_BOTTOM, 4, RECOVER);
    printf("m = %d\n", m);
    prints(s, 10);
    printf("\n");
	// 411440521 JoshLee
    return 0;
}