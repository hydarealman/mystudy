#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge{
    int l,r,val;
};

int n = 10001;
vector<int> father(n,-1);

void init() {
    for (int i = 0; i < n; i++) {
        father[i] = i;
    }
}

int find(int u) {
    return u == father[u] ? u : father[u] = find(father[u]);
}

void join(int u,int v) {
    u = find(u);
    v = find(v);
    if (u == v) return;
    father[v] = u;
}

int main() {
    //对边从小到大排序,如果没有联通就加入
    int v,e;
    int v1,v2,val;
    vector<Edge> edges;
    int result_val;
    cin >> v >> e;
    while(e--) {
        cin >> v1 >> v2 >> val;
        edges.push_back({v1,v2,val});
    }

    sort(edges.begin(),edges.end(),[](const Edge& a,const Edge& b){
        return a.val < b.val;
    });

    init();

    for (Edge edge : edges) {
        int x = find(edge.l);
        int y = find(edge.r);

        if (x != y) {
            result_val += edge.val;
            join(x,y);
        }
    }
    cout << result_val << endl;
    return 0;
}