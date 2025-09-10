#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *left, *right;
} Node;

Node* newNode(int k) {
    Node* n = malloc(sizeof(Node));
    n->key = k; n->left = n->right = NULL;
    return n;
}

// Simple stack for nodes
Node* stack[100]; int top = -1;
void push(Node* n){ stack[++top] = n; }
Node* pop(){ return stack[top--]; }
int empty(){ return top == -1; }

void preorder(Node* root) {
    if (!root) return;
    push(root);
    while (!empty()) {
        Node* cur = pop();
        printf("%d ", cur->key);
        if (cur->right) push(cur->right);
        if (cur->left) push(cur->left);
    }
}

int main() {
    Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);

    printf("Preorder Traversal: ");
    preorder(root);
    return 0;
}
