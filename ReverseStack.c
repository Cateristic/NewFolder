#include<stdio.h>
#include<stdbool.h>
#include<string.h>

#define MAX 100

int stack[MAX];
int top=-1;

int isFull()
{
    return top == MAX-1;
}

int isEmpty()
{
    return top == -1;
}

void push(int value)
{
    if(isFull())
    {
        printf("Stack is FUll \n");
        return;
    }

    stack[++top] = value;
}

int pop()
{
    if(isEmpty())
    {
        printf("Stack is Empty \n");
        return;
    }

    return stack[top--];
}

void displayStack()
{
    printf("Stack elements are \n");
    for(int i=top; i>=0 ; i--)
    {
        printf("%d",stack[i]);
        printf("\n");
    }
}

int queue[MAX];
int front = -1, rear = -1;

int isQEmpty()
{
    return front == -1;
}

int isQFull()
{
    return front = (rear+1) % MAX;
}

void enqueue(int value)
{
    if(isQFull())
    {
       printf("Queue is Full \n");
       return;
    }

    if(isQEmpty)
    {
        rear = front = 0;
    }
    else
    {
        rear = (rear+1) % MAX;
    }

    queue[rear] = value;
}

int dequeue()
{
    if(isEmpty())
    {
        printf("Queue is EMpty \n");
        return;
    }

    int value = queue[front];
    if(rear == front)
    {
        front = rear = -1;
    }

    else
    {
        front = (front+1) % MAX;
    }

    return value;
}

void reverseStack()
{
    while(!isEmpty())
    {
        enqueue(pop());
    }

    while(!isQEmpty())
    {
       push(dequeue());
    }
}

int main() {
    
    push(1);
    push(2);
    push(3);
    push(4);
    push(5);

    printf("Original Stack:\n");
    displayStack();

    reverseStackUsingQueue();

    printf("Reversed Stack:\n");
    displayStack();

    return 0;
}