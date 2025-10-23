#include <stdio.h> 
#include <stdlib.h>
#define MAX_NODES 25

int n;
int matrix[MAX_NODES][MAX_NODES];

int set[MAX_NODES];
int totalCost = 0;      // Storing the total cost of the minimum spanning tree
int mst[MAX_NODES][2];  // Store the edges of the minimum spanning tree. 
                            // If the i-th edge is (u, v), then mst[i-1][0] = u,mst[i-1][1] = v


typedef struct 
{
    int u;
    int v;
    int weight;
}Edge;

int findRoot(int x){
    if(set[x] == x){
        return x;
    }
    set[x] = findRoot(set[x]);
    return set[x];
}

void uni(int x, int y){
    int xRoot = findRoot(x);
    int yRoot = findRoot(y);
    set[xRoot] = yRoot;
}

int CountSet(){
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if(set[i] == i){count += 1;}
    }
    return count;
}

Edge createEdge(int u, int v, int w){
    Edge newone;
    newone.u = u;
    newone.v = v;
    newone.weight = w;
    return newone;
}

typedef struct 
{
    Edge* array;
    int capacity;
    int size;
}Minheap;

Minheap* createMinHeap(int capacity){
    Minheap* newone = (Minheap*)malloc(sizeof(Minheap));
    newone->capacity = capacity;
    newone->size = 0;
    newone->array = (Edge*)malloc(capacity * sizeof(Edge));
    return newone;
}

void swap(Edge *a,Edge* b){
    Edge temp = *a;
    *a = *b;
    *b = temp;
}

int parent(int i){
    return (i-1)/2;
}

int left(int i){
    return 2*i +1;
}

int right(int i){
    return 2*i+2;
}

void insert(Minheap* heap,Edge key){
    if(heap->size == heap->capacity){return;}
    int i = heap->size;
    heap->array[i] = key;
    heap->size++;
    // printf("%d %d %d\n",i,heap->array[parent(i)].weight,heap->array[i].weight);
    while(i != 0 && heap->array[parent(i)].weight > heap->array[i].weight){
        swap(&heap->array[parent(i)], &heap->array[i]);
        i = parent(i);
    }
}

Edge pop(Minheap* heap){
    Edge root = heap->array[0];
    swap(&heap->array[0], &heap->array[heap->size-1]);
    heap->size--;
    int currenIndex = 0;
    while (currenIndex < heap->size)
    {
        int leftIndex = left(currenIndex);
        int rightIndex = right(currenIndex);
        int smalledt = currenIndex;
        if(leftIndex < heap->size && heap->array[leftIndex].weight < heap->array[smalledt].weight){
            smalledt = leftIndex;
        }
        if(rightIndex < heap->size && heap->array[rightIndex].weight < heap->array[smalledt].weight){
            smalledt = rightIndex;
        }
        if (smalledt == currenIndex)
        {
            break;
        }
        swap(&heap->array[currenIndex], &heap->array[smalledt]);
        currenIndex = smalledt;
    }
    return root;
}

int main() {
    // Input
    int not = 0;
    not = scanf("%d", &n);  // Read the number of nodes
    
    // Read adjacency matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            not = scanf("%d", &matrix[i][j]);
        }
    }

    Minheap* heap = createMinHeap(25);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if(i == j || i > j || matrix[i][j]==0){
                continue;
            }
            Edge edge = createEdge(i, j, matrix[i][j]);
            insert(heap, edge);
        }
    }
    for (int i = 0; i < n; i++)
    {
        set[i] = i;
    }
    int count = 0;
    while(CountSet() != 1 && heap->size!=0){
        Edge minone = pop(heap);
        if(findRoot(minone.u) != findRoot(minone.v)){
            uni(minone.u, minone.v);
            totalCost += minone.weight;
            mst[count][0] = minone.u;
            mst[count][1] = minone.v;
            count++;
        }
    }
    

    // OutPut
    printf("%d", totalCost);
    for (int i = 0; i < n-1; i++) {
        printf(",(%d,%d)", mst[i][0], mst[i][1]);  
    }
    printf("\n");
    
    return 0;
}