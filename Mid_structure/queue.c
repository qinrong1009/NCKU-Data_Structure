#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int MAX_SIZE = 100;   // 設定隊列的最大大小
int arr[MAX_SIZE];  // 队列存储元素的数组
int front;          // 队列前端的指针
int rear;           // 队列尾部的指针


// 建立隊列（初始化）
void init() {
    front = -1;  // 初始化隊列，前端指標為 -1
    rear = -1;   // 初始化隊列，尾端指標為 -1
}

// 檢查隊列是否滿
bool isFull() {
    return rear + 1 >= MAX_SIZE;  // 判斷滿了
}

// 檢查隊列是否空
bool isEmpty() {
    return front == rear;  // 如果 front 為 -1 表示隊列空
}

// 新增元素到隊列（隊尾加入）
void add(int value) {
    if (isFull()) {
        return;
    }
    rear += 1; // 更新 rear，注意循環隊列
    arr[rear] = value;  // 將值加入隊列尾部
}

// 刪除隊列的前端元素（隊首刪除）
int delete() {
    if (isEmpty()) {
        return -1;  // 如果隊列為空，返回 -1
    }
    front += 1;
    int deletedValue = arr[front];  // 取得 front 位置的元素
    return deletedValue;
}

// 取得隊列的前端元素（不刪除）
int frontElement() {
    if (isEmpty()) {
        printf("Queue is empty!\n");
        return -1;  // 如果隊列為空，返回 -1
    }
    return arr[front + 1];  // 返回 front 位置的元素
}

// 測試隊列功能
int main() {
    init();  // 創建隊列

    // 測試新增元素
    add(10);
    add(20);
    add(30);

    // 顯示隊列前端元素
    printf("Front element is %d\n", frontElement());

    // 測試刪除元素
    delete();
    delete();

    // 顯示隊列前端元素
    printf("Front element after deletions is %d\n", frontElement());

    // 測試隊列空情況
    delete();  // 這會使隊列變空
    delete();  // 嘗試再次刪除

    return 0;
}
