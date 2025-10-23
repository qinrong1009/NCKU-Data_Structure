#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int *queue;
    int *visited;
    int *order;
    int doneNum;
    int **adjArray;
}BFS;

BFS* create(int vurNum, int* array){
    BFS *newBFS = (BFS *)malloc(sizeof(BFS));
    newBFS->queue = (int*)malloc(vurNum*sizeof(int));
    newBFS->visited = (int*)malloc(vurNum*sizeof(int));
    newBFS->order = (int*)malloc(vurNum*sizeof(int));
    newBFS->doneNum = 0;
    newBFS->adjArray = (int **)malloc(vurNum * sizeof(int *));
    for (int i = 0; i < vurNum; i++) {
        newBFS->adjArray[i] = (int *)malloc(vurNum * sizeof(int));
        for (int j = 0; j < vurNum; j++) {
            newBFS->adjArray[i][j] = array[i*100 + j];  // 初始化
        }
    }
    for (int i = 0; i < vurNum; i++)
    {
        newBFS->queue[i] = -1;
        newBFS->visited[i] = 0;
        newBFS->order[i] = -1;
    }
    return newBFS;
}

void addQueue(BFS *bfs, int index){
    for(int i = 0; i < 100;i++){
        if(bfs->queue[i] == -1){
            bfs->queue[i] = index;
            return;
        }
    }
    return;
}

void removeFirstQueue(BFS *bfs){
    for(int i = 0; i < 100;i++){
        if(bfs->queue[i] == -1){
            return;
        }
        bfs->queue[i] = bfs->queue[i+1];
    }
    return;
}

void process(BFS* bfs,int vurIndex,int vurNum){
    if(vurIndex == 0){
        bfs->visited[0] = 1;
        bfs->order[0] = 0;
        bfs->doneNum += 1;
    }else{
        removeFirstQueue(bfs);
    }
    for (int i = 0; i < vurNum; i++)
    {
        if(bfs->adjArray[vurIndex][i] == 1 && bfs->visited[i] == 0){
            bfs->visited[i] = 1;
            bfs->order[bfs->doneNum] = i;
            bfs->doneNum += 1;
            addQueue(bfs, i);
        }
    }
}
int main(int argc, char *argv[]){
    int vurNum;
    int n = scanf("%d",&vurNum);
    int array[100][100] = {0};
    int array2[100] = {0};
    
    int temp;
    for(int i = 0;i < vurNum;i++){
        for(int j = 0;j < vurNum;j++){
            n = scanf("%d",&temp);
            array[i][j] = temp;
        }
    }

    BFS *bfs = create(vurNum, array);

    process(bfs, 0, vurNum);
    while(bfs->queue[0] != -1){
        process(bfs, bfs->queue[0], vurNum);
    }


    for(int i = 0;i < vurNum;i++){
        if(bfs->order[i] == -1){break;}
        printf("%d ",bfs->order[i]+1); 
    }
}