#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100
char input[MAX_SIZE];
char postfix[MAX_SIZE];
char stack[MAX_SIZE];

int stackSize = 0;
int postSize = 0;

char variables[MAX_SIZE];
float values[MAX_SIZE];
int numVar = 0;

char top(){
    return stack[stackSize - 1];
}

char pop(){
    stackSize -= 1;
    return stack[stackSize];
}

void push(char oper){
    if(oper >= 'a' && oper <= 'z'){
        postfix[postSize++] = oper;
    }else if (oper == '(')
    {
        stack[stackSize++] = oper;
    }else if (oper == '*' || oper == '/')
    {
        while (stack[stackSize - 1] == '*' || stack[stackSize - 1] == '/')
        {
            postfix[postSize++] = pop();
        }
        stack[stackSize++] = oper;
    }else if(oper == '+' || oper == '-'){
        while (stack[stackSize - 1] == '*' || stack[stackSize - 1] == '/' || stack[stackSize - 1] == '+' || stack[stackSize - 1] == '-')
        {
            postfix[postSize++] = pop();
        }
        stack[stackSize++] = oper;
    }else if (oper == ')')
    {
        while (stack[stackSize - 1] != '(')
        {
            postfix[postSize++] = pop();
        }
        pop();
    }else if (oper == '$')
    {
        while (stackSize > 0)
        {
            postfix[postSize++] = pop();
        }
    }
    
}


// 樹的節點結構
typedef struct TreeNode {
    char data;
    int height;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 創建新節點
TreeNode* createNode(char data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->height = 0;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void addHeight(TreeNode* root, int h){
    if (root == NULL){return;}
    root->height = h;
    addHeight(root->left,h+1);
    addHeight(root->right,h+1);
    
}

void levelOrderTraversal(TreeNode* root) {
    if (root == NULL) return;

    TreeNode* queue[100];  // 假設樹的大小不會超過100
    int front = 0, rear = 0, h = -1;

    queue[rear++] = root;  // 把根節點入隊

    while (front < rear) {
        TreeNode* node = queue[front++];  // 出隊
        if(node->height > h && node->height != 0){
            printf("\n");
            h = node->height;
        }
        printf("%c ", node->data);

        // 左右子樹入隊
        if (node->left != NULL) {
            queue[rear++] = node->left;
        }
        if (node->right != NULL) {
            queue[rear++] = node->right;
        }
    }
}

// 前序遍歷（根 -> 左 -> 右）（VLR）
void preorderTraversal(TreeNode* root) {
    if (root != NULL) {
        printf("%c ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// 後序遍歷（左 -> 右 -> 根）(LRV)
void postorderTraversal(TreeNode* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%c ", root->data);
    }
}

// 後序遍歷（左 -> 右 -> 根）(LRV)
float postorderEvaluation(TreeNode* root) {
    if(root->data >= 'a' && root->data <= 'z'){
        float value = 0;
        for (int i = 0; i < numVar; i++)
        {
            if(root->data == variables[i]){value = values[i];}
        }
        return value;
    }else{
        float left = postorderEvaluation(root->left);
        float right = postorderEvaluation(root->right);
        if(root->data == '+'){return left + right;}
        if(root->data == '-'){return left - right;}
        if(root->data == '*'){return left * right;}
        if(root->data == '/'){return left / right;}
    }
    return 0;
}

int main() {
    printf("Please enter an infix expression and press enter:");
    while (scanf("%s",input) != EOF)
    {
        for (int i = 0; i < strlen(input); i++)
        {
            push(input[i]);
        }
        push('$');
        
        TreeNode* tree[postSize];
        int treeSize = 0;


        for (int i = 0; i < postSize; i++)
        {
            if (postfix[i] >= 'a' && postfix[i] <= 'z')
            {
                tree[treeSize++] = createNode(postfix[i]);
                variables[numVar++] = postfix[i];
            }else{
                TreeNode* root = createNode(postfix[i]);
                root->right = tree[--treeSize];
                root->left = tree[--treeSize];
                tree[treeSize++] = root;
            }
        }
        if(treeSize == 1){
            addHeight(tree[0], 0);
            printf("The level-order of the expression tree:\n");
            levelOrderTraversal(tree[0]);
        }
        printf("\nThe postfix expression: ");
        postorderTraversal(tree[0]);
        printf("\nThe prefix expression: ");
        preorderTraversal(tree[0]);
        printf("\n");
        for (int i = 0; i < numVar; i++)
        {
            printf("Please enter %c = ",variables[i]);
            scanf("%f", &values[i]);
        }
        printf(" = %.2f\n",postorderEvaluation(tree[0]));
        printf("Please enter an infix expression and press enter:");
        stackSize = 0;
        postSize = 0;
        numVar = 0;

    }
    return 0;
}