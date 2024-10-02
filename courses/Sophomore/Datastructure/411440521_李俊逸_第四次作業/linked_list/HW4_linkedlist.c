/********************************
 *	Author:	411440521 JoshLee	*
 *	Date:	2023/12/16			*
 ********************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define ListNode
typedef struct _Node *NodePtr;
typedef struct _Node {
    int data;      // Store the value of the node
    NodePtr next;  // Store the address of the next node
} Node;

// List functions

// Insert a node behind
void insert(NodePtr *target, int data) {
    NodePtr new_node = (NodePtr)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;

    // for empty list (Optional)
    if (*target == NULL) {
        *target = new_node;
        return;
    }

    // for non-empty list
    new_node->next = (*target)->next;
    (*target)->next = new_node;
}
// 411440521 JoshLee
// Delete the node behind and return its data
int delete(NodePtr *target) {
    // for empty
    if (*target == NULL) {
        printf("List is empty!");
        exit(1);
    }

    // for the last element (Optional)
    if ((*target)->next == NULL) {
        NodePtr deleted = *target;
        int data = deleted->data;

        *target = NULL;
        free(deleted);
        return data;
    }

    // for other elements
    NodePtr deleted = (*target)->next;
    int data = deleted->data;

    (*target)->next = deleted->next;
    free(deleted);
    return data;
}

// Find the first position in the list not less than the given value
NodePtr insertnum(NodePtr *head, int value) {
    NodePtr *current = head;  // Use an indirect pointer

    // Traverse the list to find the appropriate position
    while (*current != NULL && (*current)->data < value) {
        current = &((*current)->next);
    }

    // Create a new node and insert it into the list
    NodePtr new_node = (NodePtr)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = *current;
    *current = new_node;

    return new_node;
}

// Concatenate two lists
NodePtr concatenate(NodePtr p, NodePtr q) {
    if (p == NULL) return q;

    NodePtr current = p;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = q;

    return p;
}
// 411440521 JoshLee
// Reverse the list
NodePtr invert(NodePtr head) {
    NodePtr prev = NULL;
    NodePtr current = head;
    NodePtr next_node;

    while (current != NULL) {
        next_node = current->next;
        current->next = prev;
        prev = current;
        current = next_node;
    }

    return prev;
}

// Convert the list to a circular list
NodePtr Lin2Cir(NodePtr head) {
    NodePtr current = head;

    // Get the last node
    while (current->next != NULL) {
        current = current->next;
    }

    // Connect the last node to the head
    current->next = head;

    return head;
}

// Traverse the list and print all values
void print(NodePtr head) {
    NodePtr current = head;
    int elements_in_current_line = 0;
    int elements_in_one_line = 10;

    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;

        if (++elements_in_current_line >= elements_in_one_line) {
            printf("\n");
            elements_in_current_line = 0;
        }
    }
    printf(elements_in_current_line ? "\n" : "");
}

// Self-Defined
// 411440521 JoshLee
// Create an empty list
NodePtr create_list() { return NULL; }

// Insert a node at the end
void append(NodePtr *target, int data) {
    // Traverse the list until the end is reached
    while (*target != NULL)
        // Move to the next node using its next pointer
        target = &((*target)->next);

    NodePtr new_node = (NodePtr)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;

    *target = new_node;
}

// Advance function, move the pointer by a specified number of steps
NodePtr advance(NodePtr current, int steps) {
    int i;
    for (i = 0; i < steps && current != NULL; i++) current = current->next;
    return current;
}

// Assume the filter function to filter elements based on a condition
NodePtr filter(int (*condition)(int), NodePtr head) {
    NodePtr result = create_list();
    NodePtr current = head;

    while (current != NULL) {
        if (condition(current->data)) {
            append(&result, current->data);
        }
        current = current->next;
    }

    return result;
}

// Free the memory of the list
void free_list(NodePtr *head) {
    NodePtr current = *head;  // Current list node, used for traversing the list

    while (current != NULL) {
        NodePtr temp = current;   // Temporary store the current node
        current = current->next;  // Move to the next node
        free(temp);               // Free the memory of the node
        temp = NULL;
    }

    *head = NULL;  // Set the external pointer (list->head) to NULL
}

// Question
// 411440521 JoshLee
// Odd number condition (for filter)
int is_odd(int value) { return value % 2 == 1; }

// Generate random numbers
void random_number_generator(NodePtr *head, int range, int offset, int len) {
    srand(time(NULL));
    free_list(head);
    int i;
    for (i = 0; i < len; i++) insertnum(head, rand() % range + offset);
}

// Eeny, meeny, miny, moe algorithm
NodePtr emmm(NodePtr *head, int steps) {
    NodePtr result = create_list();

    NodePtr current = *head;  // point to 1st
    while (current->next != current) {
        current = advance(current, steps - 2);  // point to 5th

        int deleted = delete (&current);  // delete 6th
        append(&result, deleted);
        current = advance(current, 1);  // start with deleted + 1
    }

    // the last element in the circular list
    int last_deleted = delete (&current);
    append(&result, last_deleted);

    *head = NULL;  // prevent dangling pointer
    return result;
}
// 411440521 JoshLee
int main() {
    NodePtr list = create_list();

    // 1.
    // Use random numbers to generate 50 numbers,
    // then use print() to print out the generated random numbers,
    // use insertnum() to add them to the list,
    // and finally use print() to print out the elements in the list.
    random_number_generator(&list, 90, 10, 50);
    printf("List:\n");
    print(list);
    printf("\n");

    // 2.
    // Use invert() to invert the entire list
    // and print out the elements in the list
    list = invert(list);
    printf("Reversed List:\n");
    print(list);
    printf("\n");

    // 3.
    // Use delete() to remove odd numbers from the list into a new list,
    // and use print() to print out the elements in the two lists respectively.
    NodePtr odd_list = filter(is_odd, list);
    printf("Odd List:\n");
    print(odd_list);
    printf("\n");
    printf("List:\n");
    print(list);
    printf("\n");

    // 4.
    // Use int concatenate() to string the odd-numbered list
    // just taken out in front of the original list,
    // and use print() to print out the elements in the list.
    list = concatenate(odd_list, list);
    printf("Concatenated List:\n");
    print(list);
    printf("\n");

    // 5.
    // Use int Lin2Cir() to turn the list in (4) into a circular list.
    list = Lin2Cir(list);

    // 6.
    // After it becomes a circular list,
    // start counting from the first node.
    // When it reaches the sixth element,
    // use delete() to delete the node and
    // output the content of the node
    // until the entire circular list has no nodes.
    printf("Eeny, meeny, miny, moe Result:\n");
    NodePtr result = emmm(&list, 6);  // list was deleted
    print(result);

    // Free the memory
    free_list(&result);
	// 411440521 JoshLee
    return 0;
}
