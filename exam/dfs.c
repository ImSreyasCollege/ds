#include <stdio.h>
#include <stdbool.h>

int mat[50][50];
int n;
int vis[20];
int count=0;

bool isVis(int val){
    for(int i=0; i< count; i++){
        if(val == vis[i]){
            return true;
        }
    }
    return false;
}

void dfs(int i){
    vis[count++] = i;
    for(int j=0; j<n; j++){
        if(i != j && mat[i][j] == 1 && !isVis(j)){
            dfs(j);
        }
    }
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
    dfs(start);

    printf("DFS : ");
    for(int i=0; i<n; i++){
        printf(" %d ", vis[i]);
    }
}