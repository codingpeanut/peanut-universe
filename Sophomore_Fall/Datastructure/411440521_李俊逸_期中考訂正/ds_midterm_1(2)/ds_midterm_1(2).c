/********************************
 *	Author:	411440521 JoshLee	*
 *	Date:	2023/11/30			*
 ********************************/
#include <stdio.h>
#include <stdlib.h>


#define SIZE 100

typedef struct _bracket {
    char type;
    int pos;
} Bracket;

Bracket stack[SIZE];
int top = -1;


// stack functions
int full() {
    return top == SIZE - 1;
}

int empty() {
    return top == -1;
}

void push(char type, int pos) {
    if (full()) {
        printf("Stack is full!\n");
        exit(1);
    }
    Bracket left;
    left.type = type;
    left.pos = pos;
    stack[++top] = left;
}

Bracket pop() {
    if (empty()) {
        printf("Stack is empty!\n");
        exit(2);
    } 
    return stack[top--];
}


// self defined
char correspond(char bracket) {
    if (bracket == '(') return ')';
    if (bracket == '[') return ']';
    if (bracket == '{') return '}';
    if (bracket == ')') return '(';
    if (bracket == ']') return '[';
    if (bracket == '}') return '{';
    return '\0';
}

int is_left(char symb) 
{ return (symb == '(' || symb == '[' || symb == '{') ? 1 : 0; }

int is_right(char symb) 
{ return (symb == ')' || symb == ']' || symb == '}') ? 1 : 0; }


int main() {
    char symb;
    int pos = 0;

    while ((symb = getchar()) != '\n') {
        if (is_left(symb)) {
            push(symb, pos);
        } else if (is_right(symb)) {
            Bracket right = {symb, pos};
            if (!empty()) {
                Bracket left = pop();
                if (right.type == correspond(left.type)) {
                    printf("%c%d,%d%c\n", left.type, left.pos, right.pos, right.type);
                } else {
                    push(left.type, left.pos);
                    printf("right parenthesis %c at %d has no matching left parenthesis %c\n", right.type, right.pos, correspond(right.type));
                }
            } else {
                printf("right parenthesis %c at %d has no matching left parenthesis %c\n", right.type, right.pos, correspond(right.type));
            }
        }
        pos++;
    }
    while (!empty()) {
        Bracket left = pop();
        printf("left parenthesis %c at %d has no matching right parenthesis %c\n", left.type, left.pos, correspond(left.type));
    }
    return 0;
}
