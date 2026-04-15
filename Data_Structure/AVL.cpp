#include <iostream>
#include <algorithm>
using namespace std;

struct Node{
    int key;
    int height;
    Node* left;
    Node* right;
    Node(int k) : key(k),height(1),left(NULL),right(NULL) {}
};

//获取节点高度
int getHeight(Node* node) {
    return node ? node->height : 0;
}

//计算结点高度
void updateHeight(Node* node) {
    if (node) {
        node->height = max(getHeight(node->left),getHeight(node->right)) + 1;
    }
}

void rotateLL(Node*& root) {
    Node* leftChild = root->left;
    root->left = leftChild->right;
    leftChild->right = root;
    root = leftChild;
    updateHeight(root->right);//更新原根节点(现右子节点)的高度
    updateHeight(root);//更新根节点的高度
}

void rotateRR(Node*& root) {}

void rotateLR(Node*& root) {}

void rotateRL(Node*& root) {}

//插入

//删除

//查找
Node* search(Node* root,int key) {
    if (!root || root->key == key) return root;
    if (key < root->key) {
        return search(root->left,key);
    }
    else {
        return search(root->right,key);
    }
}



