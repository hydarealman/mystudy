// #include <iostream>
// #include <vector>
// #include <map>
// using namespace std;


// map<int, int> memo;  // 记忆化，避免重复计算
// int solve(int num) {
//     if (num == 1) return 1;

//     // 如果已经计算过，直接返回
//     if (memo.find(num) != memo.end()) return memo[num];

//     int count = 1;  // n本身是一种分解

//     for (int i = 2; i <= num / 2; i++) {
//         if (num % i == 0) {
//             count += solve(i);
//         }
//     }

//     // 保存结果到记忆化表
//     memo[num] = count;
//     return count;
// }

// int main() {
//     int n;
//     while(cin >> n) {
//         cout << solve(n) << endl;
//     }
//     return 0;
// }


// 记忆化搜索
// 终止条件: 当num递归到1时,当num是质数时
// 递推表达式: f(n) = 1 sum(f(n / i))
// 整数因子分解问题
#include <iostream>
#include <map>
using namespace std;

map<int,int> memo;
int solve(int num) {
    if (num == 1) return 1;

    if (memo.find(num) != memo.end()) return memo[num];

    int count = 1;
    for (int i = 2; i <= num / 2; i++) {
        if (num % i == 0) {
            count += solve(num / i);
        }
        
    }
    memo[num] = count;
    return count;
}

int main() {
    int n;
    while(cin >> n) {
        cout << solve(n) << endl;
    }
}
