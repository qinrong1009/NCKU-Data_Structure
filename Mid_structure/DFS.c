#include <stdio.h>
#include <stdbool.h>

#define MAX_NODES 105

int graph[MAX_NODES][MAX_NODES]; // 鄰接矩陣
bool visited[MAX_NODES];         // 記錄節點是否被訪問過

// 深度優先搜尋函數
void dfs(int node, int n) {
    // 標記目前節點為已訪問
    visited[node] = true;
    printf("Visited node: %d\n", node);

    // 遍歷所有鄰接的節點
    for (int i = 0; i < n; i++) {
        // 如果有邊連接，且該節點尚未被訪問，遞迴訪問
        if (graph[node][i] == 1 && !visited[i]) {
            dfs(i, n);
        }
    }
}

int main() {
    int n, m; // n 表示節點數，m 表示邊數

    // 初始化圖和訪問陣列
    for (int i = 0; i < MAX_NODES; i++) {
        visited[i] = false;
        for (int j = 0; j < MAX_NODES; j++) {
            graph[i][j] = 0;
        }
    }

    // 輸入節點數和邊數
    printf("Enter number of nodes and edges: ");
    scanf("%d %d", &n, &m);

    // 輸入邊的資料，填入鄰接矩陣
    printf("Enter edges (u v):\n");
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = 1; 
        graph[v][u] = 1; 
    }

    // 從節點 0 開始執行 DFS
    printf("Starting DFS from node 0:\n");
    dfs(0, n);

    return 0;
}
