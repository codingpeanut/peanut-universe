/********************************
 *	Author:	411440521 JoshLee	*
 *	Date:	2023/10/6			*
 ********************************/
#include <stdio.h>

#define SIZE 100
int stack[SIZE];    // store position of left brackets
int top = -1;

// stack functions
int full();
int empty();
void push(char);
int pop();

// self defined
char corresponding_bracket(char);
int encode_left_bracket(char);
char decode_left_bracket(int);

int main() {
    char symb;
    int pos = 0;
    
    while((symb = getchar()) != '\n') {
        if(symb == '(' || symb == '[') {
            int left_bracket_type = encode_left_bracket(symb);
            push(pos * 10 + left_bracket_type);                              // * NOTICE * tens and higher stands for left_bracket_position; ones stands for left_bracket_type
        } else if(symb == ')' || symb == ']') {
            char right_bracket = symb;                                       // right_bracket on pos
            if(!empty()) {
                int popped_value = pop();                                    // encoded_left_bracket on the top of the stack
                int left_bracket_pos = popped_value / 10;                    // get pos
                char left_bracket = decode_left_bracket(popped_value % 10);  // get bracket type
                if ((right_bracket == ')' && left_bracket == '(') ||
                    (right_bracket == ']' && left_bracket == '[')) {         // if paired
                    printf("%c%d,%d%c\n", left_bracket, left_bracket_pos, pos, right_bracket);  // print bracket pair position
                } else {                                                     // if not paired
                    // printf("位置編號%d的左括弧%c沒有可配對的右括弧%c\n", left_bracket_pos, left_bracket, corresponding_bracket(left_bracket));
                    printf("位置編號%d的右括弧%c沒有可配對的左括弧%c\n", pos, right_bracket, corresponding_bracket(right_bracket));
                }
            } else {                                                         // lack left_bracket
                printf("位置編號%d的右括弧%c沒有可配對的左括弧%c\n", pos, right_bracket, corresponding_bracket(right_bracket));
            }
        }
        pos++;
    }
    while(!empty()) {    // 在堆疊裡的左括號都沒有右括號
        int popped_value = pop();
        int left_bracket_pos = popped_value / 10;
        char left_bracket = decode_left_bracket(popped_value % 10);
        printf("位置編號%d的左括弧%c沒有可配對的右括弧%c\n", left_bracket_pos, left_bracket, corresponding_bracket(left_bracket));
    }
    return 0;
}
// 411440521 JoshLee
int full() {
    return top == SIZE - 1;
}

int empty() {
    return top == -1;
}

void push(char c) {
    if(!full())
        stack[++top] = c;
    else
        printf("Stack is full!\n");
}

int peek() {
    return stack[top];
}

int pop() {
    if (!empty()) {
        int popped_value = stack[top];
        stack[top--] = 0;
        return popped_value;
    } else {
        printf("Stack is empty!\n");
        return -1;
    }
}

char corresponding_bracket(char bracket) {
    if(bracket == '(') return ')';
    if(bracket == '[') return ']';
    if(bracket == ')') return '(';
    if(bracket == ']') return '[';
    return '\0';
}

int encode_left_bracket(char bracket) {
    if(bracket == '(') return 1;
    if(bracket == '[') return 2;
    return -1;
}

char decode_left_bracket(int encoded_bracket) {
    if(encoded_bracket == 1) return '(';
    if(encoded_bracket == 2) return '[';
}