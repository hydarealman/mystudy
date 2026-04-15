#pragma once//头文件保护宏,防止一个头文件被多次包含
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef int LTDataType;
typedef struct ListNode{
    struct ListNode* prev;
    struct ListNode* next;
    LTDataType data;
}ListNode;

//1.动态申请一个结点
ListNode* BuyListNode(LTDataType x) {
    ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        printf("分配内存失败\n");
		exit(-1);
    }
    newNode->prev = newNode->next = NULL;
    newNode->data = x;
    return newNode;
}

//2.创建头节点进行初始化
ListNode* ListInit() {
    ListNode* plist = BuyListNode(0);
    plist->prev = plist->next = plist;
    return plist;
}

//3.尾插
void ListPushBack(ListNode* plist,LTDataType x) {
    assert(plist);
    ListNode* newNode = BuyListNode(x);
    ListNode* tail = plist->prev;
    tail->next = newNode;
    newNode->prev = tail;
    newNode->next = plist;
    plist->prev = newNode;
}
//4.尾删
void ListPopBack(ListNode* plist) {
    assert(plist);
	assert(plist->next != plist);
    ListNode* tail = plist->prev;
    ListNode* tailPrev = tail->prev;
    tailPrev->next = plist;
    plist->prev = tailPrev;
    free(tail);
	tail = NULL;
}
//头插
void ListPushFront(ListNode* plist,LTDataType x) {
    assert(plist);
    ListNode* newNode = BuyListNode(x);
    ListNode* first = plist->next;
    plist->next = newNode;
    newNode->prev = plist;
    newNode->next = first;
    first->prev = newNode;
}
//头删
void ListPopFront(ListNode* plist) {
    assert(plist);
    assert(plist->next != plist);
    ListNode* first = plist->next;
    ListNode* second = first->next;
    plist->next = second;
    second->prev = plist;
    free(first);
    first = NULL;
}
//查找元素
ListNode* ListFind(ListNode* plist,LTDataType x) {
    assert(plist);
    ListNode* cur = plist->next;
    while(cur != plist) {
        if (cur->data == x) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}
//在pos位置之前进行插入
void ListInsert(ListNode* pos,LTDataType x) {
    assert(pos);
    ListNode* newNode = BuyListNode(x);
    ListNode* posPrev = pos->prev;
    posPrev->next = newNode;
    newNode->prev = posPrev;
    newNode->next = pos;
    pos->prev = newNode;
}
//删除pos位置的结点
void ListErase(ListNode* pos) {
    assert(pos);
    ListNode* posPrev = pos->prev;
    ListNode* posNext = pos->next;
    posPrev->next = posNext;
    posNext->prev = posPrev;
    free(pos);
    pos = NULL;
}
//打印数据
void Listprint(ListNode* plist) {
    assert(plist);
    ListNode* cur = plist->next;
    while(cur != plist) {
        printf("%d",cur->data);
        cur = cur->next;
    }
    printf("\n");
}
int main() {

}
