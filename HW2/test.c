#include <stdio.h>
#include <stdlib.h>

// 節點結構
typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
} Node;

// 建立一個新節點
Node* createNode(int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->left = newNode;
    newNode->right = newNode;
    return newNode;
}

// 將兩個排序的雙向循環列表合併為一個排序的
Node* mergeCircularLists(Node* list1, Node* list2) {
    if (!list1) return list2;
    if (!list2) return list1;

    Node *head1 = list1, *head2 = list2;
    Node *tail1 = list1->left, *tail2 = list2->left;

    // 中斷兩個列表的循環結構，方便後續合併
    tail1->right = NULL;
    head1->left = NULL;
    tail2->right = NULL;
    head2->left = NULL;

    // 開始合併
    Node dummy; // 用於合併的虛擬節點
    Node *current = &dummy;

    while (head1 && head2) {
        if (head1->key < head2->key) {
            current->right = head1;
            head1->left = current;
            head1 = head1->right;
        } else {
            current->right = head2;
            head2->left = current;
            head2 = head2->right;
        }
        current = current->right;
    }

    // 接上剩下的節點
    if (head1) {
        current->right = head1;
        head1->left = current;
    } else if (head2) {
        current->right = head2;
        head2->left = current;
    }

    // 確認尾部並重建循環結構
    Node* mergedHead = dummy.right;
    Node* mergedTail = mergedHead;

    while (mergedTail->right) {
        mergedTail = mergedTail->right;
    }
    mergedHead->left = mergedTail;
    mergedTail->right = mergedHead;

    return mergedHead;
}

// 輸出循環列表
void printCircularList(Node* list) {
    if (!list) return;
    Node* start = list;
    do {
        printf("%d ", list->key);
        list = list->right;
    } while (list != start);
    printf("\n");
}

// 測試程式
int main() {
    // 建立第一個排序的雙向循環列表
    Node* list1 = createNode(1);
    list1->right = createNode(3);
    list1->right->left = list1;
    list1->right->right = createNode(5);
    list1->right->right->left = list1->right;
    list1->right->right->right = list1;
    list1->left = list1->right->right;

    // 建立第二個排序的雙向循環列表
    Node* list2 = createNode(2);
    list2->right = createNode(4);
    list2->right->left = list2;
    list2->right->right = createNode(6);
    list2->right->right->left = list2->right;
    list2->right->right->right = list2;
    list2->left = list2->right->right;

    // 合併兩個列表
    Node* mergedList = mergeCircularLists(list1, list2);

    // 輸出合併結果
    printCircularList(mergedList);

    return 0;
}
