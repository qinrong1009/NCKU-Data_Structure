#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_SIZE = 100;
int array[MAX_SIZE];
int capacity = MAX_SIZE;
int size = 0;


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
void insert(int key) {
    if (size == capacity) {
        printf("Heap is full!\n");
        return;
    }
    // 將新元素放在堆的末尾
    int i = size;
    array[i] = key;
    size++;

    // 向上調整（上浮）元素
    while (i != 0 && array[parent(i)] > array[i]) {
        swap(&array[i], &array[parent(i)]);
        i = parent(i);
    }
}

int find(int key){
    for(int i = 0; i < size;i++){
        if(array[i] == key){return i;}
    }
    return -1;
}

void delete(int key){
    int index = find(key);
    if(index == -1){return;}
    swap(&array[size - 1],&array[index]);
    size -= 1;
    int currentIndex = index;
    while (currentIndex != 0 && array[parent(currentIndex)] > array[currentIndex]) {
        swap(&array[currentIndex], &array[parent(currentIndex)]);
        currentIndex = parent(currentIndex);
    }
    while (currentIndex < size) {
        int leftIndex = left(currentIndex);
        int rightIndex = right(currentIndex);
        int smallest = currentIndex;

        //  確定左子節點是否存在且是否小於當前元素
        if (leftIndex < size && array[leftIndex] < array[smallest]) {
            smallest = leftIndex;
        }
        // 確定右子節點是否存在且是否小於當前元素
        if (rightIndex < size && array[rightIndex] < array[smallest]) {
            smallest = rightIndex;
        }

        // 如果當前元素已經是最小的，就結束
        if (smallest == currentIndex) {
            break;
        }

        // 否則，交換並更新當前索引
        swap(&array[currentIndex], &array[smallest]);
        currentIndex = smallest; // 更新當前索引為最小的子節點
    }
    return;
}

// 打印堆的內容
void printHeap() {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// 測試最小堆
int main() {
    char str[100];
    int key;
    while(1){
        if(scanf("%s %d",str, &key) == EOF){break;}
        if(str[0] == 'i'){insert(key);}//字源可以用== 字串要用strcmp(a,b) == 0是一樣
        else{delete(key);}
    }
    printHeap();
    return 0;
}
