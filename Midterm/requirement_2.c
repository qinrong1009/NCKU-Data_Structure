#include <stdio.h>
#include <string.h>
#include <stdlib.h>  
#define MAX_N 20

int array[MAX_N];
int size = 0;

void swap(int *a,int* b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int parent(int i){
    return (i-1)/2;
}

int left(int i){
    return 2*i +1;
}

int right(int i){
    return 2*i+2;
}

void insert(int key){
    if(size >= 20){return;}
    int i = size;
    array[i] = key;
    size++;
    while(i != 0 && array[parent(i)] > array[i]){
        swap(&array[parent(i)], &array[i]);
        i = parent(i);
    }
}

int pop(){
    int root = array[0];
    swap(&array[0], &array[size-1]);
    size--;
    int currenIndex = 0;
    while (currenIndex < size)
    {
        int leftIndex = left(currenIndex);
        int rightIndex = right(currenIndex);
        int smalledt = currenIndex;
        if(leftIndex < size && array[leftIndex] > array[smalledt]){
            smalledt = leftIndex;
        }
        if(rightIndex < size && array[rightIndex] > array[smalledt]){
            smalledt = rightIndex;
        }
        if (smalledt == currenIndex)
        {
            break;
        }
        swap(&array[currenIndex], &array[smalledt]);
        currenIndex = smalledt;
    }
    return root;
}

int main() {
    // Input
    int n;  // The first line input
    // int heap[MAX_N];  // operations should be performed on this array


    if (scanf("%d", &n) != 1) {
        return 1; 
    }

    while (scanf("%d", &array[size]) == 1) {
        size++;
        if (size >= MAX_N) break; 
    }   

    int back[n];

    for (int i = n-1; i >= 0; i--)
    {
        back[i] = pop();
    }
    

    // Output
    for (int i = 0; i < size; i++) {
        printf("%d", array[i]);
        if (i < size-1) printf(" ");
    }
    printf(" ");
    for (int i = 0; i < n; i++)
    {
        printf("%d", back[i]);
        if (i < n - 1) printf(" ");
    }
    
    printf("\n");

    return 0;
}