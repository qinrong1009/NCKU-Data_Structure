#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 200

int table[MAX_SIZE];
int bucket = 0;
int slot = 0;

int search_bucket;
int search_slot;

// 初始化 table 為空
void init_table() {
    for (int i = 0; i < MAX_SIZE; i++) {
        table[i] = -1; // -1 表示空位
    }
}

// Hash function
int hash_func(int key) {
    return key % bucket;
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
    return;
}

void insert(int key) {
    int index = hash_func(key) * slot;
    int original_index = index;

    // 線性探測
    while (table[index] != -1) {
        index = (index + 1) % (bucket*slot);
    }

    table[index] = key;
}

int search(int key) {
    int index = hash_func(key)*slot;
    int original_index = index;

    // 線性探測
    while (1) {
        if (table[index] == key) {
            search_bucket = index / slot;
            search_slot = index % slot;
            return 1;
        }
        index = (index + 1) % (bucket*slot);
        if(index == original_index) return -1;
    }
    return -1;
}

void delete(int key) {
    int index = hash_func(key)*slot;
    int original_index = index;

    // 線性探測
    while (table[index] != -1) {
        if (table[index] == key) {
            table[index] = -1;
            break;
        }
        index = (index + 1) % bucket;
        if (index == original_index) {
            return; // 回到起點，結束搜尋
        }
    }

    int lastSpace = index;//記錄空格
    int currentIndex = index + 1;

    while (table[currentIndex] != -1 && currentIndex != index){//current輪到空格了（連續的一串都檢查完） or 回到起點
        int target = hash_func(table[currentIndex]) * slot;//currentIndex的理想格數
        int currentDistance = (currentIndex >= target) ? currentIndex - target : bucket*slot - target + currentIndex;//currentIndex離理想格數的距離
        int spaceDistance = (lastSpace >= target) ? lastSpace - target : bucket*slot - target + lastSpace;//lastspcae離理想格數的距離
        if (spaceDistance < currentDistance) //lastspace離理想格數比較近 => 交換可以讓currentIndex更近
        {
            swap(&table[lastSpace], &table[currentIndex]);
            lastSpace = currentIndex;
        }
        currentIndex = (currentIndex + 1) % (bucket * slot);
    }
    return;
}

void printtt(){
    for (int i = 0; i < bucket*slot; i++)
    {
        printf("%d ",table[i]);
    }
    printf("\n");
}

// Main function for testing
int main() {
    char command[10];
    int key;

    init_table();

    while (1) {
        scanf("%s", command);
        if (strcmp(command, "bucket") == 0) {
            scanf("%d", &key);
            bucket = key;
        }else if (strcmp(command, "slot") == 0) {
            scanf("%d", &key);
            slot = key;
        }else if (strcmp(command, "insert") == 0) {
            scanf("%d", &key);
            insert(key);
        } else if (strcmp(command, "search") == 0) {
            scanf("%d", &key);
            search(key);
            printf("%d %d\n", search_bucket, search_slot);
        } else if (strcmp(command, "delete") == 0) {
            scanf("%d", &key);
            delete(key);
        } else if (strcmp(command, "exit") == 0) {
            break;
        }
    }
    printtt();
    return 0;
}
