#include <stdio.h>
#include <stdlib.h>

// 定義 Disjoint Set 結構
typedef struct {
    int *parent; // parent[i] 代表 i 的父節點
    int *size;   // size[i] 代表以 i 為根的樹的大小
    int n;       // 節點數量
    int *height;       // 樹的高度
} DisjointSet;

// 創建一個大小為 n 的 Disjoint Set
DisjointSet* createSet(int n) {
    DisjointSet* set = (DisjointSet*)malloc(sizeof(DisjointSet));
    set->n = n;
    set->parent = (int*)malloc(n * sizeof(int));
    set->size = (int*)malloc(n * sizeof(int));
    set->height = (int*)malloc(n * sizeof(int));

    // 初始化：每個節點的父節點指向-1，樹的大小為 1
    for (int i = 0; i < n; i++) {
        set->parent[i] = -1;
        set->size[i] = 1;
        set->height[i] = 1;
    }

    return set;
}

// 查找操作（不使用路徑壓縮）
int find(DisjointSet* set, int x) {
    while (set->parent[x] != -1) {
        x = set->parent[x];
    }
    return x;
}

// 合併操作，使用按大小合併
void unionSets(DisjointSet* set, int x, int y) {
    int rootX = find(set, x);
    int rootY = find(set, y);

    if (rootX != rootY) {

        // 合併矮樹到高樹下面（Height Rule）
        if (set->height[rootX] < set->height[rootY]) {
            set->parent[rootX] = rootY;  // 讓 rootX 的父節點指向 rootY
            if(set->height[rootX] + 1 > set->height[rootY]){
                set->height[rootY] += set->height[rootX];  // 更新新樹的大小
            }
        } else {
            set->parent[rootY] = rootX;  // 讓 rootY 的父節點指向 rootX
            if(set->height[rootY] + 1 > set->height[rootX]){
                set->height[rootX] += set->height[rootY];  // 更新新樹的大小
            }
        }
    }
}

// 測試主函數
int main() {
    // 創建一個包含 10 個元素的 Disjoint Set
    DisjointSet* set = createSet(10);

    // 合併一些集合
    unionSets(set, 1, 2);
    unionSets(set, 2, 3);
    unionSets(set, 4, 5);
    unionSets(set, 6, 7);
    unionSets(set, 5, 6);

    // 查找操作
    printf("Find(1): %d\n", find(set, 1));  // 應該返回同一個根
    printf("Find(2): %d\n", find(set, 2));
    printf("Find(3): %d\n", find(set, 3));
    printf("Find(4): %d\n", find(set, 4));
    printf("Find(5): %d\n", find(set, 5));
    printf("Find(6): %d\n", find(set, 6));
    printf("Find(7): %d\n", find(set, 7));

    // 合併兩個集合
    unionSets(set, 1, 7);  // 將集合 1 和集合 7 合併

    printf("Find(1) after union: %d\n", find(set, 1));
    printf("Find(7) after union: %d\n", find(set, 7));

    return 0;
}
