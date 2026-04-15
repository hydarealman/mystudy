#include <iostream>
using namespace std;
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

//入栈
void Push(Stack S,ElementType item) {
    Stack tmp;
    tmp = (Stack)malloc(sizeof(struct SNode));
    tmp->Data = item;
    tmp->Next = S->Next;
    S->Next = tmp;
}

//出栈
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
int main() {
    Stack S;int x;
    ElementType i,y;
    printf("请输入一个数: ");
    scanf("%d",&x);
    S = CreateStack();
    while(x > 0) {
        while (x != 0) {
            Push(S,x%8);
            x /= 8;
        }
        if (x == 0) {
            while(!IsEmpty(S)) {
                int num = Pop(S);
                printf("%d ",num);
            }
        }
    }
}