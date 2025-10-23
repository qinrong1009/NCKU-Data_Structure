#include <stdio.h>
#include <stdlib.h>

// 定義堆的節點結構
typedef struct LeftistNode {
    int key;                    // 節點的值
    struct LeftistNode* left;   // 左子樹
    struct LeftistNode* right;  // 右子樹
    int npl;                    // Null Path Length
} LeftistNode;

// 創建一個新的堆節點
LeftistNode* createNode(int key) {
    LeftistNode* newNode = (LeftistNode*)malloc(sizeof(LeftistNode));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    newNode->npl = 0;
    return newNode;
}

// 求Null Path Length (NPL)
int NPL(LeftistNode* node) {
    return node == NULL ? -1 : node->npl;
}

// 合併兩個Min Leftist Tree（遞迴合併）
LeftistNode* meld(LeftistNode* t1, LeftistNode* t2) {
    if (t1 == NULL) return t2;
    if (t2 == NULL) return t1;

    // 確保t1的key小於等於t2的key
    if (t1->key > t2->key) {
        LeftistNode* temp = t1;
        t1 = t2;
        t2 = temp;
    }

    // 遞迴合併右子樹
    t1->right = meld(t1->right, t2);

    // 如果左子樹的NPL小於右子樹，交換左右子樹
    if (NPL(t1->left) < NPL(t1->right)) {
        LeftistNode* temp = t1->left;
        t1->left = t1->right;
        t1->right = temp;
    }

    // 更新當前節點的NPL
    t1->npl = NPL(t1->right) + 1;
    return t1;
}

// 插入操作：插入新的元素並保持最小堆結構
LeftistNode* insert(LeftistNode* root, int key) {
    LeftistNode* newNode = createNode(key);
    return meld(root, newNode);
}

// 刪除根節點操作：刪除最小元素（根節點）
LeftistNode* deleteMin(LeftistNode* root) {
    if (root == NULL) return NULL;

    LeftistNode* temp = root;
    // 合併左右子樹
    LeftistNode* newRoot = meld(root->left, root->right);

    // 釋放根節點記憶體
    free(temp);
    return newRoot;
}

// 層次遍歷
void levelOrderTraversal(LeftistNode* root) {
    if (root == NULL) return;

    LeftistNode* queue[100];  // 假設樹的大小不會超過100
    int front = 0, rear = 0;

    queue[rear++] = root;  // 把根節點入隊

    while (front < rear) {
        LeftistNode* node = queue[front++];  // 出隊
        printf("%d ", node->key);

        // 左右子樹入隊
        if (node->left != NULL) {
            queue[rear++] = node->left;
        }
        if (node->right != NULL) {
            queue[rear++] = node->right;
        }
    }
    printf("\n");
}

// 釋放堆的記憶體
void destroyTree(LeftistNode* root) {
    if (root != NULL) {
        destroyTree(root->left);
        destroyTree(root->right);
        free(root);
    }
}

int main() {
    LeftistNode* root = NULL;

    // 插入元素
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 30);
    root = insert(root, 25);

    // 層次遍歷
    printf("Level order traversal of the Min Leftist Tree: ");
    levelOrderTraversal(root);

    // 刪除最小元素
    root = deleteMin(root);
    printf("After deleting the minimum element: ");
    levelOrderTraversal(root);

    // 合併兩棵樹
    LeftistNode* root2 = NULL;
    root2 = insert(root2, 8);
    root2 = insert(root2, 18);

    printf("Tree 2 before melding: ");
    levelOrderTraversal(root2);

    root = meld(root, root2);
    printf("After melding two trees: ");
    levelOrderTraversal(root);

    // 釋放記憶體
    destroyTree(root);

    return 0;
}
