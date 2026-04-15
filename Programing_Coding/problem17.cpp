#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
#include <string>
using namespace std;

/*遇到过的问题: 
代码输出的列编号是从0开始的,而题目要求从1开始

*/


// 回溯法与分支定界法
// n皇后问题

// 存储每个方案
vector<vector<vector<char> > > result;

// 补充: 这里不需要遍历行,因为在单层搜索的过程中,每一层递归,只会选
// for循环里面的一个元素
// 满足n皇后就返回真,不满足n皇后就返回假
bool isValid(vector<vector<char> > chessboard,int col, int row, int n) {
    // 遍历列
    for (int i = 0; i < row; i++) {
        if (chessboard[i][col] == '*') {
            return false;
        }
    }
    // 遍历45度
    for (int i = row - 1,j = col - 1; i >= 0 && j >= 0; i--,j--) {
        if (chessboard[i][j] == '*') {
            return false;
        }
    }

    // 遍历135度
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--,j++) {
        if (chessboard[i][j] == '*') {
            return false;
        }
    }
    return true;
}

// 回溯法暴搜索n皇后问题
void backtracking(int n,int row,vector<vector<char> >& chessboard) {
    if (row == n) {
        result.push_back(chessboard);
        return;
    }

    for (int col = 0; col < n; col++) {
        if (isValid(chessboard,col,row,n)) { // 如果同行同列同斜线存在就不继续搜索了
            chessboard[row][col] = '*';               // 放入皇后
            backtracking(n,row + 1,chessboard);   // 继续递归
            chessboard[row][col] = '.';               // 回溯
        }
    }
}

int main() {
    // '*'表示放置皇后 '.'表示不防止皇后
    int n;      // n*n的棋盘
    cin >> n;
    // 构造棋盘
    vector<vector<char> > chessboard(n,vector<char>(n));
    for (int  i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            chessboard[i][j] = '.';
        }
    }

    // 存储方案总数
    vector<vector<int> > count;

    // 暴搜计算结果
    backtracking(n,0,chessboard); // 先从第0行开始搜索

    for (int i = 0; i < result.size(); i++) {
        vector<int> temp;
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (result[i][j][k] == '*') { // 如果第i个结果的第j行第k列示皇后则统计数据
                    temp.push_back(k);
                }
            }
        }
        count.push_back(temp);
    }

    // 打印数据
    for (int i = 0; i < count.size(); i++) {
        for (int j = 0; j < count[0].size() - 1; j++) {
            cout << count[i][j] + 1 << " ";
        }
        cout << count[i][count[0].size()-1] + 1 << endl;
    }

    // 题目理解错误的代码
    // // 统计结果
    // for (int i = 0; i < result.size(); i++) {
    //     for (int j = 0; j < n; j++) {
    //         for (int k = 0; k < n; k++) {
    //             if (result[i][j][k] == '*') { // 如果第i个结果的第j行第k列示皇后则统计数据
    //                 cnt[j][k]++;
    //             }
    //         }
    //     }
    // }
    // // 输出结果: 输出的是所有可能的放置情况,每一行代表一种方案
    // // 该行的数字表示每一行的皇后所在的列号
    // for (int i = 0; i < cnt.size(); i++) {
    //     for (int j = 0; j < cnt[0].size() - 1; j++) {
    //         cout << cnt[i][j] << " ";
    //     }
    //     cout << cnt[i][cnt[0].size() - 1] << endl;
    // }

    cout << "Total=" << result.size() << endl;
}