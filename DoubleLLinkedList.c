#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
    int data;
    struct Node* perv;
    struct Node* next;
} Node;

Node* head = NULL;

Node* createNode(int data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = newNode->perv = NULL;
    return newNode;
}

void insertEnd(int data)
{
    Node* newNode = createNode(data);

    if(head == NULL)
    {
        head = newNode;
        return ;
    }

    Node* temp = head;

    while(temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = newNode;
    newNode->perv = temp;
}

void display()
{
    Node* temp = head;
    printf("Double linekd list is \n");
    while(temp != NULL)
    {
        printf("%d",temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void findEven()
{
    Node* temp = head;
    int found = 0;

    printf("Even number are \n");

    while(temp != NULL)
    {
        if(temp->data % 2 == 0)
        {
            printf("%d",temp->data);
            found = 1;
        }
        temp = temp->next;
    }

    if(!found)
    {
        printf("Nonde \n");
    }

    printf("\n");
}


int main()
{
   int choice,value;

   while(1)
   {
    printf("\nMenu:\n");
    printf("1. Insert Node\n");
    printf("2. Display List\n");
    printf("3. Find Even Nodes\n");
    printf("4. Exit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
           printf("Enter value to insert : \n");
           scanf("%d",&value);
           insertEnd(value);
           break;
        
        case 2:
           display();
           break;

        case 3:
           findEven();
           break;

        case 4:
            exit(0);

        default:
           printf("Enter the valid choice");
    }
   }


   return 0;
}