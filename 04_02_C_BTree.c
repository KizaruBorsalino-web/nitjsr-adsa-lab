#include <stdio.h>
#include <stdlib.h>
#define T 3   // minimum degree

typedef struct BTreeNode {
    int keys[2*T-1], n;
    struct BTreeNode* C[2*T];
    int leaf;
} BTreeNode;

BTreeNode* createNode(int leaf){
    BTreeNode* n=malloc(sizeof(BTreeNode));
    n->leaf=leaf; n->n=0;
    for(int i=0;i<2*T;i++) n->C[i]=NULL;
    return n;
}
BTreeNode* root=NULL;

void traverse(BTreeNode* r){
    int i; for(i=0;i<r->n;i++){ if(!r->leaf) traverse(r->C[i]); printf("%d ",r->keys[i]); }
    if(!r->leaf) traverse(r->C[i]);
}
BTreeNode* search(BTreeNode* r,int k){
    int i=0; while(i<r->n && k>r->keys[i]) i++;
    if(i<r->n && r->keys[i]==k) return r;
    return r->leaf? NULL: search(r->C[i],k);
}
void splitChild(BTreeNode* x,int i,BTreeNode* y){
    BTreeNode* z=createNode(y->leaf); z->n=T-1;
    for(int j=0;j<T-1;j++) z->keys[j]=y->keys[j+T];
    if(!y->leaf) for(int j=0;j<T;j++) z->C[j]=y->C[j+T];
    y->n=T-1;
    for(int j=x->n;j>=i+1;j--) x->C[j+1]=x->C[j];
    x->C[i+1]=z;
    for(int j=x->n-1;j>=i;j--) x->keys[j+1]=x->keys[j];
    x->keys[i]=y->keys[T-1]; x->n++;
}
void insertNonFull(BTreeNode* x,int k){
    int i=x->n-1;
    if(x->leaf){
        while(i>=0 && k<x->keys[i]){ x->keys[i+1]=x->keys[i]; i--; }
        x->keys[i+1]=k; x->n++;
    } else {
        while(i>=0 && k<x->keys[i]) i--;
        i++;
        if(x->C[i]->n==2*T-1){ splitChild(x,i,x->C[i]); if(k>x->keys[i]) i++; }
        insertNonFull(x->C[i],k);
    }
}
void insertItem(int k){
    if(!root){ root=createNode(1); root->keys[0]=k; root->n=1; }
    else{
        if(root->n==2*T-1){
            BTreeNode* s=createNode(0); s->C[0]=root; splitChild(s,0,root);
            int i=0; if(s->keys[0]<k) i++; insertNonFull(s->C[i],k);
            root=s;
        } else insertNonFull(root,k);
    }
}

int main(){
    int a[]={10,20,5,6,12,30,7,17};
    for(int i=0;i<8;i++) insertItem(a[i]);
    printf("B-Tree traversal: "); traverse(root); printf("\n");
    printf("Search 12 -> %s\n", search(root,12)?"Found":"Not Found");
}
