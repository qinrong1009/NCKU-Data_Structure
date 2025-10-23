#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 定義堆疊結構體
const int MAX_SIZE = 5;  // 設定堆疊的最大大小

int arr[MAX_SIZE];
int top = -1;

// 檢查堆疊是否滿
bool isFull() {
    return top == MAX_SIZE - 1;
}

// 檢查堆疊是否空
bool isEmpty() {
    return top == -1;
}

// 取得堆疊頂端的元素
int getTop() {
    if (isEmpty()) {
        return -1;  // 堆疊空時返回 -1
    }
    return arr[top];
}

// 推入元素到堆疊
void push( int value) {
    if (isFull()) {
        return;
    }
    arr[++top] = value;  // 先將 top 增加，再賦值
}

// 彈出堆疊頂端的元素
int pop() {
    if (isEmpty()) {
        return -1;  // 堆疊空時返回 -1
    }
    int poppedValue = arr[top--];  // 先取出值，再將 top 減少
    return poppedValue;
}

// 測試堆疊功能
int main() {

    // 測試推入元素
    push(10);
    push(20);
    push(30);

    // 顯示堆疊頂端元素
    printf("Top element is %d\n", getTop());

    // 測試彈出元素
    pop();
    pop();

    // 顯示堆疊頂端元素
    printf("Top element after popping is %d\n", getTop());

    // 測試空堆疊
    pop();  // 這會使堆疊變空
    pop();  // 嘗試再次彈出
    
    return 0;
}
