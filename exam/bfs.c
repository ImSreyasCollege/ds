#include <stdio.h>
#include <stdbool.h>

int mat[50][50], n, vis[50], front= -1, back= -1;

bool isVis(int val){
    for(int i = 0; i <=back; i++){
        if(val == vis[i]) return true;
    }
    return false;
}

void bfs(int start){
    if(front == -1 && back == -1){
        front = 0;
        vis[++back] = start;
    }
    for(int j = 0; j < n; j++){
        if(start != j && mat[start][j] == 1 && !isVis(j)){
            vis[++back] = j;
        }
    }
    if(back == n) return;
    ++front;
    bfs(vis[front]);
}

void main(){
    int start;
    printf("enter the no.of vertex : ");
    scanf("%d", &n);
    printf("Enter the adjacency matrix : \n");
    for(int i = 0; i< n; i++){
        for(int j=0; j< n; j++){
            scanf("%d", &mat[i][j]);
        }
    }
    printf("enter the starting vertex : ");
    scanf("%d", &start);
    bfs(start);

    printf("BFS : ");
    for(int i=0; i<n; i++){
        printf(" %d ", vis[i]);
    }
}