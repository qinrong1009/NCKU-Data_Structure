#include <stdio.h>
#include <stdlib.h>

const int MAX_SIZE = 105;
int array[MAX_SIZE];

// 交換兩個節點的值
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 返回父節點的索引
int parent(int i) {//root from 0
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

// 插入節點到二元樹（以遞迴方式插入）
void insert(int index, int data) {
    if(array[index] == -1){
        array[index] = data;
        return;
    }
    if(array[index] <= data){
        insert(right(index), data);
    }else{
        insert(left(index), data);
    }
}

// 搜尋樹中的節點
int search(int index, int data) {
    if(array[index] == data){return index;}
    if(array[index] == -1){return -1;}
    if (data < array[index]) {
        return search(left(index), data);
    } else {
        return search(right(index), data);
    }
}

// 前序遍歷（根 -> 左 -> 右）（VLR）
void preorderTraversal(int index) {
    if (array[index] != -1) {
        printf("%d ", array[index]);
        preorderTraversal(left(index));
        preorderTraversal(right(index));
    }
}

// 中序遍歷（左 -> 根 -> 右）(LVR)
void inorderTraversal(int index) {
    if (array[index] != -1) {
        inorderTraversal(left(index));
        printf("%d ", array[index]);
        inorderTraversal(right(index));
    }
}

// 後序遍歷（左 -> 右 -> 根）(LRV)
void postorderTraversal(int index) {
    if (array[index] != -1) {
        postorderTraversal(left(index));
        postorderTraversal(right(index));
        printf("%d ", array[index]);
    }
}

// 找到樹中的最小值節點
int findMin(int index) {
    while (array[left(index)] != -1) {
        index = left(index);
    }
    return index;
}

int findMax(int index) {
    while (array[right(index)] != -1) {
        index = right(index);
    }
    return index;
}

// 刪除節點
void delete(int index, int data) {
    if (array[index] == -1) return;

    // 如果要刪除的節點小於當前節點，遞迴搜尋左子樹
    if (data < array[index]) {
        delete(left(index), data);
    }
    // 如果要刪除的節點大於當前節點，遞迴搜尋右子樹
    else if (data > array[index]) {
        delete(right(index), data);
    } else {
        // 找到要刪除的節點
        // 節點只有一個子節點或沒有子節點
        array[index] = -1;
        if (array[left(index)] != -1) {
            int leftindex = findMax(left(index));
            swap(&array[index], &array[leftindex]);
        } else if (array[right(index)] != -1) {
            int rightindex = findMin(right(index));
            swap(&array[index], &array[rightindex]);
        }
    }
}

void levelOrderTraversal() {
    int index = 0;
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if(array[i] != -1){
            printf("");
        }
    }
}

int main() {

    for (int i = 0; i < MAX_SIZE; i++)
    {
        array[i] = -1;
    }
    
    insert(0, 50);
    insert(0, 30);
    insert(0, 20);
    insert(0, 40);
    insert(0, 70);
    insert(0, 60);
    insert(0, 80);

    // 中序遍歷
    printf("Inorder traversal: ");
    inorderTraversal(0);
    printf("\n");

    // 前序遍歷
    printf("Preorder traversal: ");
    preorderTraversal(0);
    printf("\n");

    // 後序遍歷
    printf("Postorder traversal: ");
    postorderTraversal(0);
    printf("\n");

    // 搜尋某個節點
    int searchValue = 40;
    int result = search(0, searchValue);
    if (result != -1) {
        printf("Found node with value %d\n", array[result]);
    } else {
        printf("Node with value %d not found\n", searchValue);
    }

    // 刪除節點
    delete(0, 20);
    printf("Inorder traversal after deleting 20: ");
    inorderTraversal(0);
    printf("\n");
    
    return 0;
}
