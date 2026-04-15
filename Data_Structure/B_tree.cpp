#include <stdio.h>
#include <stdlib.h>

// B 树的阶数
#define ORDER 3

// B 树节点结构
typedef struct BTreeNode {
    int leaf; // 是否是叶子节点
    int n;    // 当前关键字数量
    int keys[ORDER - 1]; // 关键字数组
    struct BTreeNode* child[ORDER]; // 子节点数组
} BTreeNode;

// 创建新节点
BTreeNode* createNode() {
    BTreeNode* newNode = (BTreeNode*)malloc(sizeof(BTreeNode));
    newNode->leaf = 1;
    newNode->n = 0;
    for (int i = 0; i < ORDER - 1; ++i) {
        newNode->keys[i] = 0;
    }
    for (int i = 0; i < ORDER; ++i) {
        newNode->child[i] = NULL;
    }
    return newNode;
}

// 分裂节点
void splitChild(BTreeNode* parent, int index, BTreeNode* child) {
    BTreeNode* newNode = createNode();
    newNode->leaf = child->leaf;
    newNode->n = ORDER / 2 - 1;

    // 将 child 中的一半关键字移动到 newNode 中
    for (int i = 0; i < ORDER / 2 - 1; ++i) {
        newNode->keys[i] = child->keys[i + ORDER / 2];
    }

    // 如果 child 不是叶子节点，将一半子节点移动到 newNode 中
    if (!child->leaf) {
        for (int i = 0; i < ORDER / 2; ++i) {
            newNode->child[i] = child->child[i + ORDER / 2];
            child->child[i + ORDER / 2] = NULL;
        }
    }

    // 调整 child 的关键字数量
    child->n = ORDER / 2 - 1;
    newNode->n = ORDER / 2 - 1;

    // 将 parent 中的一个关键字和 newNode 相关的子节点插入到 parent 中
    for (int i = parent->n; i > index; --i) {
        parent->keys[i] = parent->keys[i - 1];
        parent->child[i + 1] = parent->child[i];
    }
    parent->keys[index] = child->keys[ORDER / 2 - 1];
    parent->child[index + 1] = newNode;

    // 调整 parent 的关键字数量
    parent->n++;

    // 将 parent 中的一个关键字插入到 child 中
    child->keys[ORDER / 2 - 1] = 0;
    child->child[ORDER / 2] = NULL;
}

// 插入非满节点
void insertNonFull(BTreeNode** root, int key) {
    BTreeNode* node = *root;
    int i = node->n - 1;

    // 如果是叶子节点，直接插入
    if (node->leaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->n++;
    } else {
        // 如果是内部节点，找到要插入的子节点
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;

        // 如果子节点已满，先分裂再插入
        if (node->child[i]->n == ORDER - 1) {
            splitChild(node, i, node->child[i]);
            if (key > node->keys[i]) {
                i++;
            }
        }

        // 递归插入子节点
        insertNonFull(&(node->child[i]), key);
    }
}

// 插入关键字
void insert(BTreeNode** root, int key) {
    BTreeNode* node = *root;

    // 如果树为空，创建一个新节点作为根
    if (!node) {
        *root = createNode();
        (*root)->keys[0] = key;
        (*root)->n = 1;
        return;
    }

    // 如果根节点已满，先分裂再插入
    if (node->n == ORDER - 1) {
        BTreeNode* newRoot = createNode();
        newRoot->leaf = 0;
        newRoot->child[0] = *root;
        *root = newRoot;
        splitChild(newRoot, 0, node);
        insertNonFull(root, key);
    } else {
        insertNonFull(root, key);
    }
}



// 打印 B 树
void printBTree(BTreeNode* node, int level) {
    if (node) {
        printf("Level %d: ", level);
        for (int i = 0; i < node->n; ++i) {
            printf("%d ", node->keys[i]);
        }
        printf("\n");

        if (!node->leaf) {
            for (int i = 0; i <= node->n; ++i) {
                printBTree(node->child[i], level + 1);
            }
        }
    }
}

int main() {
    BTreeNode* root = NULL;

    // 插入一些关键字
    insert(&root, 3);
    insert(&root, 7);
    insert(&root, 2);
    insert(&root, 9);
    insert(&root, 1);
    insert(&root, 6);
    insert(&root, 4);
    insert(&root, 5);
    insert(&root, 8);

    // 打印 B 树
    printBTree(root, 0);

    return 0;
}
