#include <stdio.h>
#include <stdlib.h>

typedef struct _ListNode{
    int data;
    struct _ListNode *next;
}ListNode,* CyclicList;

CyclicList ListInit() {
    /*创建一个头节点,让指针与指向自己,并返回头节点地址*/
    CyclicList list = (CyclicList)malloc(sizeof(ListNode));
    list->next = list;
    list->data = -1;
    return list;
}
/*插入*/
int ListInsert(CyclicList list,int data,int n) {
    /*将node插入第n位,从n从1开始*/
    if (list == NULL ||  n < 1) {
        return -1;
    }
    ListNode* cur = list;
    int cur_i = 0;
    while(cur->next != list && cur_i < (n-1)) {
        //不是最后一个节点,且不是插入位置的前一个节点,就后移一位
        cur = cur->next;
        cur_i++;
    }
    //如果移到最后节点,仍然不是插入位置前一个节点,出错
    if(cur->next==list)			
	{
		if(cur_i!=(n-1))		
		{
			printf("[%s %d]error din't have No.%d\n", __FUNCTION__,__LINE__, n);
			return -1;	
		}
	}
    ListNode* node = (CyclicList)malloc(sizeof(ListNode));
    node->data = data;
    node->next = cur->next;
    cur->next = node;
    return 0;
}
/*删除*/
int ListDelete(CyclicList list,int* data,int n) {
    if (list == NULL || data == NULL || n < 1) {
        return -1;
    }
    ListNode* cur = list;
    int cur_i = 0;
    while(cur->next != list && cur_i < n - 1) {
        cur = cur->next;
        cur_i++;
    }
    if (cur->next == list) {
        printf("[%s %d]error din't have No.%d\n",__FUNCTION__,__LINE__, n);
        return -1;
    }
    ListNode *delete_node = cur->next;
    cur->next = delete_node->next;
    free(delete_node);
    return 0;
}
/*查找*/
int ListFind(CyclicList list,int *data,int n) {
    if (list == NULL || data == NULL || n < 1) {
        return -1;
    }
    ListNode* cur = list->next;
    int cur_i = 1;
    if (cur == list) {
        printf("[%s %d]error din't have No.%d\n", __FUNCTION__,__LINE__, n);
        return -1;
    }
    while(cur->next != list && cur_i < n) {
        cur = cur->next;
        cur_i++;
    }
    if (cur->next == list) {
        if (cur_i != n) {
            printf("[%s %d]error din't have No.%d\n", __FUNCTION__,__LINE__, n);
			return -1;
        }
    }
    *data = cur->data;
    printf("[%s %d]find No.%d = %d\n", __FUNCTION__,__LINE__, n,*data);
    return 0;
}

void ListDestroy(CyclicList list) {
    ListNode* cur = list->next;
    ListNode* next = NULL;
    while(cur != list) {
        next = cur->next;
        free(cur);
        cur = next;
    }
    list->next = list;
}

void ListPrintf(CyclicList list) {
    ListNode* cur = list->next;
    printf("list:[");
    while(cur != list) {
        printf("%d,",cur->data);
        cur = cur->next;
    }
    printf("]\n");
}

int main()
{
	CyclicList list=ListInit();
	int data=0;
	
	printf("Cycliclist is empty !!! \n");
	ListInsert(list, 2, 2);		// 空链表时，验证插入
	ListDelete(list, &data, 1);	// 空链表时，验证删除
	ListFind(list, &data, 1);	// 空链表时，验证查询
	ListDestroy(list);			// 空链表时，验证销毁
	
	printf("\ninsert 3 data\n");
	// 正常插入3个数据
	ListInsert(list, 1, 1);
	ListInsert(list, 2, 2);
	ListInsert(list, 3, 3);
	ListPrintf(list);
	
	printf("\n验证错误值\n");
	ListInsert(list, 5, 5);		// 验证插入
	ListDelete(list, &data, 4);	// 验证删除
	ListFind(list, &data, 4);	// 验证查询
	
	printf("\n正常操作\n");
	// 正常操作
	ListFind(list, &data, 2);
	printf("delete 2,now\n");
	ListDelete(list, &data, 2);
	ListPrintf(list);
	
	printf("Insert 4 to 2,now\n");
	ListInsert(list, 4, 2);
	ListPrintf(list);
	
	printf("Destroy ,now\n");
	ListDestroy(list);
	ListPrintf(list);

	return 0;
}
