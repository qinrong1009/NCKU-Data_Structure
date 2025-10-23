#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *array;      // 存放堆的數組
    int capacity;    // 最大容量
    int size;        // 當前大小
} MinHeap;

// 建立最小堆
MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->capacity = capacity;
    heap->size = 0;
    heap->array = (int*)malloc(capacity * sizeof(int));
    return heap;
}

// 交換兩個節點的值
void swap(int* a, int* b) {
    int temp = *a;
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
void insert(MinHeap* heap, int key) {
    if (heap->size == heap->capacity) {
        printf("Heap is full!\n");
        return;
    }
    // 將新元素放在堆的末尾
    int i = heap->size;
    heap->array[i] = key;
    heap->size++;

    // 向上調整（上浮）元素
    while (i != 0 && heap->array[parent(i)] > heap->array[i]) {
        swap(&heap->array[i], &heap->array[parent(i)]);
        i = parent(i);
    }
}

int find(MinHeap* heap, int key){
    for(int i = 0; i < heap->size;i++){
        if(heap->array[i] == key){return i;}
    }
    return -1;
}

void delete(MinHeap* heap, int key){
    int index = find(heap, key);
    if(index == -1){return;}
    swap(&heap->array[heap->size - 1],&heap->array[index]);
    heap->size -= 1;
    int currentIndex = index;
    while (currentIndex != 0 && heap->array[parent(currentIndex)] > heap->array[currentIndex]) {
        swap(&heap->array[currentIndex], &heap->array[parent(currentIndex)]);
        currentIndex = parent(currentIndex);
    }
    while (currentIndex < heap->size) {
        int leftIndex = left(currentIndex);
        int rightIndex = right(currentIndex);
        int smallest = currentIndex;

        //  確定左子節點是否存在且是否小於當前元素
        if (leftIndex < heap->size && heap->array[leftIndex] < heap->array[smallest]) {
            smallest = leftIndex;
        }
        // 確定右子節點是否存在且是否小於當前元素
        if (rightIndex < heap->size && heap->array[rightIndex] < heap->array[smallest]) {
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

// 打印堆的內容
void printHeap(MinHeap* heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->array[i]);
    }
    printf("\n");
}

// 測試最小堆
int main() {
    MinHeap* heap = createMinHeap(100);
    char str[100];
    int key;
    while(1){
        if(scanf("%s %d",str, &key) == EOF){break;}
        if(str[0] == 'i'){insert(heap, key);}
        else{delete(heap, key);}
    }
    printHeap(heap);
    return 0;
}
