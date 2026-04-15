#include<stdio.h>
#include<iostream>
using namespace std;
typedef struct LNode{
    int data;
    LNode* next;
}LNode,*LinkList;
int len = 0;
int len2 = 0;
// //创建链表
// void CreateList(LinkList L,int n) {
//     L = new LNode;
//     L->next = NULL;
//     LinkList r = L;
//     for (int i = 0; i < n; i++) {
//         LinkList p = new LNode;
//         cin >> p->data;
//         p->next = NULL;
//         r->next = p;
//         r = p;
//     }
// }  
//前插法创建链表 
void CreateList_Head(LinkList L,int n) {
    L = new LNode;
    L->next = NULL;

    for (int i = 0; i < n; i++) {
        LinkList p = new LNode;
        cin >> p->data;
        p->next = L->next;
        L->next = p;
    }
}
//后插法创建链表
void CreateList_Tail(LinkList L,int n) {
    LinkList r;
    L = new LNode;
    L->next = NULL;
    r = L;
    for (int i = 0; i < n; i++) {
        LinkList p = new LNode;
        cin >> p->data;
        p->next = NULL;
        r->next = p;
        r = p;
    }
}

//在链表最后插入数据
void LL_add(LinkList head,int x) {
    LinkList l = new LNode;
    l->next = NULL;
    l->data = x;
    if (head->next == NULL) {
        head->next = l;
    }
    else {
        LinkList r = head;
        while(r->next != NULL) {
            r = r->next;
        }
        r->next = l;
    }
}
//查找并返回第i个节点
LinkList LL_index(LinkList head,int i) {
    if ((i <= 0) || (i > len)) {
        cout << "error" << endl;
        return NULL;
    }
    else {
        LinkList r = head;
        for (int k = 0; k <= i; k++) {
            r = r->next;
        }
        return r;
    }
}
//打印并输出第i个节点
void LL_get(LinkList head,int i) {
    int x = LL_index(head,i)->data;
}
//把数据插入到第i个节点处
void LL_insert(LinkList head,int i,int item) {
    if (i <= 0 || i > len) {
        cout << "error" << endl;
        return;
    }
    else {
        LinkList l = new LNode;
        l->data = item;
        l->next = LL_index(head,i);
        LL_index(head,i-1)->next = l;
        len++;
        ///LL_display();
    }
}
//删除第i个节点
LinkList LL_del(LinkList head,int i) {
    if (i <= 0 || i >= len) {
        cout << "error" << endl;
    }
    else {
        if (i == 1) {
            LinkList temp = LL_index(head,i);
            head->next = LL_index(head,2);
            delete temp;
        }
        else if (i == len) {
            LinkList temp = LL_index(head,i);
            LL_index(head,i-1)->next = NULL;
            delete temp;
        }
        else {
            LinkList temp = LL_index(head,i);
            LL_index(head,i-1)->next = LL_index(head,i+1);
            delete temp;
        }
    }
    return head;
}
//打印输出链表的所有节点
void LL_display(LinkList head) {
    LinkList p = head;
    while(p->next != NULL) {
        p = p->next;
        cout << p->data << " ";
    }
    cout << endl;
}
//节点交换函数
void swap(LinkList head,int pa,int pb) {
    if (pa != pb && pa > 0 && pa <= len && pb > 0 && pb <= len) {
        LinkList p = LL_index(head,pa);
        LinkList q = LL_index(head,pb);

        LinkList p_before;
        if (pa == 1) {
            p_before = head;
        }
        else {
            p_before = LL_index(head,pa-1);
        }
        
        LinkList p_after;
        if (pa == len) {
            p_after = NULL;
        }
        else {
            p_after = LL_index(head,pa + 1);
        }

        LinkList q_before;
        if (pb == 1) {
            q_before = head;
        }
        else {
            q_before = LL_index(head,pb - 1);
        }

        LinkList q_after;
        if (pb == len) {
            q_after = NULL;
        }
        else {
            q_after = LL_index(head,pa + 1);
        }

        p_before->next = q;
        q->next = p_after;

        q_before->next = p;
        p->next = q_after;
        LL_display(head);
    }
    else {
        cout << "error" << endl;
        return;
    }
}
//单链表排序函数
void sort(LinkList head) {
    for (int i = 1; i <= len; i++) {
        for (int k = i; k <= len; k++) {
            if (LL_index(head,i)->data > LL_index(head,k)->data) {
                swap(head,i,k);
            }
        }
    }
}
//链表合并函数
LinkList LL_merge(LinkList& La,LinkList& Lb) {
    LinkList L;
    LinkList p;
    p = La;
    for (int i = 1; i <= len; i++) {
        p = p->next;
        LL_insert(L,i,p->data);
    }
    p = Lb;
    for (int i = 1; i <= len2; i++) {
        p = p->next;
        LL_insert(L,i,p->data);
    }
    for (int i = 1; i <= len + len2; i++) {
        for (int  k = i; k <= len + len2; k++) {
            if (LL_index(L,i)->data > LL_index(L,k)->data) {
                swap(L,i,k);
            }
        }
    }
    return L;
}
int main() {

}