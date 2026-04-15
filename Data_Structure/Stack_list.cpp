#include<stdio.h>
#include<malloc.h>
typedef int ElementType;
typedef struct SNode *Stack; 
struct SNode{
    ElementType Data;
    Stack Next;
};

Stack CreateStack();  // 初始化链栈 
int IsEmpty(Stack S);  // 判断链栈是否为空 
void Push(Stack S,ElementType item);  // 入栈 
ElementType Pop(Stack S);  // 出栈

//初始化
Stack CreateStack(){
    Stack S;
    S = (Stack)malloc(sizeof(struct SNode));
    S->Next = NULL;
    return S;
}

//判断是否为空
int IsEmpty(Stack S) {
    return (S->Next == NULL);
}

//入栈(头插法)
void Push(Stack S,ElementType item) {
    Stack tmp;
    tmp = (Stack)malloc(sizeof(struct SNode));
    tmp->Data = item;
    tmp->Next = S->Next;
    S->Next = tmp;
}

//出栈(保留虚拟头节点,删除首元节点)
ElementType Pop(Stack S) {
    Stack First;
    ElementType TopVal;
    if (IsEmpty(S)) {
        printf("堆栈空");
        return 0;
    }
    else{
        First = S->Next;
        S->Next = First->Next;
        TopVal = First->Data;
        free(First);
        return TopVal;
    }
}

int main(){
	Stack S;
	S = CreateStack();
	printf("5入栈\n");
	Push(S,5);
	printf("7入栈\n");
	Push(S,7);
	printf("66入栈\n");
	Push(S,66);
	printf("%d出栈\n",Pop(S));
	printf("%d出栈\n",Pop(S));
	return 0;
} 
