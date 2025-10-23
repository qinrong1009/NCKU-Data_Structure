#include<stdio.h>
#include<stdlib.h>

typedef struct LinkedList *pointer;//搞懂這個用法

typedef struct {
	int data;
	pointer next; 
}LinkedList;

void Insert(LinkedList** head,int newData){
	LinkedList *newNode = (LinkedList *)malloc(sizeof(LinkedList));
    if(*head == NULL){
        newNode->data = newData;
        newNode->next = newNode;
        *head = newNode;
    }else{
        LinkedList *temp;
        newNode->data = newData;
        newNode->next = *head;
        temp = (*head)->next;
        while (temp->next != (*head))
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    newNode->data = newData;
    newNode->next = *head;
    *head = newNode;
}

void printLinkedList(LinkedList* head) {
    LinkedList *temp;
    temp = head;
    while (temp->next != head) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("%d -> ", temp->data);
}


int main()
{
    LinkedList *head = NULL;//宣告一個指標變數指向NULL
	
    Insert(&head,3);//傳遞指標變數的位置 以修改內容的地址
    Insert(&head,7);
    Insert(&head,10); 
    Insert(&head,16); 
    
    printf("before:\n");
    printLinkedList(head);//沒有要修改 只是需要地址 所以傳指標變數即可
}