#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* newNode(int val) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->val = val;
    node->left = node->right = NULL;
    return node;
}

TreeNode* insert(TreeNode* root, int val) {
    if (root == NULL) return newNode(val);
    if (val < root->val) root->left = insert(root->left, val);
    else if (val > root->val) root->right = insert(root->right, val);
    return root;
}

TreeNode* minValueNode(TreeNode* node) {
    TreeNode* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

TreeNode* delete(TreeNode* root, int key) {
    if (root == NULL) return root;
    if (key < root->val) root->left = delete(root->left, key);
    else if (key > root->val) root->right = delete(root->right, key);
    else {
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root); return temp;
        }
        else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root); return temp;
        }
        TreeNode* temp = minValueNode(root->right);
        root->val = temp->val;
        root->right = delete(root->right, temp->val);
    }
    return root;
}

// Recursive Traversals
void inorder(TreeNode* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->val);
        inorder(root->right);
    }
}

void preorder(TreeNode* root) {
    if (root) {
        printf("%d ", root->val);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(TreeNode* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->val);
    }
}

// Iterative Traversals
void iterativePreorder(TreeNode* root) {
    if (root == NULL) return;
    TreeNode* stack[100];
    int top = -1;
    stack[++top] = root;
    while (top != -1) {
        TreeNode* node = stack[top--];
        printf("%d ", node->val);
        if (node->right) stack[++top] = node->right;
        if (node->left) stack[++top] = node->left;
    }
}

void iterativeInorder(TreeNode* root) {
    TreeNode* stack[100];
    int top = -1;
    TreeNode* curr = root;
    while (top != -1 || curr != NULL) {
        while (curr != NULL) {
            stack[++top] = curr;
            curr = curr->left;
        }
        curr = stack[top--];
        printf("%d ", curr->val);
        curr = curr->right;
    }
}

void iterativePostorder(TreeNode* root) {
    if (root == NULL) return;
    TreeNode* s1[100], *s2[100];
    int t1 = -1, t2 = -1;
    s1[++t1] = root;
    while (t1 != -1) {
        TreeNode* node = s1[t1--];
        s2[++t2] = node;
        if (node->left) s1[++t1] = node->left;
        if (node->right) s1[++t1] = node->right;
    }
    while (t2 != -1) {
        printf("%d ", s2[t2--]->val);
    }
}

// Mirror Image
void mirror(TreeNode* root) {
    if (root == NULL) return;
    TreeNode* temp = root->left;
    root->left = root->right;
    root->right = temp;
    mirror(root->left);
    mirror(root->right);
}

// Count Nodes
int countTotal(TreeNode* root) {
    if (root == NULL) return 0;
    return 1 + countTotal(root->left) + countTotal(root->right);
}

int countLeaf(TreeNode* root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    return countLeaf(root->left) + countLeaf(root->right);
}

int countInternal(TreeNode* root) {
    if (root == NULL || (root->left == NULL && root->right == NULL)) return 0;
    return 1 + countInternal(root->left) + countInternal(root->right);
}

// Menu
int main() {
    TreeNode* root = NULL;
    int choice, val;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Insert\n2. Delete\n3. Recursive Inorder\n4. Recursive Preorder\n5. Recursive Postorder\n");
        printf("6. Iterative Inorder\n7. Iterative Preorder\n8. Iterative Postorder\n");
        printf("9. Mirror Tree\n10. Count Total Nodes\n11. Count Leaf Nodes\n12. Count Internal Nodes\n0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter value: "); scanf("%d", &val);
                root = insert(root, val); break;
            case 2:
                printf("Enter value to delete: "); scanf("%d", &val);
                root = delete(root, val); break;
            case 3:
                printf("Inorder: "); inorder(root); break;
            case 4:
                printf("Preorder: "); preorder(root); break;
            case 5:
                printf("Postorder: "); postorder(root); break;
            case 6:
                printf("Iterative Inorder: "); iterativeInorder(root); break;
            case 7:
                printf("Iterative Preorder: "); iterativePreorder(root); break;
            case 8:
                printf("Iterative Postorder: "); iterativePostorder(root); break;
            case 9:
                mirror(root); printf("Tree Mirrored.\n"); break;
            case 10:
                printf("Total nodes: %d\n", countTotal(root)); break;
            case 11:
                printf("Leaf nodes: %d\n", countLeaf(root)); break;
            case 12:
                printf("Internal nodes: %d\n", countInternal(root)); break;
            case 0:
                printf("Exiting...\n"); break;
            default:
                printf("Invalid choice!\n");
        }
    } while(choice != 0);

    return 0;
}
