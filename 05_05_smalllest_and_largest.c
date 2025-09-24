#include <stdio.h>
#include <string.h>

#define V 6
int graph[V][V];
int visited[V], stack[V], top;
int minCycle=1e9, maxCycle=-1;

void DFS(int u, int start) {
    visited[u]=1; stack[top++]=u;
    for(int v=0; v<V; v++) if(graph[u][v]) {
        if(!visited[v]) DFS(v,start);
        else {
            for(int i=0;i<top;i++) if(stack[i]==v) {
                int len=top-i; // cycle length
                if(len>1) {
                    if(len<minCycle) minCycle=len;
                    if(len>maxCycle) maxCycle=len;
                }
            }
        }
    }
    visited[u]=0; top--; // backtrack
}

void findCycles() {
    minCycle=1e9; maxCycle=-1;
    memset(visited,0,sizeof(visited)); top=0;
    for(int i=0;i<V;i++) DFS(i,i);
    if(maxCycle==-1) printf("No cycles found\n");
    else printf("Smallest cycle: %d, Largest cycle: %d\n", minCycle, maxCycle);
}

int main() {
    // Example graph (directed)
    int g[V][V]={
        {0,1,0,0,0,0},
        {0,0,1,0,0,0},
        {0,0,0,1,0,0},
        {1,0,0,0,1,0},
        {0,0,0,0,0,1},
        {0,0,1,0,0,0}
    };
    memcpy(graph,g,sizeof(g));
    findCycles();
    return 0;
}
