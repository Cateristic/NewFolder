#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define MAX 100

char stack[MAX];
int top = -1;

bool isEmpty()
{
    return top == -1;
}

bool isFull()
{
    return top == MAX -1;
}

void push(char ch)
{
    if(isEmpty())
    {
        printf("is empty \n");
        return;
    }
    stack[++top] = ch;
}

