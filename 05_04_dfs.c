#include <stdio.h>
#include <string.h>

#define V 6
int graph[V][V];   // adjacency matrix
int color[V], d[V], f[V], time=0;

void DFSVisit(int u) {
    color[u]=1; d[u]=++time;
    for(int v=0; v<V; v++) if(graph[u][v]) {
        if(color[v]==0) { 
            printf("Tree Edge: %d -> %d\n", u,v);
            DFSVisit(v);
        }
        else if(color[v]==1) printf("Back Edge: %d -> %d\n", u,v);
        else if(d[u]<d[v])   printf("Forward Edge: %d -> %d\n", u,v);
        else                 printf("Cross Edge: %d -> %d\n", u,v);
    }
    color[u]=2; f[u]=++time;
}

void DFS() {
    memset(color,0,sizeof(color));
    time=0;
    for(int u=0; u<V; u++) if(color[u]==0) DFSVisit(u);
}

int main() {
    // Example graph
    int g[V][V]={
        {0,1,1,0,0,0},
        {0,0,0,1,0,0},
        {0,0,0,1,1,0},
        {0,0,0,0,0,1},
        {0,0,0,0,0,1},
        {0,0,0,0,0,0}
    };
    memcpy(graph,g,sizeof(g));
    DFS();
    return 0;
}
