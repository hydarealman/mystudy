#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MOD = 1e9 + 7;
const int MAXL = 2005;
const int MAXS = 205;

int n, L;
vector<pair<int, int>> shapes; // (length, width)
vector<int> cake_id; // 每个形状属于哪个蛋糕类型
int dp[MAXL][MAXS];

int main() {
    cin >> n >> L;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        shapes.push_back({ a, b });
        cake_id.push_back(i);
        if (a != b) {
            shapes.push_back({ b, a });
            cake_id.push_back(i);
        }
    }
    int S = shapes.size();

    // 初始化：第一块蛋糕
    for (int s = 0; s < S; s++) {
        int len = shapes[s].first;
        if (len <= L) {
            dp[len][s] = 1;
        }
    }

    // 转移
    for (int l = 1; l <= L; l++) {
        for (int s = 0; s < S; s++) {
            if (dp[l][s] == 0) continue;
            int w = shapes[s].second;
            for (int t = 0; t < S; t++) {
                if (cake_id[t] == cake_id[s]) continue; // 相邻不能是同一蛋糕类型
                if (shapes[t].first != w) continue;
                int nl = l + shapes[t].first;
                if (nl > L) continue;
                dp[nl][t] = (dp[nl][t] + dp[l][s]) % MOD;
            }
        }
    }

    int ans = 0;
    for (int s = 0; s < S; s++) {
        ans = (ans + dp[L][s]) % MOD;
    }
    cout << ans << endl;

    return 0;
}       