/********************************
 *	Author:	411440521 JoshLee	*
 *	Date:	2023/12/16			*
 ********************************/
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

// LinkedQueue functions
NodePtr create_queue() { return NULL; }

int emptyq(NodePtr *front) { return *front == NULL; }
// 411440521 JoshLee
void addq(NodePtr *front, int data) {
    NodePtr new_node = (NodePtr)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Memory allocation error!\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->link = NULL;

    if (*front == NULL) {
        *front = new_node;
    } else {
        NodePtr temp = *front;
        while (temp->link != NULL) {
            temp = temp->link;
        }
        temp->link = new_node;
    }
}

NodePtr deleteq(NodePtr *front) {
    if (emptyq(front)) {
        printf("Queue is empty!\n");
        exit(1);
    }

    NodePtr deleted = *front;
    *front = deleted->link;

    return deleted;
}

void printq(NodePtr front, int elements_in_one_line) {
    NodePtr current = front;
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

// Self Defined
// 411440521 JoshLee
// Helper function to reverse the queue
void reverse_queue(NodePtr *q) {
    if (emptyq(q)) {
        return;
    }

    int fr = deleteq(q)->data;

    reverse_queue(q);

    addq(q, fr);
}

void random_number_generator(NodePtr *front, int range, int offset, int len) {
    srand(time(NULL));
    while (!emptyq(front)) deleteq(front);
    for (int i = 0; i < len; i++) addq(front, rand() % range + offset);
}

// Helper function to recover elements to the original queue
void recover_elements(NodePtr *q, NodePtr *temp_q) {
    while (!emptyq(temp_q)) {
        NodePtr deleted = deleteq(temp_q);
        addq(q, deleted->data);
        free(deleted);
    }
}
// 411440521 JoshLee
// Helper function to get an element from the queue
int getElement(NodePtr *front, Direction direction, int position,RecoveryOption recovery) {
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
    } else {                       // Assuming FROM_BACK
        reverse_queue(front);      // reverse queue to delete the back n-th element
        for (i = 0; i < position; i++) {
            NodePtr deleted = deleteq(front);
            addq(&temp_q, deleted->data);
            deleted_value = deleted->data;
            free(deleted);
        }
        reverse_queue(front);      // reverse queue to recover_elements to the
                                   // original direction
        reverse_queue(&temp_q);    // same
        if (recovery == RECOVER) recover_elements(front, &temp_q);
    }

    return deleted_value;
}
// 411440521 JoshLee
int main() {
    NodePtr q = create_queue();
    int m;

    // Question 1: assign m the 2nd element from the back
    random_number_generator(&q, 10, 0, 50);
    printq(q, 10);  // 10 numbers per line
    printf("p1: assign m the 2nd element from the back\n");
    m = getElement(&q, FROM_BACK, 2, NO_RECOVER);
    printf("m = %d\n", m);
    printq(q, 10);
    printf("\n");

    // Question 2: assign m the 2nd element from the back without changing the queue
    random_number_generator(&q, 10, 0, 50);
    printq(q, 10);  // 10 numbers per line
    printf("p2: assign m the 2nd element from the back without changing the queue\n");
    m = getElement(&q, FROM_BACK, 2, RECOVER);
    printf("m = %d\n", m);
    printq(q, 10);
    printf("\n");

    // Question 3: assign m the 3rd element from the back
    random_number_generator(&q, 10, 0, 50);
    printq(q, 10);  // 10 numbers per line
    printf("p3: assign m the 3rd element from the back\n");
    m = getElement(&q, FROM_BACK, 3, NO_RECOVER);
    printf("m = %d\n", m);
    printq(q, 10);
    printf("\n");

    // Question 4: assign m the 3rd element from the back without changing the queue
    random_number_generator(&q, 10, 0, 50);
    printq(q, 10);  // 10 numbers per line
    printf("p4: assign m the 3rd element from the back without changing the queue\n");
    m = getElement(&q, FROM_BACK, 3, RECOVER);
    printf("m = %d\n", m);
    printq(q, 10);
    printf("\n");

    // Question 5: assign m the 4th element from the back
    random_number_generator(&q, 10, 0, 50);
    printq(q, 10);  // 10 numbers per line
    printf("p5: assign m the 4th element from the back\n");
    m = getElement(&q, FROM_BACK, 4, NO_RECOVER);
    printf("m = %d\n", m);
    printq(q, 10);
    printf("\n");

    // Question 6: assign m the 4th element from the back without changing the queue
    random_number_generator(&q, 10, 0, 50);
    printq(q, 10);  // 10 numbers per line
    printf("p6: assign m the 4th element from the back without changing the queue\n");
    m = getElement(&q, FROM_BACK, 4, RECOVER);
    printf("m = %d\n", m);
    printq(q, 10);
    printf("\n");
	// 411440521 JoshLee
    return 0;
}
