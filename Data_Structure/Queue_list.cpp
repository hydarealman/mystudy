#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

/*结点结构*/
typedef struct Node{
    int data;
    struct Node *next;
}Node;

/*链队列结构*/
typedef struct LinkQueue{
    Node* front,*rear;
}LinkQueue;

//初始化链队列
void InitLinkQueue(LinkQueue* LinkQ) {
    Node* head = (Node*)malloc(sizeof(Node));
    if (LinkQ != NULL && head != NULL) {
        LinkQ->front = LinkQ->rear = head;
        head->next = NULL;
    }
}

//判空
bool isEmpty(LinkQueue* LinkQ) {
    return LinkQ->front == LinkQ->rear;
}

//入队
void EnterLinkQueue(LinkQueue* LinkQ,int x) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = x;
    node->next = NULL;
    LinkQ->rear->next = node;
    LinkQ->rear = node;
}

//出队
void ExitLinkQueue(LinkQueue* LinkQ,int* x) {
    if (isEmpty(LinkQ)) {
        return;
    }
    Node* node = LinkQ->front->next;
    *x = node->data;
    //建立新联系
    LinkQ->front->next = node->next;
    //如果队尾出队了,那么就是空队
    if (LinkQ->rear == node)
        LinkQ->front = LinkQ->rear;
    free(node);
}

int main() {

}