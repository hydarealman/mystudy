#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
#include <string>
#include <set>
using namespace std;

// 回溯法与分支定界法
// 最长公共子串问题

int main() {

    // // // 维护区间的暴力解法 -> 失败(只能处理相同长度字串的操作)
    // string str1;
    // string str2;
    // cin >> str1;
    // cin >> str2;

    // set<string> result; // 存储找到的最长子串

    // int max_sub_len = 0;
    // for (int i = 0; i < str1.size(); i++) {
    //     for (int j = i; j < str1.size(); j++) {

    //         int each = i;
    //         int sub_len = 0;
    //         string str_sub = "";
    //         while(each <= j) {
    //             if (str1[each] == str2[each]) {
    //                 sub_len++;
    //                 str_sub += str1[each];
    //             }

    //             // max_sub_len = max(max_sub_len,sub_len);
    //             if (sub_len > max_sub_len) {
    //                 // 如果有更长的最长字串就清除掉旧的,放入新的
    //                 result.clear();
    //                 result.insert(str_sub);
    //                 max_sub_len = sub_len;
    //             }
    //             else if (max_sub_len == sub_len) {
    //                 // 如果有相同的最长子串就放入
    //                 result.insert(str_sub);
    //             }
    //             else {
    //                 // 没有的话,不做更新
    //             }

    //             // 类似于减枝
    //             if (str1[each] != str2[each]) {
    //                 break;
    //             }

    //             each++;
    //         }
    //     }
    // }

    // // 输出结果
    // cout << max_sub_len << endl;
    // for (set<string>::iterator it = result.begin(); it != result.end(); ++it) {
    //     cout << *it << endl;
    // }



    
    // // 遍历开头的暴力解法 -> 正确
    // string str1;
    // string str2;
    // cin >> str1;
    // cin >> str2;

    // int max_sub_len = 0;
    // set<string> result;
    // for (int i = 0; i < str1.size(); i++) {
    //     for (int j = 0; j < str2.size(); j++) {

    //         int x = i, y = j;
    //         string str_sub = "";
    //         while (x < str1.size() && y < str2.size() && str1[x] == str2[y]) {
    //             str_sub += str1[x];
    //             x++;
    //             y++;
    //         }

    //         int sub_len = (x+1) - i - 1;
    //         // max_sub_len = max(max_sub_len,sub_len);

    //         if (sub_len > max_sub_len) {
    //             // 如果有更长的最长字串就清除掉旧的,放入新的
    //             result.clear();
    //             result.insert(str_sub);
    //             max_sub_len = sub_len;
    //         }
    //         else if (max_sub_len == sub_len) {
    //             // 如果有相同的最长子串就放入
    //             result.insert(str_sub);
    //         }
    //         else {
    //             // 没有的话,不做更新
    //         }
    //     }
    // }


    // // 输出结果
    // // cout << max_sub_len << endl;
    // // for (string sub : result) { // c98
    // //     cout << sub << endl;
    // // }

    // cout << max_sub_len << endl;
    // for (set<string>::iterator it = result.begin(); it != result.end(); ++it) {
    //     cout << *it << endl;
    // }


    // 动态规划解法 && 分支定界法
    /*
    二维数组可以比较好的记录所有比较情况
    dp[i-1][j-1] // 以下标i-1为结尾的A,以下表j-1为结尾的B -> 方便初始化

    // dp[i][0] 和 dp[0][j] 没有意义
    
    */

    string str1;
    string str2;
    cin >> str1;
    cin >> str2;

    int max_sub_len = 0;
    vector<vector<int> > dp(str1.size() + 1, vector<int>(str2.size() + 1,0));
    set<string> result;
    for (int i = 1; i <= str1.size(); i++) {
        for (int j = 1; j <= str2.size(); j++) {
            if (str1[i-1] == str2[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            }
            if (dp[i][j] > max_sub_len) {
                max_sub_len = dp[i][j];
                result.clear();
                result.insert(str1.substr((i + 1) - max_sub_len - 1, max_sub_len));
            }
            else if (dp[i][j] == max_sub_len) {
                result.insert(str1.substr((i + 1) - max_sub_len - 1, max_sub_len));
            }
        }
    }
    cout << max_sub_len << endl;
    for (set<string>::iterator it = result.begin(); it != result.end(); ++it) {
        cout << *it << endl;
    }
}