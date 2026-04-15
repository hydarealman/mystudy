#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
#include <string>
#include <cstring>
using namespace std;
const int MAXN = 100005;

// 回溯法与分支定界法
// 奇怪的Andy,奇怪的旅行
// 最多能走过多个城市 -> 任意点最远点是直径端点
/*
u:       当前正在访问的节点
parent:  当前节点u的父节点
depth:   从起点到当前节点的距离
*/

void dfs(int u, int parent ,int depth , vector<int>& dist, vector<vector<int> > graph) {
    dist[u] = depth;    // 记录当前节点的距离原点的距离
    // for (int v : graph[u]) {
    //    if (v != parent) {  // 不允许访问同一座城市
    //         dfs(v,u,depth + 1,dist,graph); // 搜索下一个节点
    //    } 
    // }

   for (int i = 0; i < graph[u].size(); i++) {
        if (graph[u][i] != parent) { // 不允许访问同一个城市
            dfs(graph[u][i], u, depth + 1, dist, graph);
        }
   }
}

int main() {
    // 邻接表构造图
    int n;
    cin >> n;
    vector<int> dist(n+1,0);              // 记录各个节点距离原点的距离(dist[u],表示距离节点u的最大距离)
    vector<vector<int> > graph(n+1);     // 邻接图
    for (int i = 0; i < n-1; i++) {     // n-1条边
        int u,v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // 第一次dfs： 从任意节点开始,找到距离最远的节点
    // (在树中,从任意节点出发,距离它最远的点一定是树直径的一个端点)
    dfs(1, -1, 0,dist,graph); // 以这个节点为起点 那么其父节点为-1(不存在)
    
    // 寻找距离原点距离最远的点
    int farthest_first_Node = 0;
    for (int i = 2; i < dist.size(); i++) { // 节点1是起点就不遍历了
        if (dist[i] > farthest_first_Node) {
            farthest_first_Node = i;
        }
    }

    // 第二次dfs: 从第一次找到的最远节点开始(树直径的一个端点),找到直径的另一端
    dist.assign(n+1, 0);  // 将 vector 的所有元素设置为 0
    dfs(farthest_first_Node, -1, 0,dist,graph);

    // 查找两次端点的距离就是最大距离
    int maxDist = 0;
    for (int i = 1; i < dist.size(); i++) {
        if (dist[i] > maxDist) {
            maxDist = dist[i];
        }
    }

    // 输出最多能走过多少个城市 (最大距离 + 1) - > 直径的节点数 = 边数 + 1
    cout << maxDist + 1 << endl;
}