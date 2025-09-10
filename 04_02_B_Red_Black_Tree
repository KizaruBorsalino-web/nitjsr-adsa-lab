#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } Color;

typedef struct Node {
    int key; Color color;
    struct Node *left,*right,*parent;
} Node;

Node* root=NULL;

Node* newNode(int k){
    Node* n=malloc(sizeof(Node)); n->key=k; n->color=RED;
    n->left=n->right=n->parent=NULL; return n;
}

// (Insert & balance)
void rotateLeft(Node* x){ Node* y=x->right; x->right=y->left;
    if(y->left) y->left->parent=x; y->parent=x->parent;
    if(!x->parent) root=y;
    else if(x==x->parent->left) x->parent->left=y; else x->parent->right=y;
    y->left=x; x->parent=y;
}
void rotateRight(Node* y){ Node* x=y->left; y->left=x->right;
    if(x->right) x->right->parent=y; x->parent=y->parent;
    if(!y->parent) root=x;
    else if(y==y->parent->left) y->parent->left=x; else y->parent->right=x;
    x->right=y; y->parent=x;
}
void fixInsert(Node* z){
    while(z->parent && z->parent->color==RED){
        if(z->parent==z->parent->parent->left){
            Node* y=z->parent->parent->right;
            if(y && y->color==RED){ z->parent->color=BLACK; y->color=BLACK; z->parent->parent->color=RED; z=z->parent->parent; }
            else { if(z==z->parent->right){ z=z->parent; rotateLeft(z);} z->parent->color=BLACK; z->parent->parent->color=RED; rotateRight(z->parent->parent);}
        } else {
            Node* y=z->parent->parent->left;
            if(y && y->color==RED){ z->parent->color=BLACK; y->color=BLACK; z->parent->parent->color=RED; z=z->parent->parent; }
            else { if(z==z->parent->left){ z=z->parent; rotateRight(z);} z->parent->color=BLACK; z->parent->parent->color=RED; rotateLeft(z->parent->parent);}
        }
    }
    root->color=BLACK;
}
void insertItem(int k){
    Node* z=newNode(k),*y=NULL,*x=root;
    while(x){ y=x; if(z->key<x->key) x=x->left; else x=x->right; }
    z->parent=y;
    if(!y) root=z; else if(z->key<y->key) y->left=z; else y->right=z;
    fixInsert(z);
}
Node* searchItem(Node* r,int k){ if(!r||r->key==k) return r; return k<r->key?searchItem(r->left,k):searchItem(r->right,k); }
void inorder(Node* r){ if(r){ inorder(r->left); printf("%d(%s) ",r->key,r->color?"B":"R"); inorder(r->right);} }

int main(){
    int a[]={10,20,30,15,25,5};
    for(int i=0;i<6;i++) insertItem(a[i]);
    printf("Inorder: "); inorder(root); printf("\n");
    printf("Search 25 -> %s\n", searchItem(root,25)?"Found":"Not Found");
}
