#include<stdio.h>

void fiboI(int n)
{
    int a=0;
    int b=1;
    int next;

    if(n>=1)
    {
        printf("%d",a);
    }
    if(n>=2)
    {
        printf("%d",b);
    }

    for(int i=3; i<=n ; i++)
    {
        next = a+b;
        printf("%d",next);
        a = b;
        b = next;
    }

    printf("\n");
}

int fiboR(int n)
{
    if(n==0)
    {
        return 0;
    }
    else if(n==1)
    {
        return 1;
    }
    else
    {
        return fiboR(n-1)+fiboR(n-2);
    }
}

void printF(int n)
{
    for(int i=0; i<n; i++)
    {
        printf("%d",fiboR(i));
    }

    printf("\n");
}