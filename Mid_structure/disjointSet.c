#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_SIZE = 105;
int set[MAX_SIZE];

int findRoot(int x){
    if(set[x] == x)return x;
    set[x] = findRoot(set[x]);//collapse
    return set[x];
}

void uni(int x,int y){
    int xRoot = findRoot(x);
    int yRoot = findRoot(y);
    set[xRoot] = yRoot;
}

int main(){
    for (int i = 0; i < MAX_SIZE; i++)
    {
        set[i] = i;
    }
    //操作
}