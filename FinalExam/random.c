#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

int delete[100];
int deleteNum = 0;

// SMMH structure
typedef struct {
    int heap[MAX_SIZE];
    int size;
} SMMH;

// Initialize SMMH
void initialize(SMMH* smmh) {
    smmh->size = 0;
    memset(smmh->heap, 0, sizeof(smmh->heap)); 
}

// Swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Helper function to maintain SMMH property after insertion
void bubbleUp(SMMH* smmh, int index) {
    if (index % 2 == 1){
        if (smmh->heap[index-1] > smmh->heap[index]){
            swap(&smmh->heap[index], &smmh->heap[index-1]);
            index = index - 1; 
        }
    }
    

    int parent = index / 2;
    if (parent==1) return;

    if (index % 4 < 2) { //在gp的左邊
        if (smmh->heap[index] > smmh->heap[parent + 1]) {//跟gp的右子樹比
            swap(&smmh->heap[index], &smmh->heap[parent + 1]);
            bubbleUp(smmh, parent + 1);
        }
        if (smmh->heap[index] < smmh->heap[parent]) {
            swap(&smmh->heap[index], &smmh->heap[parent]);
            bubbleUp(smmh, parent);
        }
    } else { 
        if (smmh->heap[index] > smmh->heap[parent]) {
            swap(&smmh->heap[index], &smmh->heap[parent]);
            bubbleUp(smmh, parent);
        }
        if (smmh->heap[index] < smmh->heap[parent - 1]) {
            swap(&smmh->heap[index], &smmh->heap[parent - 1]);
            bubbleUp(smmh, parent - 1);
        }
    }
}

// Insert a key into SMMH
void insert(SMMH* smmh, int key) {//第一個元素index = 2 size = 1
    if (smmh->size >= MAX_SIZE - 1) return;
    
    smmh->size++;
    smmh->heap[smmh->size+1] = key;
    bubbleUp(smmh, smmh->size + 1);
}

//Write a function to delete the maximum and minimum values
void deleteMin(SMMH* smmh){
    int current = 2;
    int last = smmh->size + 1;
    if(last == 2){
        smmh->size--;
        return;
    }
    if(last != 2){
        swap(&smmh->heap[current], &smmh->heap[last]);
        smmh->size--;
    }
    int done = 0;
    while (!done && current <= last)//
    {
        if(smmh->heap[current] > smmh->heap[current+1] && (current+1) < smmh->size){
            swap(&smmh->heap[current], &smmh->heap[current+1]);
        }
        int gp = current / 2;//parnet
        int gc1 = 2*current;//佐子樹
        int gc2 = gc1 + 2;//又子樹
        // printf("gc1:%d gc2:%d last:%d\n", gc1, gc2, last);
        if(gc2 < last){
            if (smmh->heap[gc1] > smmh->heap[gc2])
            {
                gc1 = gc2; //讓gc1是最小的
            }
        }
        if(gc1 >= last){break;}
        if(smmh->heap[gc1] < smmh->heap[current]){
            swap(&smmh->heap[gc1], &smmh->heap[current]);
            current = gc1;
        }else{
            done = 1;
        }
    }
    // if(smmh->heap[current] > smmh->heap[current+1] && (current+1) < smmh->size){
    //     swap(&smmh->heap[current], &smmh->heap[current+1]);
    // }
    
}
void deleteMax(SMMH* smmh){
    int current = 3;
    int last = smmh->size + 1;
    if(last == 3){
        smmh->size--;
        return;
    }
    if(last != 3){
        swap(&smmh->heap[current], &smmh->heap[last]);
        smmh->size--;
    }
    int done = 0;
    while (!done && current <= last)//
    {
        if(smmh->heap[current] < smmh->heap[current-1]){
            swap(&smmh->heap[current], &smmh->heap[current-1]);
        }
        int gp = current / 2;//parnet
        int gc1 = 2*current + 1;//佐子樹
        int gc2 = gc1 - 2;//又子樹
        // printf("gc1:%d gc2:%d last:%d\n", gc1, gc2, last);
        if(gc2 < last){
            if (smmh->heap[gc1] < smmh->heap[gc2])
            {
                gc1 = gc2; //讓gc1是最小的
            }
        }
        if(gc1 >= last){break;}
        if(smmh->heap[gc1] > smmh->heap[current]){
            swap(&smmh->heap[gc1], &smmh->heap[current]);
            current = gc1;
        }else{
            done = 1;
        }
    }
    // if(smmh->heap[current] < smmh->heap[current-1]){
    //     swap(&smmh->heap[current], &smmh->heap[current-1]);
    // }
}

void printLevelOrder(SMMH* smmh) {
    if (smmh->size == 0 ) {
        printf("\n");
        return;
    }
    for (int i = 2; i <= smmh->size+1; i++) {
        for (int j = 0; i < deleteNum; i++)
        {
            if (delete[j] == smmh->heap[i])
            {
                continue;
            }
        }
        
        printf("%d", smmh->heap[i]);
        if (i < smmh->size + 1) {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    SMMH smmh;
    initialize(&smmh);
    
    char command[20];
    int key;

    while (1) {
        scanf("%s", command);
        if (strcmp(command, "exit") == 0) {
            printLevelOrder(&smmh);
            break;
        } else if (strcmp(command, "insert") == 0) {
            scanf("%d", &key);
            insert(&smmh, key);
        } else if (strcmp(command, "delete") == 0) {
            scanf("%d", &key);
            delete[deleteNum++] = key;
        }
    } return 0;
}