#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

char stack[MAX][MAX];
int top = -1;

bool isEmpty() {
    return top == -1;
}

bool isFull() {
    return top == MAX - 1;
}

void push(char *str) {
    if (isFull()) {
        printf("Stack is full\n");
        return;
    }
    strcpy(stack[++top], str);
}

char *pop() {
    if (isEmpty()) {
        return NULL;
    }
    return stack[top--];
}

char *peek() {
    if (isEmpty()) {
        return NULL;
    }
    return stack[top];
}

void postFixToInfix(char *postfix) {
    top = -1; // Reset the stack

    for (int i = 0; i < strlen(postfix); i++) {
        char ch = postfix[i];

        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            char op[2] = {ch, '\0'};
            push(op);
        } 
        else if (ch == '^' || ch == '/' || ch == '*' || ch == '+' || ch == '-') {
            char *op2 = pop();
            char *op1 = pop();

            if (op1 == NULL || op2 == NULL) {
                printf("Invalid postfix expression.\n");
                return;
            }

            char temp[MAX];
            snprintf(temp, MAX, "(%s%c%s)", op1, ch, op2);
            push(temp);
        }
    }

    if (top != 0) {
        printf("Invalid postfix expression.\n");
        return;
    }

    printf("Infix expression: %s\n", pop());
}

int main() {
    int choice;
    char postfix[MAX];

    while (1) {
        printf("\nMenu:\n");
        printf("1. Convert Postfix to Infix\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline from buffer

        switch (choice) {
            case 1:
                printf("Enter postfix expression (only alphabets and operators): ");
                scanf("%s", postfix);
                postFixToInfix(postfix);
                break;

            case 2:
                printf("Exiting program.\n");
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
