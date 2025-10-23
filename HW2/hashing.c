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

// Insert a key
void insert(int key) {
    int index = hash_func(key) * slot;
    int original_index = index;

    // 線性探測
    while (table[index] != -1) {//被占位了
        index = (index + 1) % (bucket*slot);
    }

    table[index] = key;
    //printf("Inserted: %d\n", key);
}

// Search for a key
void search(int key) {
    int index = hash_func(key)*slot;
    int original_index = index;

    // 線性探測
    while (1) {
        if (table[index] == key) {
            search_bucket = index / slot;
            search_slot = index % slot;
            return;
        }
        index = (index + 1) % (bucket*slot);
        if(index == original_index) return;
    }
    return;
}

// Delete a key
void delete(int key) {
    int index = hash_func(key)*slot;
    int original_index = index;
    int lastkey = 0;
    // 線性探測
    while (1) {
        if (table[index] == key) {
            table[index] = -1;
        }
        index = (index + 1) % (bucket*slot);
        if(index == original_index) return;
    }

    // while (table[index] != -1) {
    //     if (table[index] == key) {
    //         table[index] = -1;
    //         //printf("Deleted key %d at index %d.\n", key, index);
    //         break;
    //     }
    //     index = (index + 1) % bucket;
    //     if (index == original_index) {
    //         return; // 回到起點，結束搜尋
    //     }
    // }
    // lastkey = index;
    // index = (index + 1)%(bucket*slot);
    // while(index != original_index){
    //     if(hash_func(table[index]) == hash_func(key)){
    //         swap(&table[index], &table[lastkey]);
    //         lastkey = index;
    //         //printf("detect");
    //     }
    //     index = (index + 1)%(bucket*slot);
    // }
    // for (int i = 0; i < bucket; i++) {
    //     int nonEmpty = i * slot;  // 每個 slot 區域的起始位置

    //     // 遍歷每個 slot 的元素
    //     for (int j = i * slot; j < (i + 1) * slot; j++) {
    //         if (table[j] != -1) {  // 找到非 -1 元素
    //             // 如果找到的非 -1 元素不在 nonEmpty 位置，則交換
    //             if (nonEmpty != j) {
    //                 int temp = table[nonEmpty];
    //                 table[nonEmpty] = table[j];
    //                 table[j] = temp;
    //             }
    //             nonEmpty++;  // 更新下一個非 -1 元素應放置的位置
    //         }
    //     }
    // }
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
        // printtt();
    }
    return 0;
}
