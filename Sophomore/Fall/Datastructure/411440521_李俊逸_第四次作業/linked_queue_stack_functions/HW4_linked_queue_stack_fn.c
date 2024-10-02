#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Enumeration for flags
typedef enum { FROM_FRONT, FROM_BACK } Direction;

typedef enum { RECOVER, NO_RECOVER } RecoveryOption;

// Define Node
typedef struct _Node *NodePtr;
typedef struct _Node {
    int data;
    NodePtr link;
} Node;

// LinkedStack functions
NodePtr create_stack() { return NULL; }

int emptys(NodePtr *top) { return *top == NULL; }

void pushs(NodePtr *top, int data) {
    NodePtr new_node = (NodePtr)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->link = *top;

    *top = new_node;
}

NodePtr pops(NodePtr *top) {
    if (emptys(top)) {
        printf("Stack is empty!\n");
        exit(1);
    }

    NodePtr popped = *top;
    *top = popped->link;
    return popped;
}

void prints(NodePtr *top, int elements_in_one_line) {
    NodePtr current = *top;
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

void free_stack(NodePtr *s) {
    while (!emptys(s)) {
        NodePtr popped = pops(s);
        free(popped);
    }
}

// LinkedQueue functions (Using LinkedStack Functions)

NodePtr create_queue() { return create_stack(); }

int emptyq(NodePtr *front) { return emptys(front); }

void addq(NodePtr *front, int data) {
    NodePtr temp_s = create_stack();

    // Reverse the order of elements in the stack
    while (!emptys(front)) {
        NodePtr popped = pops(front);
        pushs(&temp_s, popped->data);
        free(popped);
    }

    // Add the new element at the top
    pushs(front, data);

    // Restore the original order of elements
    while (!emptys(&temp_s)) {
        NodePtr popped = pops(&temp_s);
        pushs(front, popped->data);
        free(popped);
    }
}

NodePtr deleteq(NodePtr *front) {
    if (emptys(front)) {
        printf("Queue is empty!\n");
        exit(1);
    }

    return pops(front);
}

void printq(NodePtr *front, int elements_in_one_line) {
    prints(front, elements_in_one_line);
}

void free_queue(NodePtr *front) { free_stack(front); }

// Question

void random_number_generator(NodePtr *front, int range, int offset, int len) {
    srand(time(NULL));
    while (!emptyq(front)) deleteq(front);
    for (int i = 0; i < len; i++) addq(front, rand() % range + offset);
}

// Helper function to reverse the queue
void reverse_queue(NodePtr *q) {
    if (emptyq(q)) {
        return;
    }

    int fr = deleteq(q)->data;

    reverse_queue(q);

    addq(q, fr);
}

// Helper function to recover elements to the original stack
void recover_elements(NodePtr *q, NodePtr *temp_q) {
    while (!emptyq(temp_q)) {
        NodePtr deleted = deleteq(temp_q);
        addq(q, deleted->data);
        free(deleted);
    }
}

// Helper function to get an element from the stack
int getElement(NodePtr *front, Direction direction, int position,
               RecoveryOption recovery) {
    NodePtr temp_q = create_queue();
    int i, deleted_value;

    if (direction == FROM_FRONT) {
        for (i = 0; i < position; i++) {
            NodePtr deleted = deleteq(front);
            addq(&temp_q, deleted->data);
            deleted_value = deleted->data;
            free(deleted);
        }
        reverse_queue(front);
        reverse_queue(&temp_q);
        if (recovery == RECOVER) recover_elements(front, &temp_q);
        reverse_queue(front);
    } else {
        reverse_queue(front);  // reverse q to delete the back n-th element
        for (i = 0; i < position; i++) {
            NodePtr deleted = deleteq(front);
            addq(&temp_q, deleted->data);
            deleted_value = deleted->data;
            free(deleted);
        }
        reverse_queue(
            front);  // reverse q to recover_elements to the original direction
        reverse_queue(&temp_q);
        if (recovery == RECOVER) recover_elements(front, &temp_q);
    }

    free_queue(&temp_q);
    return deleted_value;
}

int main() {
    NodePtr q = create_queue();

    // 1.
    // Use rand()%100+1 to get 40 random numbers,
    // output the numbers (one by one, one space in between,
    // and 10 numbers in one line) and push the numbers into a created queue Q
    // one by one.
    printf("a: use rand()%%100+1 to get 40 random numbers\n");
    random_number_generator(&q, 100, 1, 40);
    printq(&q, 10);  // 10 numbers per line
    printf("\n");

    // 2.
    // Assign and output integer i the 2nd element from the tail of Q,
    // leaving Q unchanged.
    // (Note: Be sure to do in the way like the shadow following the body.)
    printf(
        "b: assign i the 2nd element from the tail without changing the "
        "queue\n");
    int i = getElement(&q, FROM_BACK, 2, RECOVER);
    printf("i = %d\n", i);
    printq(&q, 10);
    printf("\n");

    // 3.
    // Assign and output integer j the 8th element from the head of Q,
    // leaving Q unchanged.
    // random_number_generator(&q, 10, 0, 50);
    // printq(&q, 10);  // 10 numbers per line
    printf(
        "c: assign j the 8th element from the front without changing the "
        "queue\n");
    int j = getElement(&q, FROM_FRONT, 8, RECOVER);
    printf("j = %d\n", j);
    printq(&q, 10);
    printf("\n");

    // Assign and output integer k the 3rd element from the tail of Q.
    // (Note: Be sure to do in the way like the shadow following the body.)
    // random_number_generator(&q, 10, 0, 50);
    // printq(&q, 10);  // 10 numbers per line
    printf("d: assign k the 3rd element from the tail\n");
    int k = getElement(&q, FROM_BACK, 3, NO_RECOVER);
    printf("k = %d\n", k);
    printq(&q, 10);
    printf("\n");

    return 0;
}