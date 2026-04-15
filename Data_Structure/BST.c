#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* left;
    struct Node* right;
}Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//插入
void insert(Node** root,int data) {
    if (*root == NULL) {//遇到空结点就插入新节点
        *root = createNode(data);
        return;
    }
    if (data <= (*root)->data) {//小于根节点就遍历左
        insert(&((*root)->left),data);
    }
    else {//大于根节点就遍历右
        insert(&((*root)->right),data);
    }
}

//前序遍历
void inorder(Node* root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%d",root->data);
    inorder(root->right);
}

int main() {
    Node* root = NULL;
    int arr[] = {8, 5, 12, 3, 6, 10, 14};
    int n = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < n; i++) {
        insert(&root, arr[i]);
    }
    printf("中序遍历结果：\n");
    inorder(root);
    return 0;
}