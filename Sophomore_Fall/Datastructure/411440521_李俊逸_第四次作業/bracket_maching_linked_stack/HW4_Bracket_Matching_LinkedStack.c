/********************************
 *	Author:	411440521 JoshLee	*
 *	Date:	2023/12/16			*
 ********************************/
#include <stdio.h>
#include <stdlib.h>

// Define Bracket
typedef struct _Bracket *BracketPtr;
typedef struct _Bracket {
    char symb;
    int pos;
    BracketPtr link;
} Bracket;

// LinkedStack functions
int emptys(BracketPtr *top) { return *top == NULL; }

void pushs(BracketPtr *top, char symb, int pos) {
    BracketPtr new_node = (Bracket *)malloc(sizeof(Bracket));
    new_node->symb = symb;
    new_node->pos = pos;
    new_node->link = *top;

    *top = new_node;
}

BracketPtr pops(BracketPtr *top) {
    if (emptys(top)) {
        printf("Stack is empty!\n");
        exit(1);
    }

    BracketPtr popped = *top;
    *top = popped->link;

    return popped;
}

// Create a new LinkedStack
BracketPtr create_stack() { return NULL; }

// Self-defined
int is_left(char symb) { return symb == '(' || symb == '[' || symb == '{'; }

int is_right(char symb) { return symb == ')' || symb == ']' || symb == '}'; }

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
    BracketPtr top = create_stack();

    char symb;
    int pos = 0;

    while ((symb = getchar()) != '\n') {
        if (is_left(symb)) {
            pushs(&top, symb, pos);
        } else if (is_right(symb)) {
            if (!emptys(&top)) {
                BracketPtr left = pops(&top);
                if (symb == correspond(left->symb)) {
                    printf("%c%d,%d%c\n", left->symb, left->pos, pos, symb);
                    free(left);  // Free the memory allocated for the popped node
                } else {
                    printf("right parenthesis %c at %d has no matching left parenthesis %c\n", symb, pos, correspond(symb));
                    free(left);  // Free the memory allocated for the popped node
                }
            } else {
                printf("right parenthesis %c at %d has no matching left parenthesis %c\n", symb, pos, correspond(symb));
            }
        }
        pos++;
    }
    while (!emptys(&top)) {
        BracketPtr left = pops(&top);
        printf("left parenthesis %c at %d has no matching right parenthesis %c\n", left->symb, left->pos, correspond(left->symb));
        free(left);  // Free the memory allocated for the popped node
    }

    return 0;
}