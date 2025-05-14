#include <stdio.h>
#include <stdlib.h>

// Tree Node definition
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert into Binary Tree (level order)
Node* insert(Node* root, int data) {
    if (root == NULL) return createNode(data);

    Node* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        Node* temp = queue[front++];

        if (!temp->left) {
            temp->left = createNode(data);
            break;
        } else {
            queue[rear++] = temp->left;
        }

        if (!temp->right) {
            temp->right = createNode(data);
            break;
        } else {
            queue[rear++] = temp->right;
        }
    }
    return root;
}

// Traversals
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(Node* root) {
    if (root) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Node* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

// Count total nodes
int countNodes(Node* root) {
    if (!root) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Count leaf nodes
int countLeafNodes(Node* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 1;
    return countLeafNodes(root->left) + countLeafNodes(root->right);
}

// Count non-leaf nodes
int countNonLeafNodes(Node* root) {
    if (!root || (!root->left && !root->right)) return 0;
    return 1 + countNonLeafNodes(root->left) + countNonLeafNodes(root->right);
}

// Mirror image
void mirror(Node* root) {
    if (!root) return;
    Node* temp = root->left;
    root->left = root->right;
    root->right = temp;

    mirror(root->left);
    mirror(root->right);
}

// Height of tree
int height(Node* root) {
    if (!root) return 0;
    int l = height(root->left);
    int r = height(root->right);
    return 1 + (l > r ? l : r);
}

// Main menu
int main() {
    Node* root = NULL;
    int choice, value;

    do {
        printf("\n--- Binary Tree Menu ---\n");
        printf("1. Insert Node\n");
        printf("2. Inorder Traversal\n");
        printf("3. Preorder Traversal\n");
        printf("4. Postorder Traversal\n");
        printf("5. Count Total Nodes\n");
        printf("6. Count Leaf Nodes\n");
        printf("7. Count Non-Leaf Nodes\n");
        printf("8. Mirror Tree\n");
        printf("9. Height of Tree\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            case 2:
                printf("Inorder: ");
                inorder(root);
                printf("\n");
                break;
            case 3:
                printf("Preorder: ");
                preorder(root);
                printf("\n");
                break;
            case 4:
                printf("Postorder: ");
                postorder(root);
                printf("\n");
                break;
            case 5:
                printf("Total Nodes: %d\n", countNodes(root));
                break;
            case 6:
                printf("Leaf Nodes: %d\n", countLeafNodes(root));
                break;
            case 7:
                printf("Non-Leaf Nodes: %d\n", countNonLeafNodes(root));
                break;
            case 8:
                mirror(root);
                printf("Tree mirrored.\n");
                break;
            case 9:
                printf("Height of Tree: %d\n", height(root));
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 0);

    return 0;
}