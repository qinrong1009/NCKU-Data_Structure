#include<stdio.h>
#include<stdlib.h>

typedef struct LinkedList *pointer;//搞懂這個用法

typedef struct {
	int data;
	pointer next; 
    pointer prev; 
}LinkedList;

void Insert(LinkedList** head,int newData){
	LinkedList *newNode = (LinkedList *)malloc(sizeof(LinkedList));
    newNode->data = newData;
    newNode->next = *head;
    newNode->prev = NULL;
    if(*head != NULL){
        (*head)->prev = newNode;
    }
    *head = newNode;
}

void printLinkedList(LinkedList* head) {
    LinkedList *temp;
    while (head != NULL) {
        printf("%d -> ", head->data);
        temp = head;
        head = head->next; 
    }
    printf("NULL\n");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->prev; 
    }
    printf("NULL\n");
}


int main()
{
    LinkedList *head = NULL;//宣告一個指標變數指向NULL
	
    Insert(&head,3);//傳遞指標變數的位置 以修改內容的地址
    Insert(&head,7);
    Insert(&head,10); 
    Insert(&head,16); 
    
    // printf("before:\n");
    printLinkedList(head);//沒有要修改 只是需要地址 所以傳指標變數即可


}

/*
*p p是指標變數 存取位置 加*是 1.宣告這是指標變數存取 2.使用時是使用該位置的值
指標變數也有自己的位置
就算只傳指標變數 也要用Type*去接 因為這是他真正的類別
malloc的回傳值也是地址 也要用指標接
指標與struct：(*p).member是正式用法 p->member是方便寫法
*/