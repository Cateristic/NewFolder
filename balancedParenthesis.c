#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX 100

int stack[MAX];
int top = -1;

bool isEmpty() {
    return top == -1;
}

bool isFull() {
    return top == MAX - 1;
}

void push(char value) {
    if (isFull()) {
        printf("Stack overflow!\n");
        return;
    }
    stack[++top] = value;
}

char pop() {
    if (isEmpty()) {
        return -1;
    }
    return stack[top--];
}

char peek() {
    if (isEmpty()) {
        return -1;
    }
    return stack[top];
}

bool isValidParenthesis(char *expression) {
    top = -1;  // Reset stack for each new expression

    for (int i = 0; i < strlen(expression); i++) {
        char ch = expression[i];

        if (ch == '(' || ch == '[' || ch == '{') {
            push(ch);
        } else if (ch == ')' || ch == ']' || ch == '}') {
            if (isEmpty()) {
                return false;
            }

            char topElement = pop();
            if ((ch == ')' && topElement != '(') ||
                (ch == ']' && topElement != '[') ||
                (ch == '}' && topElement != '{')) {
                return false;
            }
        }
    }

    return isEmpty(); // Return true if stack is empty (balanced)
}

int main() {
    char expression[MAX];
    int choice;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Check for Balanced Parentheses\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter expression: ");
                scanf("%s", expression);

                if (isValidParenthesis(expression)) {
                    printf("Parentheses are balanced.\n");
                } else {
                    printf("Parentheses are NOT balanced.\n");
                }
                break;

            case 2:
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
