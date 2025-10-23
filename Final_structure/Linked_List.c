#include<stdio.h>
#include<stdlib.h>

//typedef struct LinkedList *pointer;//搞懂這個用法

typedef struct LinkedList{
	int data;
	struct LinkedList *next; 
}LinkedList;

void Insert(LinkedList** head,int newData){
	LinkedList *newNode = (LinkedList *)malloc(sizeof(LinkedList));
    newNode->data = newData;
    newNode->next = *head;
    *head = newNode;
}

void InsertAfterK(LinkedList** head,int targetData, int newData){
    LinkedList *target = NULL;
    LinkedList *trace = (*head);
    while (trace != NULL)
    {
        if(trace->data == targetData){
            target = trace;
            break;
        }
        trace = trace->next;
    }
    if(trace == NULL){
        return;
    }
	LinkedList *newNode = (LinkedList *)malloc(sizeof(LinkedList));
    newNode->data = newData;
    newNode->next = target->next;
    target->next = newNode;
}

void Delete(LinkedList** head,int targetData){
    LinkedList *target = NULL;
    LinkedList *prev = NULL;
    LinkedList *trace = (*head);
    while (trace != NULL)
    {
        if(trace->data == targetData){
            target = trace;
            break;
        }
        prev = trace;
        trace = trace->next;
    }
    if(trace == NULL){
        return;
    }
	prev->next = target->next;
}

void printLinkedList(LinkedList* head) {
    while (head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}

int get(LinkedList* head, int index) {
    LinkedList *target = head;
    for (int i = 0; i < index; i++)
    {
        if(target == NULL){break;}
        target = target->next;
    }
    if(target == NULL){return -1;}
    return target->data;
}

int main()
{
    LinkedList *head = NULL;//宣告一個指標變數指向NULL
	
    Insert(&head,3);//傳遞指標變數的位置 以修改內容的地址
    Insert(&head,7);
    Insert(&head,10); 
    
    printf("before:\n");
    printLinkedList(head);//沒有要修改 只是需要地址 所以傳指標變數即可

    InsertAfterK(&head,3,5);
    printf("After:\n");
    printLinkedList(head);

    Delete(&head, 7);
    printf("After:\n");
    printLinkedList(head);
	
    printf("%d",get(head, 3));
}

/*
*p p是指標變數 存取位置 加*是 1.宣告這是指標變數存取 2.使用時是使用該位置的值
指標變數也有自己的位置
就算只傳指標變數 也要用Type*去接 因為這是他真正的類別
malloc的回傳值也是地址 也要用指標接
指標與struct：(*p).member是正式用法 p->member是方便寫法
*/