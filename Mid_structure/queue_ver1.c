#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 5  // 設定隊列的最大大小

typedef struct {
    int arr[MAX_SIZE];  // 队列存储元素的数组
    int front;          // 队列前端的指针
    int rear;           // 队列尾部的指针
} Queue;


// 建立隊列（初始化）
Queue* create() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));  // 分配記憶體
    queue->front = -1;  // 初始化隊列，前端指標為 -1
    queue->rear = -1;   // 初始化隊列，尾端指標為 -1
    return queue;
}

// 檢查隊列是否滿
bool isFull(Queue* queue) {
    return queue->rear + 1 >= MAX_SIZE;  // 判斷滿了
}

// 檢查隊列是否空
bool isEmpty(Queue* queue) {
    return queue->front == queue->rear;  // 如果 front 為 -1 表示隊列空
}

// 新增元素到隊列（隊尾加入）
void add(Queue* queue, int value) {
    if (isFull(queue)) {
        return;
    }
    queue->rear += 1; // 更新 rear，注意循環隊列
    queue->arr[queue->rear] = value;  // 將值加入隊列尾部
}

// 刪除隊列的前端元素（隊首刪除）
int delete(Queue* queue) {
    if (isEmpty(queue)) {
        return -1;  // 如果隊列為空，返回 -1
    }
    queue->front += 1;
    int deletedValue = queue->arr[queue->front];  // 取得 front 位置的元素
    return deletedValue;
}

// 取得隊列的前端元素（不刪除）
int frontElement(Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty!\n");
        return -1;  // 如果隊列為空，返回 -1
    }
    return queue->arr[queue->front + 1];  // 返回 front 位置的元素
}

// 測試隊列功能
int main() {
    Queue* queue = create();  // 創建隊列

    // 測試新增元素
    add(queue, 10);
    add(queue, 20);
    add(queue, 30);

    // 顯示隊列前端元素
    printf("Front element is %d\n", frontElement(queue));

    // 測試刪除元素
    delete(queue);
    delete(queue);

    // 顯示隊列前端元素
    printf("Front element after deletions is %d\n", frontElement(queue));

    // 測試隊列空情況
    delete(queue);  // 這會使隊列變空
    delete(queue);  // 嘗試再次刪除

    // 釋放記憶體
    free(queue);
    
    return 0;
}
