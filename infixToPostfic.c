#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;

// Stack functions
bool isEmpty() {
    return top == -1;
}

bool isFull() {
    return top == MAX - 1;
}

void push(char ch) {
    if (isFull()) {
        printf("Stack is full!\n");
        return;
    }
    stack[++top] = ch;
}

char pop() 
{
    if (isEmpty()) {
        return '\0';
    }
    return stack[top--];
}

char peek() 
{
    if (isEmpty()) {
        return '\0';
    }
    return stack[top];
}

// Operator precedence
int precedence(char ch) 
{
    if (ch == '^')
        return 3;
    else if (ch == '*' || ch == '/')
        return 2;
    else if (ch == '+' || ch == '-')
        return 1;
    else
        return 0;
}

// Infix to Postfix conversion
void infixToPostfix(char *infix, char *postfix) {
    int j = 0;
    top = -1; // Reset stack

    for (int i = 0; i < strlen(infix); i++) {
        char ch = infix[i];

        if ((ch >= 'a' && ch <= 'z') ||
            (ch >= 'A' && ch <= 'Z') ||
            (ch >= '0' && ch <= '9')) {
            postfix[j++] = ch;
        } else if (ch == '(') {
            push(ch);
        } else if (ch == ')') {
            while (!isEmpty() && peek() != '(') {
                postfix[j++] = pop();
            }
            if (!isEmpty() && peek() == '(') {
                pop(); // Remove '('
            }
        } else { // Operator
            while (!isEmpty() && precedence(peek()) >= precedence(ch)) {
                postfix[j++] = pop();
            }
            push(ch);
        }
    }

    while (!isEmpty()) {
        postfix[j++] = pop();
    }

    postfix[j] = '\0'; // Null-terminate
}

// Menu-driven main
int main() {
    char infix[MAX], postfix[MAX];
    int choice;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Convert Infix to Postfix\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter infix expression: ");
                scanf("%s", infix);
                infixToPostfix(infix, postfix);
                printf("Postfix expression: %s\n", postfix);
                break;

            case 2:
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
