//单文件编译g++ -o 输出文件名 源文件.cpp
//调试g++ -g -o hello hello.cpp  # 便于后续使用GDB调试[4,9](@ref)
//运行.\输出文件名.exe  # 例如 .\hello.exe[1,2](@ref)
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAXSIZE 8
typedef int ElemType;

typedef struct{
    ElemType *base;
    int front;
    int rear;
}Queue;

/*队头指向将要出列的元素,队尾指向下一个元素将要进来的位置*/
//初始化队列
void InitQueue(Queue *Q) {
    Q->base = (ElemType*) malloc(sizeof(ElemType) * MAXSIZE);
    assert(Q->base != NULL);
    Q->front = Q->rear = 0;
}

//入队操作
void EnQueue(Queue *Q,ElemType x) {
    if ((Q->rear + 1) % MAXSIZE == Q->front) return;  //队列已满
    Q->base[Q->rear] = x;
    Q->rear = (Q->rear + 1) %MAXSIZE;
}

//出队操作
void DeQueue(Queue *Q) {
    if (Q->front == Q->rear) return;//队列为空
    Q->front = (Q->front + 1) % MAXSIZE;
}

//打印队列数据
void ShowQueue(Queue *Q) {
    for (int i = Q->front; i != Q->rear; i = (i + 1)%MAXSIZE) {
        printf("%d",Q->base[i]);
    }
    printf("\n");
}

//获取队头元素
void GetHead(Queue *Q,ElemType *v) {
    if (Q->front == Q->rear) return;//队列为空
    *v = Q->base[Q->front];
}

//获取队列长度
int Length(Queue *Q) {
    int len = Q->rear - Q->front;
    return (len >= 0) ? len : MAXSIZE + len;
}

//清空和销毁队列
void ClearQueue(Queue *Q) {
    Q->front = Q->rear = 0;
}

void DestroyQueue(Queue *Q) {
    free(Q->base);
    Q->base = NULL;
}

int main() {
    Queue Q;
    InitQueue(&Q);
    for (int i = 1; i <= 8; ++i) {
        EnQueue(&Q, i);
    }
    ShowQueue(&Q);
    DeQueue(&Q);
    EnQueue(&Q, 10);
    DeQueue(&Q);
    EnQueue(&Q, 20);
    ShowQueue(&Q);
    printf("Length: %d\n", Length(&Q));
    return 0;
}
