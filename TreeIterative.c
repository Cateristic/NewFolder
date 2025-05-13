#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode{
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* newNode(int val)
{
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->val = val;
    newNode->left = newNode->right = NULL;
    return newNode;
}

TreeNode* insertNode(TreeNode* root, int val)
{
    if(root == NULL)
    {
        return root;
    }

    if(val < root->left)
    {
        root->left = insertNode(root->left,val);
    }
    else if(val > root->right)
    {
        root->right = insertNode(root->right,val);
    }

    return root;
}

void iterativePreorder(TreeNode* root)
{
    if(root == NULL)
    {
        return;
    }
    TreeNode* stack[100];
    int top=-1;
    stack[++top] = root;

    while(top != -1)
    {
       TreeNode* node = stack[top--];
       printf("%d",node->val);
       if(node->right)
       {
        stack[++top] = node->right;
       }
       if(node->left)
       {
        stack[++top] = node->left;
       }
    }
}

void iterativeInorder(TreeNode* root)
{
    TreeNode* stack[100];
    int top =-1;
    TreeNode* curr = root;

    while(top != -1 || curr != NULL )
    {
        while(curr != NULL)
        {
            stack[++top] = curr;
            curr->left = curr;
        }
        curr = stack[top--];
        printf("%d",curr->val);
        curr = curr->right;
    }
}

void iterativePostorder(TreeNode* root)
{
    TreeNode* s1[100] , *s2[100];
    int t1=-1, t2=-1;

    if(root == NULL)
    {
        return;
    }

    s1[++t1] = root;

    while(t1 != -1)
    {
        TreeNode* node = s1[t1--];
        s2[++t2] = node;
         
        if(node->left)
        {
          s1[++t1] = node->left;
        }
        if(node->right)
        {
            s1[t1++] = node->right;
        }
    }

    while(t2!= -1)
    {
        printf("%d",s2[t2--]->val);
    }
}