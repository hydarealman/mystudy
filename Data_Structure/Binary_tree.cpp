#include<iostream>
#include<cstring>
#include<stack>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
typedef struct TreeNode *BinTree;
struct TreeNode{
    int data;
    BinTree left;
    BinTree right;
    TreeNode() : data(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : data(x), left(nullptr), right(nullptr) {}
};

//先序遍历构造二叉树
void CreateBiTree(TreeNode*& T,int S[],int & i,int size) {
   if (i >= size || S[i] == -1) {
        T = nullptr;
        return;
   }
   else {
    /*i++是先返回,再递增,返回的是一个临时的右值,引用的初始值需要的是左值 */
    T = new TreeNode(S[i]);
    CreateBiTree(T->left,S,++i,size);
    CreateBiTree(T->right,S,++i,size);
   }
}

//递归实现(先序遍历)(中序遍历和后序遍历只需更换位置即可)
void PreOrderTraversal(BinTree BT) {
    if (BT) {
        printf("%d",BT->data);
        PreOrderTraversal(BT->left);
        PreOrderTraversal(BT->right);
    }
}

//非递归实现(先序遍历)----统一迭代法(中序遍历和后序遍历只需更换位置即可)
void PreOrderTraversal2(BinTree BT) {
    BinTree node = BT;
    stack<BinTree> st;
    if (BT != nullptr) st.push(node);
    while(!st.empty()) {
        node = st.top();
        if (node != nullptr) {
            st.pop();
            if (node->right) st.push(node->right);//右
            if (node->left) st.push(node->left);//左
            st.push(node);//中
            st.push(nullptr);
        }
        else {
            st.pop();
            node = st.top();
            st.pop();
            printf("%d",node->data);
        }
    } 
}

//非递归实现(先序遍历)----非统一迭代法
void PreOrderTraversal3(BinTree BT){
    BinTree root = BT;
    stack<BinTree> st;
    if (root == nullptr) return;
    st.push(root);
    while(!st.empty()) {
        BinTree node = st.top();
        st.pop();
        printf("%d",node->data);
        if (node->right) st.push(node->right);
        if (node->left) st.push(node->left);
    }
}
//非递归实现(中序遍历)----非统一迭代法
void inorderTraversal(BinTree BT) {
    stack<BinTree> st;
    BinTree cur = BT;
    while(cur != nullptr || !st.empty()) {
        if (cur != nullptr) {
            st.push(cur);
            cur = cur->left;
        }
        else {
            cur = st.top();
            st.pop();
            printf("%d",cur->data);
            cur = cur->right;
        }
    }
}
//非递归实现(后序遍历)----非统一迭代法
void postorderTraversal(BinTree BT) {
    stack<BinTree> st;
    vector<BinTree> v;
    if (BT == nullptr) return;
    while(!st.empty()) {
        BinTree node = st.top();
        st.pop();
        v.push_back(node);
        if (node->left) st.push(node->left);
        if (node->right) st.push(node->right);
    }
    reverse(v.begin(),v.end());
    for (int i = 0; i < v.size(); i++) {
        printf("%d",v[i]->data);
    }
}

//层序遍历(有层次)
void LevelOrderTraversal(BinTree BT){
    queue<BinTree> que;
    if (BT != nullptr) que.push(BT);
    while(!que.empty()) {
        int size = que.size();
        for (int i = 0; i < size; i++) {
            BinTree node = que.front();
            que.pop();
            printf("%d",node->data);
            if (node->left) que.push(node->left);
            if (node->right) que.push(node->right);
        }
        printf("\n");
    }
}
//层序遍历
void LevelOrderTraversal1(BinTree BT){
    queue<BinTree> que;
    if (BT != nullptr) que.push(BT);
    while(!que.empty()) {
        BinTree node = que.front();
        que.pop();
        printf("%d",node->data);
        if (node->left) que.push(node->left);
        if (node->right) que.push(node->right);
    }
}
//输出叶子结点
void FindLeaves(BinTree BT){
    if (BT) {
        if (!BT->left && !BT->right) {//如果左右都为空
            printf("%d",BT->data);
        }
        FindLeaves(BT->left);
        FindLeaves(BT->right);
    }
} 
//树高
int GetHeight(BinTree BT){
    int hl,hr,maxh;
    if (BT) {
        hl = GetHeight(BT->left);
        hr = GetHeight(BT->right);
        maxh = (hl>hr)?hl:hr;
        return maxh + 1;
    }
    else {
        return 0;
    }
} 
int main() {

}