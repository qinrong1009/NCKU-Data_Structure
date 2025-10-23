#include <stdio.h>
#include <stdlib.h>

// 定義鏈表節點
typedef struct Node {
    int vertex;          // 相鄰的頂點
    struct Node* next;   // 下一個節點
} Node;

// 定義圖結構
typedef struct Graph {
    int numVertices;     // 頂點數量
    Node** adjLists;     // 鄰接鏈表陣列
} Graph;

// 創建一個新節點
Node* createNode(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// 創建圖
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;

    // 初始化鄰接鏈表陣列
    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));

    // 初始化所有鄰接鏈表為 NULL
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }

    return graph;
}

// 添加邊到圖中
void addEdge(Graph* graph, int src, int dest) {
    // 添加從 src 到 dest 的邊
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // 如果是無向圖，則也需要添加從 dest 到 src 的邊
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// 移除邊
void removeEdge(Graph* graph, int src, int dest) {
    // 移除從 src 到 dest 的邊
    Node* temp = graph->adjLists[src];
    Node* prev = NULL;

    while (temp != NULL && temp->vertex != dest) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Edge not found from %d to %d\n", src, dest);
        return;
    }

    if (prev == NULL) {
        graph->adjLists[src] = temp->next;
    } else {
        prev->next = temp->next;
    }
    free(temp);

    // 如果是無向圖，則也需要移除從 dest 到 src 的邊
    temp = graph->adjLists[dest];
    prev = NULL;
    while (temp != NULL && temp->vertex != src) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Edge not found from %d to %d\n", dest, src);
        return;
    }

    if (prev == NULL) {
        graph->adjLists[dest] = temp->next;
    } else {
        prev->next = temp->next;
    }
    free(temp);
}

// 顯示圖的鄰接鏈表
void printGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node* temp = graph->adjLists[i];
        printf("Adjacency list of vertex %d: ", i);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}


// 測試主函數
int main() {
    Graph* graph = createGraph(5);  // 創建一個有 5 個頂點的圖

    // 添加邊
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);

    // 顯示圖的鄰接鏈表
    printf("Graph adjacency list:\n");
    printGraph(graph);

    // 移除一條邊
    removeEdge(graph, 1, 4);
    printf("\nGraph after removing edge 1-4:\n");
    printGraph(graph);
    
    return 0;
}