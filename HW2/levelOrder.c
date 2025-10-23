#include <stdio.h>
#include <stdlib.h>

// 樹的節點結構
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 創建新節點
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 插入節點到二元樹（以遞迴方式插入）
TreeNode* insert(TreeNode* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    return root;
}


void levelOrderTraversal(TreeNode* root) {
    if (root == NULL) return;

    TreeNode* queue[100];  // 假設樹的大小不會超過100
    int front = 0, rear = 0;

    queue[rear++] = root;  // 把根節點入隊

    while (front < rear) {
        TreeNode* node = queue[front++];  // 出隊
        printf("%d ", node->data);

        // 左右子樹入隊
        if (node->left != NULL) {
            queue[rear++] = node->left;
        }
        if (node->right != NULL) {
            queue[rear++] = node->right;
        }
    }
}

// 中序遍歷（左 -> 根 -> 右）
void inorderTraversal(TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}


int main() {
    TreeNode* root = NULL;

    // 插入節點
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    // 層次遍歷
    printf("Level-order traversal: ");
    levelOrderTraversal(root);
    printf("\n");

    // 中序遍歷
    printf("Inorder traversal: ");
    inorderTraversal(root);
    printf("\n");

    // 釋放記憶體
    destroyTree(root);
    return 0;
}
