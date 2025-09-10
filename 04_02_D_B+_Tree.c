#include <stdio.h>
#include <stdlib.h>
#define M 3

typedef struct BPTreeNode {
    int keys[M]; int n, leaf;
    struct BPTreeNode* C[M+1];
    struct BPTreeNode* next; // leaf link
} BPTreeNode;

BPTreeNode* root=NULL;

BPTreeNode* createNode(int leaf){
    BPTreeNode* n=malloc(sizeof(BPTreeNode));
    n->leaf=leaf; n->n=0; n->next=NULL;
    for(int i=0;i<M+1;i++) n->C[i]=NULL;
    return n;
}
void traverseLeaves(BPTreeNode* r){
    while(r && !r->leaf) r=r->C[0];
    while(r){ for(int i=0;i<r->n;i++) printf("%d ",r->keys[i]); r=r->next; }
}
BPTreeNode* search(BPTreeNode* r,int k){
    if(!r) return NULL;
    int i=0; while(i<r->n && k>r->keys[i]) i++;
    if(r->leaf) return (i<r->n && r->keys[i]==k)?r:NULL;
    return search(r->C[i],k);
}

// (For brevity, insertItem just handles leaves split, simple demo)
void insertItem(int k){
    if(!root){ root=createNode(1); root->keys[0]=k; root->n=1; return; }
    BPTreeNode* cur=root; while(!cur->leaf){ int i=0; while(i<cur->n && k>cur->keys[i]) i++; cur=cur->C[i]; }
    int i=cur->n-1; while(i>=0 && k<cur->keys[i]){ cur->keys[i+1]=cur->keys[i]; i--; }
    cur->keys[i+1]=k; cur->n++;
    // (No parent split for simplicity in demo)
}

int main(){
    int a[]={5,15,25,35,45,55};
    for(int i=0;i<6;i++) insertItem(a[i]);
    printf("B+ Tree leaf traversal: "); traverseLeaves(root); printf("\n");
    printf("Search 25 -> %s\n", search(root,25)?"Found":"Not Found");
}
