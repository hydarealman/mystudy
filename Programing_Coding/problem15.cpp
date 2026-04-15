#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
#include <string>
using namespace std;

// 回溯法与分支定界法
// 哈夫曼编码译码

// 哈夫曼树节点
class HFNode {
public:
    int weight;                 // 权重域
    char ch;                    // 数据域,保存字符信息
    vector<char> code;          // 哈夫曼编码
    int lchild,rchild,parent;   // 左孩子索引,右孩子索引,父节点索引
};

// 哈夫曼树类
class HFTree {
public: 

    // 构造函数
    HFTree(int n) {
        num = n;            // 设置叶子节点数量
        int m = 2 * n - 1;  // 设置哈夫曼节点数量 // 总节点数 = 叶子节点数 + 内部节点数 = n + (n-1) = 2n - 1
        nodes.resize(m);    // 为节点数组分配空间
        root = -1;          // 初始化根节点索引为-1
    }

    // 构建哈夫曼树
    void createHFTree() {
        /*
            节点索引分配
            索引0到n-1:  分配给原始叶子节点
            索引0到2n-2: 分配给新创建的内部节点
        */
        int m = 2 * num - 1;
        // 逐个创建内部节点
        for (int i = num; i < m; i++) {
            // 选择两个权值最小的节点
            int min1 = -1 , min2 = -1;

            // 我们已经创建了i个节点(包括原始节点和之间创建的内部节点)
            // 我们需要从这i个节点中找出两个还没有被合并的（parent == -1）且权重最小的节点
            // 第一次遍历: 找到第一个最小的
            for (int j = 0; j < i; j++) {
                if (nodes[j].parent == -1) {
                    if (min1 == -1 || nodes[j].weight < nodes[min1].weight) {
                        min1 = j;
                    }
                    else if (nodes[j].weight == nodes[min1].weight) {
                        // 权值相等时,按照出现先后顺序,下标小的优先 
                        if (j < min1) {
                            min1 = j;
                        }
                    }
                }
            }

            // 第二次遍历: 找到第二个最小的
            for (int j = 0; j < i; j++) {
                if (nodes[j].parent == -1 && j != min1) { // 不等于最小的最小就是第二个最小的 且 还没有被合并
                    if (min2 == -1 || nodes[j].weight < nodes[min2].weight) {
                        min2 = j;
                    }
                    else if (nodes[j].weight == nodes[min2].weight) {
                        // 权值相等时,按照出现先后顺序,下标小的优先 
                        if (j < min2) {
                            min2 = j;
                        }
                    }
                }         
            }

            // 确保左子树的权值不大于右子树
            if (nodes[min1].weight > nodes[min2].weight) {
                swap(min1, min2);
            }

            // 创建新节点
            nodes[i].weight = nodes[min1].weight + nodes[min2].weight;
            nodes[i].lchild = min1;
            nodes[i].rchild = min2;
            nodes[i].parent = -1;

            // 更新子节点的父节点
            nodes[min1].parent = i;
            nodes[min2].parent = i;

            // 最后一个创建的节点是根节点
            if (i == m - 1) {
                root = i;
            }
        }
    }

    // 先序遍历输出编码
    // 输入: 根节点序号
    void preOrderHelper(int node, vector<pair<char,vector<char>>>& result) {
        if (node == -1) return;

        // 如果是叶子节点,保存字符和编码
        if (nodes[node].lchild == -1 && nodes[node].rchild == -1) {
            result.push_back({nodes[node].ch, nodes[node].code});
        }

        preOrderHelper(nodes[node].lchild,result);
        preOrderHelper(nodes[node].rchild,result);
    }

    // 先序遍历输出编码
    void preOrder() { 
        vector<pair<char, vector<char>>> result;
        preOrderHelper(root, result);

        for (auto& p : result) {
            cout << p.first << ":";
            for (char c : p.second) {
                cout << c;
            }
            cout << endl;
        }
    }

    // 初始化叶子节点
    void Initialization(const vector<pair<char, double>>& chars) {
        for (int i = 0; i < num; i++) {
            nodes[i].ch = chars[i].first;            // 当前节点字符
            nodes[i].weight = chars[i].second * 100; // 频率
            nodes[i].lchild = -1;
            nodes[i].rchild = -1;
            nodes[i].parent = -1;
        }
    }

    // 生成哈夫曼编码
    void generateCode() {
        // 对每个叶子节点生成编码
        for (int i = 0; i < num; i++) {
            int child = i;
            int parent = nodes[child].parent;
            vector<char> code;
            
            // 从叶子节点回溯到根节点
            while (parent != -1) {
                if (nodes[parent].lchild == child) {
                    code.push_back('0'); // 左分支标记问0
                }
                else {
                    code.push_back('1'); // 右分支标记为1
                }
                child = parent;
                parent = nodes[child].parent;
            }

            // 反转编码
            reverse(code.begin(),code.end());
            nodes[i].code = code;
        }
    }

    // 译码
    string Decoding(string encodedStr) {
        string result = "";
        int current = root;

        for (char bit : encodedStr) {

            // 如果当前读取位是'0'表示哈夫曼树中应该走左分支
            if (bit == '0') {
                current = nodes[current].lchild;
            } // 如果当前不是'0'就走右分支
            else {
                current = nodes[current].rchild;
            }

            // 如果到达叶子节点
            if (nodes[current].lchild == -1 && nodes[current].rchild == -1) {
                result += nodes[current].ch;
                current = root;
            } 
        }

        return result;
    }

private: 
    vector<HFNode> nodes;       // 哈夫曼节点数组
    int num;                    // 叶子结点个数
    int root;                   // 根节点索引
};

int main() {
    // 读取输入字符串个数
    int n;
    cin >> n;

    // 读取输入的相应的字符及其词频
    vector<pair<char,double>> chars(n);
    for (int i = 0; i < n; i++) {
        string line;
        cin >> line;
        char ch = line[0];
        double freq = stod(line.substr(1)); // 提取字串(提取到末尾)  // 返回从索引1到末尾的子串
        chars[i] = {ch, freq};
    }

    // 输入译码
    string encodedStr;
    cin >> encodedStr;

    // 构建哈夫曼树
    HFTree hfTree(n);                 // 构造函数
    hfTree.Initialization(chars);     // 初始化   
    hfTree.createHFTree();            // 创建哈夫曼树
    hfTree.generateCode();            // 生成哈夫曼编码


    // 先序遍历输出编码
    hfTree.preOrder();

    // 译码并输出原文
    string decodedStr = hfTree.Decoding(encodedStr);
    cout << "original:" << decodedStr << endl;
}