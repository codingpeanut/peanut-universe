/********************************
 *	Author:	411440521 JoshLee	*
 *	Date:	2023/12/2			*
 ********************************/
#include <stdio.h>
#include <stdlib.h>

// Define ListNode
typedef struct _ListNode {
    char symb;
    int pos;
    struct _ListNode *link;
} Bracket;

// Define LinkedStack
typedef struct LinkedStack {
    Bracket *top;
} LinkedStack;


// LinkedStack functions
int empty(LinkedStack *s) {
    return s->top == NULL;
}

void push(LinkedStack *s, char symb, int pos) {
    Bracket *new_node = (Bracket*)malloc(sizeof(Bracket));
    new_node->symb = symb;
    new_node->pos = pos;
    new_node->link = s->top;
    
    s->top = new_node;
}
// 411440521 JoshLee
Bracket *pop(LinkedStack *s) {
    if (empty(s)) {
        printf("Stack is empty!\n");
        exit(1);
    }

    Bracket *top = s->top;
    s->top = top->link;
    
    return top;
}

// Create a new LinkedStack
LinkedStack create_LinkedStack() {
    LinkedStack ll;
    ll.top = NULL;
    return ll;
}

// Self-defined
int is_left(char symb) 
{ return symb == '(' || symb == '[' || symb == '{'; }

int is_right(char symb) 
{ return symb == ')' || symb == ']' || symb == '}'; }

char correspond(char type) {
    if (type == '(') return ')';
    if (type == '[') return ']';
    if (type == '{') return '}';
    if (type == ')') return '(';
    if (type == ']') return '[';
    if (type == '}') return '{';
    return '\0';
}
// 411440521 JoshLee
int main() {
    LinkedStack s = create_LinkedStack();

    char symb;
    int pos = 0;

    while ((symb = getchar()) != '\n') {
        if (is_left(symb)) {
            push(&s, symb, pos);
        } else if (is_right(symb)) {
            if (!empty(&s)) {
                Bracket *left = pop(&s);
                if (symb == correspond(left->symb)) {
                    printf("%c%d,%d%c\n", left->symb, left->pos, pos, symb);
                    free(left);  // Free the memory allocated for the popped node
                } else {
                    printf("right parenthesis %c at %d has no matching left parenthesis %c\n", symb,
                           pos, correspond(symb));
                    // Free the memory allocated for the popped node
                    free(left);
                }
            } else {
                printf("right parenthesis %c at %d has no matching left parenthesis %c\n", symb, pos,
                       correspond(symb));
            }
        }
        pos++;
    }
    while (!empty(&s)) {
        Bracket *left = pop(&s);
        printf("left parenthesis %c at %d has no matching right parenthesis %c\n", left->symb, left->pos, correspond(left->symb));
        // Free the memory allocated for the popped node
        free(left);
    }

    return 0;
}