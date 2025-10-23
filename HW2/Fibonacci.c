#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

typedef struct Node {
    int key;
    int degree;
    struct Node *parent, *child, *left, *right;
    int mark;
} Node;

// Fibonacci Heap structure
typedef struct FibonacciHeap {
    Node *min;
    int num;
} FibonacciHeap;

// Helper function to create a new node
Node *createNode(int key) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->degree = 0;
    node->parent = NULL;
    node->child = NULL;
    node->left = node;
    node->right = node;
    node->mark = 0;
    return node;
}

// Create an empty Fibonacci Heap
FibonacciHeap *createHeap() {
    FibonacciHeap *heap = (FibonacciHeap *)malloc(sizeof(FibonacciHeap));
    heap->min = NULL;
    heap->num = 0; //總節點數
    return heap;
}

Node* mergeCircularLists(Node* list1, Node* list2, int comp) {
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

    if(comp == 0){
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
    }else{
        while (head1 && head2) {
            if (head1->degree < head2->degree) {
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

// Insert a node into the Fibonacci Heap
void insert(FibonacciHeap *heap, int key) {     ////// insert //////
    Node *node = createNode(key);
    if (heap->min) {
        heap->min = mergeCircularLists(node, heap->min, 0);
    } else {
        heap->min = node;
    }
    heap->num++;
}

// Consolidate the heap after extract-min
void consolidate(FibonacciHeap *heap) {
    int maxDegree = heap->num;  // 設定最大可能的度數 (通常是堆積中的節點數)
    Node *aux[maxDegree];  // 用來存儲各度數節點的陣列，防止度數重複
    for (int i = 0; i < maxDegree; i++)// 初始化陣列，將所有元素設為 NULL
    {
        aux[i] = NULL;
    }

    Node *current = heap->min;  // 從最小節點開始遍歷根節點
    Node *start = current;  // 保存最初的節點，以便在循環結束後停止
    do {
        Node *x = current;  // 當前處理的節點
        current = current->right;  // 進入下一個節點
        int d = x->degree;  // 當前節點的度數
        // 如果 aux[d] 已經有節點，說明有兩個節點的度數相同，需要合併
        while (aux[d]) {
            Node *y = aux[d];  // 取得另一個相同度數的節點
            
            // 保證 x 始終是較小的節點，這樣可以保持堆的性質
            if (x->key > y->key) {
                Node *temp = x;
                x = y;
                y = temp;
            }
            
    //////////////////////////////////////////////////////////////////////////////////////////////////////

            // 連接 y 到 x，將 y 作為 x 的子節點
            y->left->right = y->right;  // 從根列表移除 y
            y->right->left = y->left;
            y->left = y;
            y->right = y;
            y->parent = x;  // 設置 x 為 y 的父節點

            // 將 y 加入到 x 的子節點列表中
            if (!x->child) {
                x->child = y;
            } else {
                x->child = mergeCircularLists(y, x->child, 0);
            }

            x->degree++;  // x 的度數增加
            y->mark = 0;  // 重置 y 的 mark 標誌
            aux[d] = NULL;  // 在 aux 陣列中清除 d 索引的節點
            d++;  // 嘗試處理下一個更大的度數


    //////////////////////////////////////////////////////////////////////////////////////////////////////

        }

        aux[d] = x;  // 在 aux 陣列中標記當前節點的度數
    } while (current != start);  // 重複直到遍歷完所有根節點
}


// Extract the minimum key
int extractMin(FibonacciHeap *heap) {       ////// extract min //////
    Node *minone = heap->min;

    // Add children of z to root list
    if (minone->child) {
        // printf("have child\n");
        Node *child = minone->child;
        do {//清空child的parent
            child->parent = NULL;
            child = child->right;
        } while (child != minone->child);

        if(minone == minone->right){
            heap->min = minone->child;
        }else{
            minone->left->right = minone->right;
            minone->right->left = minone->left;
            heap->min = mergeCircularLists(minone->right, minone->child, 0);
        }
    }else{
        // printf("no child\n");
        minone->left->right = minone->right;
        minone->right->left = minone->left;
        heap->min = minone->right;
    }
    // printf("now %d\n", heap->min->key);
    if (heap->min) consolidate(heap);
    heap->num--;
    int minKey = minone->key;
    free(minone);
    return minKey;
}

// Print the Fibonacci Heap (level-order traversal)
void printHeap(Node *node) {
    if (!node) return;

    Node* queue[100];  // 假設樹的大小不會超過100
    int front = 0, rear = 0;

    queue[rear++] = node;  // 把根節點入隊

    while (front < rear) {
        Node* temp = queue[front++];  // 出隊
        printf("%d ", temp->key);

        temp = temp->child;
        Node* start = temp;
        if(!temp)continue;
        do
        {
            queue[rear++] = temp;
            temp = temp->right;
        } while (temp != start);
    }
}

void levelOrder(FibonacciHeap *heap) {
    if (!heap->min) return;
    if (heap->min->right != heap->min)
    {
        int endKey = heap->min->key;
        Node *prev = heap->min;
        Node *current = prev->right;
        prev->left = prev;
        prev->right = prev;
        Node *next;
        do
        {
            next = current->right;
            current->left = current;
            current->right = current;
            prev = mergeCircularLists(prev,current,1);
            current = next;
        } while (next->key != endKey);
        heap->min = prev;
    }

    Node *start = heap->min;
    Node *current = start;    
    do {
        printHeap(current);
        printf("\n");
        current = current->right;
    } while (current != start);
}

// Find a node in the Fibonacci Heap
Node *findNode(Node *current, int key) {
    if (!current) return NULL;
    Node *start = current;
    do {
        if (current->key == key) return current;
        Node *found = findNode(current->child, key);
        if (found) return found;
        current = current->right;
    } while (current != start);
    return NULL;
}

// Cut a node from its parent
void cut(Node *node, Node *parent, FibonacciHeap *heap) {
    if (node->right == node) {
        parent->child = NULL;
    } else {
        node->left->right = node->right;
        node->right->left = node->left;
        if (parent->child == node) parent->child = node->right;
    }
    parent->degree--;
    node->parent = NULL;
    node->left = node;
    node->right = node;
    node->mark = 0;
    heap->min = mergeCircularLists(node,heap->min, 0);
}

// Cascading cuts
void cascadingCut(Node *parent, FibonacciHeap *heap) {
    if (!parent->parent) {return;}
    if (parent->mark == 0) {parent->mark = 1; return;}
    else{
        do
        {
            Node *next = parent->parent;
            cut(parent, next, heap);
            parent = next;
        } while (parent->parent && parent->mark == 1);  
        if(parent->parent)parent->mark = 1;
    }
}

// Decrease key operation
void decreaseKey(FibonacciHeap *heap, Node *node, int newKey) {   ////// decrease key //////
    node->key -= newKey;
    Node *parent = node->parent;
    if (parent && node->key < parent->key) {
        cut(node, parent, heap);
        cascadingCut(parent, heap);
    }else if(parent && node->key > parent->key){
        if (node != parent->child)
        {
            node->left->right = node->right;
            node->right->left = node->left;
            node->left = node;
            node->right = node;
            parent->child = mergeCircularLists(node, parent->child, 0);
        }
    }else if (parent == NULL && node != heap->min)
    {
        node->left->right = node->right;
        node->right->left = node->left;
        node->left = node;
        node->right = node;
        heap->min = mergeCircularLists(node, heap->min, 0);
    }
    
    //if (node->key < heap->min->key) heap->min = node;
}

// Delete a node from the Fibonacci Heap
void delete(FibonacciHeap *heap, int key) {         ////// delete //////
    Node *node = findNode(heap->min, key);
    decreaseKey(heap, node, node->key);
    extractMin(heap);
}

void printTop(FibonacciHeap *heap){
    Node *current = heap->min;
    Node* start = current;
    printf("Top: ");
    do
    {
        printf("%d ", current->key);
        current = current->right;
    } while (current != start);
    printf("\n\n");
}

int main() {
    FibonacciHeap *heap = createHeap();
    char command[20];
    int key, value;

    while (1) {
        scanf("%s", command);
        if (strcmp(command, "insert") == 0) {
            scanf("%d", &key);
            insert(heap, key);
        } else if (strcmp(command, "extract-min") == 0) {
            extractMin(heap);
            // printf("extract min\n");
        } else if (strcmp(command, "delete") == 0) {
            scanf("%d", &key);
            delete(heap, key);
            // printf("delete: %d\n", key);
        } else if (strcmp(command, "decrease") == 0) {
            scanf("%d %d", &key, &value);
            Node *node = findNode(heap->min, key);
            decreaseKey(heap, node, value);
            // printf("decrease %d %d\n", key, value);
        } else if (strcmp(command, "exit") == 0) {
            break;
        } else {
            printf("Unknown command\n");
        }
        
        // printTop(heap);
        // printf("min: %d\n\n", heap->min->key);
    }

    // printf("Final Fibonacci Heap:\n");
    levelOrder(heap);
    free(heap);
    return 0;
}
