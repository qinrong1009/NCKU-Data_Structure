#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjList;
    int* visited;
    int* disc;
    int* low;
    int* parent;
    int* ap;  // 用來標記關鍵節點
    int time;
} Graph;

// 創建圖
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjList = (Node**)malloc(vertices * sizeof(Node*));
    graph->visited = (int*)calloc(vertices, sizeof(int));
    graph->disc = (int*)malloc(vertices * sizeof(int));
    graph->low = (int*)malloc(vertices * sizeof(int));
    graph->parent = (int*)malloc(vertices * sizeof(int));
    graph->ap = (int*)calloc(vertices, sizeof(int));
    graph->time = 0;

    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
        graph->parent[i] = -1;
    }

    return graph;
}

// 創建新節點
Node* createNode(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// 向圖中添加邊
void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

// DFS 遞迴函數來發現關鍵節點
void DFS(Graph* graph, int u) {
    graph->visited[u] = 1;
    int children = 0;
    Node* adj = graph->adjList[u];
    while (adj != NULL) {
        int v = adj->vertex;
        if (!graph->visited[v]) {
            children++;
            DFS(graph, v);
        }
        adj = adj->next;
    }
    // 根節點的特殊情況
    if (graph->parent[u] == -1 && children > 1){
        graph->ap[u] = 1;
    }
}

// 輸出所有關鍵節點
void printArticulationPoints(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->ap[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

// 釋放圖的記憶體
void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node* temp = graph->adjList[i];
        while (temp != NULL) {
            Node* toDelete = temp;
            temp = temp->next;
            free(toDelete);
        }
    }
    free(graph->adjList);
    free(graph->visited);
    free(graph->disc);
    free(graph->low);
    free(graph->parent);
    free(graph->ap);
    free(graph);
}

// 主函數
int main() {
    Graph* graph = createGraph(5);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 3, 4);

    // 對每個未訪問的節點執行 DFS
    for (int i = 0; i < graph->numVertices; i++) {
        if (!graph->visited[i]) {
            DFS(graph, i);
        }
    }

    // 輸出所有的關鍵節點
    printf("Articulation points: ");
    printArticulationPoints(graph);

    freeGraph(graph);

    return 0;
}
