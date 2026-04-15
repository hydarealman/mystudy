#include<stdio.h>
#include<malloc.h> 
#define MaxSize 100 
typedef int ElementType;
typedef struct SNode *Stack;
struct SNode{
    ElementType Data[MaxSize];
    int Top;
};
Stack S;

Stack CreateStack();  // 初始化堆栈 
int IsFull(Stack S); // 判断堆栈是否已满 
int IsEmpty(Stack S);   // 判断堆栈是否为空 
void Push(Stack S,ElementType item);   // 入栈 
ElementType Pop(Stack S);   // 出栈 

//初始化堆栈
Stack CreateStack() {
    S = (Stack)malloc(sizeof(struct SNode));
    S->Top = -1;
    return S;
}

//是否已满
int IsFull(Stack S) {
    return (S->Top == MaxSize-1);
}

//是否为空
int IsEmpty(Stack S) {
    return (S->Top == -1);
}

//入栈
void Push(Stack S,ElementType item) {
    if (IsFull(S)) {
        printf("堆栈满");
        return;
    }
    else {
        S->Top++;
        S->Data[S->Top] = item;
        return;
    }
}

int GetTop(Stack S,ElementType *e) {
    if (IsEmpty(S)) {
        return -1;//栈空
    }
    *e = S->Data[S->Top];
    return 0;//操作成功
}

//出栈
ElementType Pop(Stack S) {
    if (IsEmpty(S)) {
        printf("堆栈已空");
        return 0;
    }
    else {
        ElementType val = S->Data[S->Top];
        S->Top--;
        return val;
    }
}

int main(){
	S = CreateStack();
	Push(S,5);
	Push(S,7);
	Push(S,66);
    ElementType num = 0;//声明的时候应该声明对象,传入的时候再取地址,否则如果创建指针直接传入指针,其实是传入了一个未初始化的指针，会导致未定义的发生
    GetTop(S,&num);
    printf("%d",num);
	// printf("%d\n",Pop(S));
	// printf("%d\n",Pop(S));
	return 0;
}