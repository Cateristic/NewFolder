#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 100

int stack[MAX];
int top = -1;

int isEmpty() {
    return top == -1;
}

int isFull() {
    return top == MAX - 1;
}

void push(int value) {
    if (isFull()) {
        printf("Stack is Full!\n");
        return;
    }
    stack[++top] = value;
}

int pop() {
    if (isEmpty()) {
        return -1;
    }
    return stack[top--];
}

int peek() {
    if (isEmpty()) {
        return -1;
    }
    return stack[top];
}

int apply(int op1, int op2, char operand) {
    switch (operand) {
        case '+': return op1 + op2;
        case '-': return op1 - op2;
        case '*': return op1 * op2;
        case '/': return op1 / op2;
        case '^': return (int)pow(op1, op2);
        default: return 0;
    }
}

int evaluatePostfix(char *postfix) {
    top = -1; // Reset stack

    for (int i = 0; i < strlen(postfix); i++) {
        char ch = postfix[i];

        if (ch >= '0' && ch <= '9') {
            push(ch - '0');  // convert char to int
        } else if (ch == '^' || ch == '*' || ch == '/' || ch == '+' || ch == '-') {
            int op2 = pop();
            int op1 = pop();
            int result = apply(op1, op2, ch);
            push(result);
        }
    }

    return pop();
}

int main() {
    int choice;
    char postfix[MAX];

    while (1) {
        printf("\nMenu:\n");
        printf("1. Evaluate Postfix Expression\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter postfix expression (single-digit operands): ");
                scanf("%s", postfix);
                int result = evaluatePostfix(postfix);
                printf("Result: %d\n", result);
                break;

            case 2:
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
