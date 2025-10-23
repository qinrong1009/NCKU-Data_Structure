#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u;      // 存放堆的數組
    int v;    // 最大容量
    int weight;        // 當前大小
} Edge;

typedef struct {
    Edge *array;     
    int capacity;    // 最大容量
    int size;        // 當前大小
} MinHeap;

Edge createEdge(int u, int v, int weight){
    Edge newone;
    newone.u = u;
    newone.v = v;
    newone.weight = weight;
    return newone;
}

// 建立最小堆
MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->capacity = capacity;
    heap->size = 0;
    heap->array = (Edge*)malloc(capacity * sizeof(Edge));
    return heap;
}

// 交換兩個節點的值
void swap(Edge* a, Edge* b) {
    Edge temp = *a;
    *a = *b;
    *b = temp;
}

// 返回父節點的索引
int parent(int i) {
    return (i - 1) / 2;
}

// 返回左子節點的索引
int left(int i) {
    return 2 * i + 1;
}

// 返回右子節點的索引
int right(int i) {
    return 2 * i + 2;
}

// 向堆中插入新元素
void insert(MinHeap* heap, Edge key) {
    if (heap->size == heap->capacity) {
        printf("Heap is full!%d\n", heap->capacity);
        return;
    }
    // 將新元素放在堆的末尾
    int i = heap->size;
    heap->array[i] = key;
    heap->size++;

    // 向上調整（上浮）元素
    while (i != 0 && heap->array[parent(i)].weight > heap->array[i].weight) {
        swap(&heap->array[i], &heap->array[parent(i)]);
        i = parent(i);
    }
}

int find(MinHeap* heap, Edge key){
    for(int i = 0; i < heap->size;i++){
        if(heap->array[i].weight == key.weight){return i;}
    }
    return -1;
}

// 打印堆的內容
void printHeap(MinHeap* heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d->%d : %d\n", heap->array[i].u, heap->array[i].v, heap->array[i].weight);
    }
}

void delete(MinHeap* heap, Edge key){
    int index = find(heap, key);
    if(index == -1){return;}
    swap(&heap->array[heap->size - 1],&heap->array[index]);
    heap->size -= 1;
    int currentIndex = index;
    while (currentIndex != 0 && heap->array[parent(currentIndex)].weight > heap->array[currentIndex].weight) {
        swap(&heap->array[currentIndex], &heap->array[parent(currentIndex)]);
        currentIndex = parent(currentIndex);
    }
    while (currentIndex < heap->size) {
        int leftIndex = left(currentIndex);
        int rightIndex = right(currentIndex);
        int smallest = currentIndex;

        //  確定左子節點是否存在且是否小於當前元素
        if (leftIndex < heap->size && heap->array[leftIndex].weight < heap->array[smallest].weight) {
            smallest = leftIndex;
        }
        // 確定右子節點是否存在且是否小於當前元素
        if (rightIndex < heap->size && heap->array[rightIndex].weight < heap->array[smallest].weight) {
            smallest = rightIndex;
        }

        // 如果當前元素已經是最小的，就結束
        if (smallest == currentIndex) {
            break;
        }

        // 否則，交換並更新當前索引
        swap(&heap->array[currentIndex], &heap->array[smallest]);
        currentIndex = smallest; // 更新當前索引為最小的子節點
    }
    return;
}

Edge pop(MinHeap* heap){
    int index = 0;
    Edge root = heap->array[index];
    swap(&heap->array[heap->size - 1],&heap->array[index]);
    heap->size -= 1;
    int currentIndex = index;
    while (currentIndex != 0 && heap->array[parent(currentIndex)].weight > heap->array[currentIndex].weight) {
        swap(&heap->array[currentIndex], &heap->array[parent(currentIndex)]);
        currentIndex = parent(currentIndex);
    }
    while (currentIndex < heap->size) {
        int leftIndex = left(currentIndex);
        int rightIndex = right(currentIndex);
        int smallest = currentIndex;

        //  確定左子節點是否存在且是否小於當前元素
        if (leftIndex < heap->size && heap->array[leftIndex].weight < heap->array[smallest].weight) {
            smallest = leftIndex;
        }
        // 確定右子節點是否存在且是否小於當前元素
        if (rightIndex < heap->size && heap->array[rightIndex].weight < heap->array[smallest].weight) {
            smallest = rightIndex;
        }

        // 如果當前元素已經是最小的，就結束
        if (smallest == currentIndex) {
            break;
        }

        // 否則，交換並更新當前索引
        swap(&heap->array[currentIndex], &heap->array[smallest]);
        currentIndex = smallest; // 更新當前索引為最小的子節點
    }
    return root;
}
////////////////////////////////////////////////////

// 定義 Disjoint Set 結構
typedef struct {
    int *parent; // parent[i] 代表 i 的父節點
    int *size;   // size[i] 代表以 i 為根的樹的大小
    int n;       // 節點數量
    int *height;       // 樹的高度
} DisjointSet;

// 創建一個大小為 n 的 Disjoint Set
DisjointSet* createSet(int n) {
    DisjointSet* set = (DisjointSet*)malloc(sizeof(DisjointSet));
    set->n = n;
    set->parent = (int*)malloc(n * sizeof(int));
    set->size = (int*)malloc(n * sizeof(int));
    set->height = (int*)malloc(n * sizeof(int));

    // 初始化：每個節點的父節點指向-1，樹的大小為 1
    for (int i = 0; i < n; i++) {
        set->parent[i] = -1;
        set->size[i] = 1;
        set->height[i] = 1;
    }

    return set;
}

// 查找操作（不使用路徑壓縮）
int findSet(DisjointSet* set, int x) {
    while (set->parent[x] != -1) {
        x = set->parent[x];
    }
    return x;
}

// 合併操作，使用按大小合併
void unionSets(DisjointSet* set, int x, int y) {
    int rootX = findSet(set, x);
    int rootY = findSet(set, y);

    if (rootX != rootY) {

        // 合併矮樹到高樹下面（Height Rule）
        if (set->height[rootX] < set->height[rootY]) {
            set->parent[rootX] = rootY;  // 讓 rootX 的父節點指向 rootY
            if(set->height[rootX] + 1 > set->height[rootY]){
                set->height[rootY] += set->height[rootX];  // 更新新樹的大小
            }
        } else {
            set->parent[rootY] = rootX;  // 讓 rootY 的父節點指向 rootX
            if(set->height[rootY] + 1 > set->height[rootX]){
                set->height[rootX] += set->height[rootY];  // 更新新樹的大小
            }
        }
    }
}

int countSet(DisjointSet* set){
    int n = set->n;
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if(set->parent[i] == -1){
            count += 1;
        }
    }
    return count;
}

// 測試最小堆
int main() {
    MinHeap* heap = createMinHeap(100);
    Edge one = createEdge(0,1,10);
    Edge two = createEdge(0,2,6);
    Edge three = createEdge(0,3,5);
    Edge four = createEdge(1,3,15);
    Edge five = createEdge(2,3,4);

    insert(heap, one);
    insert(heap, two);
    insert(heap, three);
    insert(heap, four);
    insert(heap, five);
    printHeap(heap);

    DisjointSet *set = createSet(4);
    Edge correct[100];
    int count = 0;
    printf("count:%d\n\n",countSet(set));
    while (countSet(set) != 1 && heap->size != 0)
    {
        Edge minone = pop(heap);
        printf("%d->%d : %d\n", minone.u, minone.v,minone.weight);
        printf("%d %d\n",findSet(set, minone.u) ,findSet(set, minone.v));
        if(findSet(set, minone.u) != findSet(set, minone.v)){
            correct[count] = minone;
            unionSets(set, minone.u, minone.v);
            count += 1;
        }
    }
    if(countSet(set) == 1){
        printf("succed! %d\n",count);
        for (int i = 0; i < count; i++)
        {
            printf("%d->%d : %d\n", correct[i].u, correct[i].v,correct[i].weight);
        }
    }else{
        printf("NOOOO");
    }

    return 0;
}
