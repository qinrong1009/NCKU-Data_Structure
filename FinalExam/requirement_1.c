#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY -1    // Marker for an empty slot

int *hashTable;     // Dynamically allocated hash table
int n;              // Number of buckets

int countBit(int key){
    int count = 0;
    while (key != 0)
    {
        count++;
        key = key/10;
    }
    return count;
}

//Write a function to insert the values and shiftFoldingHash
int shiftFoldingHash(int key) {
    int sum = 0;
    int length = countBit(key);
    int remain = length % 3;
    if (remain != 0)
    {
        if (remain == 1)
        {
            sum = sum + key%10;
            key = key/10;
        }else{
            sum = sum + key%100;
            key = key/100;
        }
    }
    while (key != 0)
    {
        sum = sum + key % 1000;
        key = key/1000;
    }
    return sum % n;
}


void insertKey(int key) {
    int h = shiftFoldingHash(key);
    int index = h;
    int count = 0;
    while(hashTable[index] != EMPTY){
        count++;
        index = (h + count*count) % n;
    }
    hashTable[index] = key;
    // printf("insert at %d", index);
    return;
}


void searchKey(int key) {
    int h = shiftFoldingHash(key);
    int i = 0;
    while (i < n) {
        int pos = (h + i*i) % n;
        // Found the key
        if (hashTable[pos] == key) {
            printf("%d\n", pos);
            return;
        }
        i++;
    }
}


void deleteKey(int key) {
    int h = shiftFoldingHash(key);
    int i = 0;
    while (i < n) {
        int pos = (h + i*i) % n;
        if (hashTable[pos] == key) {
            hashTable[pos] = EMPTY;
            return;
        }
        i++;
    }
}

int main() {

    scanf("bucket %d", &n);

    // Allocate the hash table
    hashTable = (int*)malloc(sizeof(int)*n);
    for (int i = 0; i < n; i++) {
        hashTable[i] = EMPTY;  // Initialize to empty
    }

    // Read commands
    while (1) {
        char cmd[16];
        if (scanf("%s", cmd) != 1) break;

        if (strcmp(cmd, "exit") == 0) {
            break;
        } else if (strcmp(cmd, "insert") == 0) {
            int key;
            scanf("%d", &key);
            insertKey(key);
        } else if (strcmp(cmd, "delete") == 0) {
            int key;
            scanf("%d", &key);
            deleteKey(key);
        } else if (strcmp(cmd, "search") == 0) {
            int key;
            scanf("%d", &key);
            searchKey(key);
        }
    }

    free(hashTable);
    return 0;
}
