#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 10  // 最大頂點數量，可以根據需求調整

// 定義 Graph 結構
typedef struct {
    int matrix[MAX_VERTICES][MAX_VERTICES];  // 鄰接矩陣
    int numVertices;                         // 當前圖的頂點數量
} Graph;

// 創建圖，初始化鄰接矩陣
Graph* createGraph(int numVertices) {
    if (numVertices > MAX_VERTICES) {
        printf("超過最大頂點數量\n");
        return NULL;
    }

    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;

    // 初始化鄰接矩陣，所有邊都設為 0
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            graph->matrix[i][j] = 0;
        }
    }

    return graph;
}

// 添加邊
void addEdge(Graph* graph, int start, int end) {
    if (start >= graph->numVertices || end >= graph->numVertices) {
        printf("頂點超出範圍\n");
        return;
    }
    graph->matrix[start][end] = 1;  // 有邊從 start 到 end
    graph->matrix[end][start] = 1;  // 若是無向圖，也需要這樣設置
}

// 移除邊
void removeEdge(Graph* graph, int start, int end) {
    if (start >= graph->numVertices || end >= graph->numVertices) {
        printf("頂點超出範圍\n");
        return;
    }
    graph->matrix[start][end] = 0;  // 刪除從 start 到 end 的邊
    graph->matrix[end][start] = 0;  // 若是無向圖，也需要這樣設置
}

// 顯示圖的鄰接矩陣
void printGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        for (int j = 0; j < graph->numVertices; j++) {
            printf("%d ", graph->matrix[i][j]);
        }
        printf("\n");
    }
}

// 釋放圖的記憶體
void destroyGraph(Graph* graph) {
    free(graph);
}

// 測試主函數
int main() {
    // 創建一個包含 5 個頂點的圖
    Graph* graph = createGraph(5);

    // 添加邊
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    // 顯示圖的鄰接矩陣
    printf("Graph adjacency matrix:\n");
    printGraph(graph);

    // 移除一條邊
    removeEdge(graph, 1, 4);
    printf("\nGraph after removing edge 1-4:\n");
    printGraph(graph);

    // 釋放記憶體
    destroyGraph(graph);

    return 0;
}
