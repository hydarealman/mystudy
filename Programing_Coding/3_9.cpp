#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

typedef pair<int, int> pii; // (距离, 顶点)

void dijkstra(int start, const vector<vector<pii>>& graph, vector<int>& dist) {
    int n = graph.size() - 1;
    dist.assign(n + 1, INT_MAX);
    dist[start] = 0;
    
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, start});
    
    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        if (d > dist[u]) continue;
        
        for (const pii& edge : graph[u]) {
            int v = edge.first;
            int w = edge.second;
            int nd = d + w;
            
            if (nd < dist[v]) {
                dist[v] = nd;
                pq.push({nd, v});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, x;
    cin >> n >> m >> x;
    
    vector<vector<pii>> graph(n + 1);  // 原图
    vector<vector<pii>> rev_graph(n + 1); // 反向图
    
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        rev_graph[v].push_back({u, w}); // 反向边
    }
    
    vector<int> dist_to(n + 1);    // 从x到各点的距离（回家）
    vector<int> dist_from(n + 1);  // 从各点到x的距离（去派对）
    
    dijkstra(x, graph, dist_to);    // 计算回家的最短路径
    dijkstra(x, rev_graph, dist_from); // 计算去派对的最短路径（使用反向图）
    
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int total = dist_to[i] + dist_from[i];
        ans = max(ans, total);
    }
    
    cout << ans << endl;
    
    return 0;
}