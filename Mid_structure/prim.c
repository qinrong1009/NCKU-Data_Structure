#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int MAX_SIZE = 105;

typedef struct {
    int u;
    int v;
    int weight;
} Edge;

typedef struct {
    Edge *array;
    int capacity;
    int size;
} MinHeap;

Edge createEdge(int u, int v, int weight) {
    Edge newone;
    newone.u = u;
    newone.v = v;
    newone.weight = weight;
    return newone;
}

MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->capacity = capacity;
    heap->size = 0;
    heap->array = (Edge*)malloc(capacity * sizeof(Edge));
    return heap;
}

void swap(Edge* a, Edge* b) {
    Edge temp = *a;
    *a = *b;
    *b = temp;
}

int parent(int i) {
    return (i - 1) / 2;
}

int left(int i) {
    return 2 * i + 1;
}

int right(int i) {
    return 2 * i + 2;
}

void insert(MinHeap* heap, Edge key) {
    if (heap->size == heap->capacity) {
        printf("Heap is full!\n");
        return;
    }

    int i = heap->size;
    heap->array[i] = key;
    heap->size++;

    while (i != 0 && heap->array[parent(i)].weight > heap->array[i].weight) {
        swap(&heap->array[i], &heap->array[parent(i)]);
        i = parent(i);
    }
}

Edge pop(MinHeap* heap) {
    if (heap->size == 0) {
        return createEdge(-1, -1, -1); // 空堆返回無效邊
    }

    Edge root = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;

    int currentIndex = 0;

    while (currentIndex < heap->size) {
        int leftIndex = left(currentIndex);
        int rightIndex = right(currentIndex);
        int smallest = currentIndex;

        if (leftIndex < heap->size && heap->array[leftIndex].weight < heap->array[smallest].weight) {
            smallest = leftIndex;
        }
        if (rightIndex < heap->size && heap->array[rightIndex].weight < heap->array[smallest].weight) {
            smallest = rightIndex;
        }

        if (smallest == currentIndex) {
            break;
        }

        swap(&heap->array[currentIndex], &heap->array[smallest]);
        currentIndex = smallest;
    }

    return root;
}

void printHeap(MinHeap* heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d->%d : %d\n", heap->array[i].u, heap->array[i].v, heap->array[i].weight);
    }
}

// Prim's Algorithm
void prim(int n, Edge edges[], int edgeCount) {
    MinHeap* heap = createMinHeap(edgeCount);
    bool visited[MAX_SIZE] = {false};
    Edge mst[MAX_SIZE];
    int mstSize = 0;

    // Start from node 0
    visited[0] = true;

    // Push all edges connected to node 0
    for (int i = 0; i < edgeCount; i++) {
        if (edges[i].u == 0 || edges[i].v == 0) {
            insert(heap, edges[i]);
        }
    }

    while (mstSize < n - 1 && heap->size > 0) {
        Edge minEdge = pop(heap);

        // Check if this edge connects to an unvisited node
        if (visited[minEdge.u] && visited[minEdge.v]) {
            continue; // Both nodes are already in the MST
        }

        // Add this edge to the MST
        mst[mstSize++] = minEdge;

        // Mark the new node as visited
        int newNode = visited[minEdge.u] ? minEdge.v : minEdge.u;
        visited[newNode] = true;

        // Push all edges connected to the new node
        for (int i = 0; i < edgeCount; i++) {
            if ((edges[i].u == newNode && !visited[edges[i].v]) || 
                (edges[i].v == newNode && !visited[edges[i].u])) {
                insert(heap, edges[i]);
            }
        }
    }

    // Print the MST
    if (mstSize == n - 1) {
        printf("MST found:\n");
        for (int i = 0; i < mstSize; i++) {
            printf("%d->%d : %d\n", mst[i].u, mst[i].v, mst[i].weight);
        }
    } else {
        printf("MST could not be found.\n");
    }
}

// Main Function
int main() {
    Edge edges[] = {
        createEdge(0, 1, 10),
        createEdge(0, 2, 6),
        createEdge(0, 3, 5),
        createEdge(1, 3, 15),
        createEdge(2, 3, 4)
    };

    int n = 4; // Number of nodes
    int edgeCount = sizeof(edges) / sizeof(edges[0]);

    prim(n, edges, edgeCount);

    return 0;
}
