// // 动态规划
// #include <iostream>
// #include <vector>
// #include <map>
// #include <algorithm>
// using namespace std;


// // 比较两个序列的字典序
// bool compareSeq(const vector<int>& a, const vector<int>& b) {
//     int minSize = min(a.size(), b.size());
//     for (int i = 0; i < minSize; i++) {
//         if (a[i] != b[i]) {
//             return a[i] < b[i];
//         }
//     }
//     return a.size() < b.size();
// }


// int main() {
//     int N,M; // N枚硬币总数,M付款金额
//     cin >> N >> M;
//     vector<int> coins(N); // 读取N之后再创建硬币
//     for (int i = 0; i < N; i++) {
//         cin >> coins[i];
//     }

//     sort(coins.begin(),coins.end()); // 从小到大排序

//     // dp[i][j] 表示第i+1个物品在背包为j的空格下的最大价值
//     vector<vector<int> > dp(N,vector<int>(M + 1));  // 老编译器版本
//     int bagweight = M;
//     // path[i][j] 存储所有可能的解
//     vector<vector<vector<int> > > path(N + 1, vector<vector<int> >(M + 1));
//     path[0][0] = vector<int>();

//     // 路径记录
//     vector<vector<bool> > choice(N,vector<bool>(M + 1,false));

//     // 初始化
//     for (int i = 0; i <= bagweight; i++) {
//         if (i >= coins[0]) {
//             dp[0][i] = coins[0];
//             choice[0][i] = true; // 选择第一个硬币
//         }
//     }

//     // 动态规划方程
//     // 先遍历物品,再遍历背包重量
//     for (int i = 1; i < N; i++) {
//         for (int j = 0; j <= bagweight; j++) {
//             // cout << "debug: " << dp[i][j] << endl;
//             if (j >= coins[i] && coins[i] + dp[i-1][j - coins[i]] > dp[i-1][j]) {
//                 dp[i][j] = coins[i] + dp[i-1][j - coins[i]];
//                 choice[i][j] = true; // 选择了第i个硬币
//                 vector<int> newPath = path[i-1][j-coins[i-1]];
//                 newPath.push_back(coins[i-1]);
//                 sort(newPath.begin(), newPath.end()); // 确保升序
                
//                 // 比较字典序,选择小的
//                 if (path[i][j].empty() || compareSeq(newPath, path[i][j])) {
//                     path[i][j] = newPath;
//                 }
//             }
//             else {
//                 // cout << "debug: 大小不够" << endl;
//                 dp[i][j] = dp[i-1][j];
//                 path[i][j] = path[i-1][j];
//             }
//             // cout << dp[i][j] << endl;
//         }
//     }

//     // 判断是否能够凑出
//     // 当背包的最大价值刚好等于自己的最大容量的时候
//     // 说明此时刚好能够凑出
//     // cout << dp[N-1][M] << endl;
//     if (dp[N-1][M] == M) {
//         for (int k = 0; k < path[N][M].size(); k++) {
//             if (k != 0) cout << " ";
//             cout << path[N][M][k];
//         }
//         cout << endl;
//     }
//     else {
//         cout << "No Solution" << endl;
//     }

//     // // debug
//     // for (int i = 0; i < N; i++) {
//     //     for (int j = 0; j <= bagweight; j++) {
//     //         cout << choice[i][j] << " ";
//     //     }
//     //     cout << endl;
//     // }
    
//     return 0;
// }



#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 比较两个序列的字典序
bool compareSeq(const vector<int>& a, const vector<int>& b) {
    int minSize = min(a.size(), b.size());
    for (int i = 0; i < minSize; i++) {
        if (a[i] != b[i]) {
            return a[i] < b[i];
        }
    }
    return a.size() < b.size();
}

int main() {
    int N, M;
    cin >> N >> M;
    vector<int> coins(N);
    for (int i = 0; i < N; i++) {
        cin >> coins[i];
    }

    // 字典序最小的解不一定只由小面值硬币组成,但当有多种组合能达到相同金额时，我们应该优先使用小面值的硬币。
    sort(coins.begin(), coins.end()); // 从小到大排序

    // dp[i][j] 表示前i个硬币能否凑出金额j
    vector<vector<bool> > dp(N + 1, vector<bool>(M + 1, false));
    // path[i][j] 存储所有可能的解
    vector<vector<vector<int> > > path(N + 1, vector<vector<int> >(M + 1));
    
    // 初始化
    dp[0][0] = true;
    path[0][0] = vector<int>();
    
    // 动态规划
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= M; j++) {
            // 不选第i个硬币
            if (dp[i-1][j]) {
                dp[i][j] = true;
                path[i][j] = path[i-1][j];
            }
            
            // 选第i个硬币
            if (j >= coins[i-1] && dp[i-1][j-coins[i-1]]) {
                dp[i][j] = true;
                vector<int> newPath = path[i-1][j-coins[i-1]];
                newPath.push_back(coins[i-1]);
                sort(newPath.begin(), newPath.end()); // 确保升序
                
                // 比较字典序,选择小的
                if (path[i][j].empty() || compareSeq(newPath, path[i][j])) {
                    path[i][j] = newPath;
                }
            }
        }
    }

    // 输出结果
    if (!dp[N][M] || path[N][M].empty()) {
        cout << "No Solution" << endl;
    } else {
        for (int k = 0; k < path[N][M].size(); k++) {
            if (k != 0) cout << " ";
            cout << path[N][M][k];
        }
        cout << endl;
    }
    
    return 0;
}