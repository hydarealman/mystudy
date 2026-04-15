#include<stdio.h>
#include<malloc.h>
#define MAXSIZE 100  
typedef int ElementType;

typedef struct LNode *List;
struct  LNode{
    ElementType Data[MAXSIZE];
    int last;//定义线性表的最后一个元素
};
List L;

List MakeEmpty(); //初始化顺序表 
int Find(ElementType X,List L); //查找 X 第一次出现的下标 
void Insert(ElementType X,int i,List L); //在下标为 i 的地方插入 X 
void Delete(int i,List L);   //删除下标为 i 的当前值 
ElementType FindKth(int K,List L);  //返回下标为 K 的当前值
int Length(List L);  //返回顺序表的长度 


//初始化
List MakeEmpty() {
    List L;
    L = (List)malloc(sizeof(struct LNode));
    L->last = -1;
    return L;
}

//按值查找
int Find(ElementType X,List L) {
    int i = 0;
    while(i <= L->last && L->Data[i] != X) {
        i++;
    }
    if (L->last < i) {
        return -1;
    }
    else {
        return i;
    }
}

//插入(插入的时候需要检查是否表满,插入位置受否合法)
void Insert(ElementType x,int i,List L) {
    int j;
    if (L->last == MAXSIZE-1) {
        printf("表满");
        return;
    }
    if (i < 0 || L->last + 1 < i) {
        printf("位置不合法");
        return;
    }
    //从后往前依次向后挪一个,给a[i]腾出位置
    for (j = L->last; j >= i; j--) {
        L->Data[j+1] = L->Data[j];
    }
    L->Data[i] = x;
    L->last++;
    return;
}

//删除
void Delete(int i,List L) {
    int j;
    if (j < 0 || L->last < i) {
        printf("L->Data[%d]不存在元素",i);
        return;
    }
    //从前往后依次向前挪一个,将a[i]覆盖了
    for (j = i; j <= L->last; j++) {
        L->Data[j-1] = L->Data[j];
    }
    L->last--;
    return;
}

//按序查找
ElementType FindKth(int K,List L) {
    if (K < 0 || L->last < K) {
        printf("L->Data[%d]不存在元素",K);
        return 0; 
    }
    return L->Data[K];
}

//表长
int Length(List L) {
    return L->last + 1;
}

int main(){
	int i=0;
	L = MakeEmpty();
	Insert(11,0,L);
	printf("在线性表L-Data[0]插入11\n");
	Insert(25,0,L);
	printf("在线性表L-Data[0]插入25\n");
	Insert(33,0,L);
	printf("在线性表L-Data[0]插入33\n");
	Insert(77,0,L);
	printf("在线性表L-Data[0]插入77\n");
	printf("此时的线性表为："); 
	for(i=0;i<Length(L);i++)
		printf("%d ",L->Data[i]);
	printf("\n");
	printf("查找值为12的下标是：%d\n",Find(12,L));
	printf("下标为3的线性表的值是：%d\n",FindKth(3,L));
	Delete(2,L);
	printf("删除线性表中下标为2的元素\n");
	Delete(2,L);
	printf("删除线性表中下标为2的元素\n");
	printf("此时的线性表为："); 
	for(i=0;i<Length(L);i++)
		printf("%d ",L->Data[i]);
	printf("\n"); 
	return 0;
} 