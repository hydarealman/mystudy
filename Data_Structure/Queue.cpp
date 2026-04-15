#include<stdio.h>
#include<iostream>
using namespace std;

#define MAXSIZE 20
typedef struct Queue{
    int data[MAXSIZE];
    int front;
    int rear;
}Queue;


//初始化队列
void InitSeQueue(Queue* queue) {
    queue->front = 0;
    queue->rear = 0;
    return;
}

//获得队列长度
int GetLength(Queue* queue) {
    return (queue->rear - queue->front + MAXSIZE) % MAXSIZE;
}

//判断队列是否为空
bool isEmpty(Queue* queue) {
    return queue->front == queue->rear;
}

//判满
bool isFull(Queue* queue) {
    return (queue->rear + 1)%MAXSIZE == queue->front;
}

//入队
void EnterQueue(Queue* queue,int e) {
    if (isFull(queue)) {
        printf("队列满了\n");
        return;
    }
    else {
        queue->data[queue->rear] = e;
        queue->rear = (queue->rear + 1) % MAXSIZE;
    }
}

//出队
void ExitQueue(Queue* queue,int* e) {
    if (isEmpty(queue)) {
        printf("已经是空队列了\n");
    }
    else {
        *e = queue->data[queue->front];
        queue->front = (queue->front + 1) % MAXSIZE;
    }
}

int main() {

}