#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key, height;
    struct Node *left, *right;
} Node;

int h(Node* n){ return n? n->height:0; }
int max(int a,int b){ return a>b?a:b; }

Node* newNode(int k){
    Node* n = malloc(sizeof(Node));
    n->key=k; n->height=1; n->left=n->right=NULL;
    return n;
}
Node* rotateRight(Node* y){ Node* x=y->left; y->left=x->right; x->right=y;
    y->height=max(h(y->left),h(y->right))+1; x->height=max(h(x->left),h(x->right))+1; return x; }
Node* rotateLeft(Node* x){ Node* y=x->right; x->right=y->left; y->left=x;
    x->height=max(h(x->left),h(x->right))+1; y->height=max(h(y->left),h(y->right))+1; return y; }
int balance(Node* n){ return n? h(n->left)-h(n->right):0; }

Node* insertItem(Node* r,int k){
    if(!r) return newNode(k);
    if(k<r->key) r->left=insertItem(r->left,k);
    else if(k>r->key) r->right=insertItem(r->right,k);
    r->height=1+max(h(r->left),h(r->right));
    int b=balance(r);
    if(b>1 && k<r->left->key) return rotateRight(r);
    if(b<-1&& k>r->right->key) return rotateLeft(r);
    if(b>1 && k>r->left->key){ r->left=rotateLeft(r->left); return rotateRight(r);}
    if(b<-1&& k<r->right->key){ r->right=rotateRight(r->right); return rotateLeft(r);}
    return r;
}

Node* minNode(Node* n){ while(n->left) n=n->left; return n; }
Node* deleteItem(Node* r,int k){
    if(!r) return r;
    if(k<r->key) r->left=deleteItem(r->left,k);
    else if(k>r->key) r->right=deleteItem(r->right,k);
    else{
        if(!r->left||!r->right){ Node* t=r->left?r->left:r->right; free(r); return t; }
        Node* t=minNode(r->right); r->key=t->key; r->right=deleteItem(r->right,t->key);
    }
    r->height=1+max(h(r->left),h(r->right));
    int b=balance(r);
    if(b>1 && balance(r->left)>=0) return rotateRight(r);
    if(b>1 && balance(r->left)<0){ r->left=rotateLeft(r->left); return rotateRight(r);}
    if(b<-1&& balance(r->right)<=0) return rotateLeft(r);
    if(b<-1&& balance(r->right)>0){ r->right=rotateRight(r->right); return rotateLeft(r);}
    return r;
}

Node* searchItem(Node* r,int k){
    if(!r||r->key==k) return r;
    return k<r->key? searchItem(r->left,k):searchItem(r->right,k);
}
void inorder(Node* r){ if(r){ inorder(r->left); printf("%d ",r->key); inorder(r->right);} }
void deleteTree(Node* r){ if(r){ deleteTree(r->left); deleteTree(r->right); free(r);} }
Node* createTree(){ return NULL; }

int main(){
    Node* root=createTree();
    int a[]={10,20,30,40,50,25};
    for(int i=0;i<6;i++) root=insertItem(root,a[i]);
    printf("Inorder: "); inorder(root); printf("\n");
    root=deleteItem(root,40);
    printf("After delete 40: "); inorder(root); printf("\n");
    printf("Search 25 -> %s\n", searchItem(root,25)?"Found":"Not Found");
    deleteTree(root);
}
