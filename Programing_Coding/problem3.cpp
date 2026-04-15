// 统计字母出现频率
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() {
    string str_input;
    getline(cin,str_input);
    vector<int> cnt(26);
    for (int i = 0; i < str_input.size(); i++) {
        cnt[str_input[i] - 'a'] += 1;
    }
    int total = 0;
    for (int i = 0; i < cnt.size(); i++) {
        total += cnt[i];
    }
    for (int i = 0; i < cnt.size(); i++) {
        // 输出统计对象
        cout << char('A' + i) << "  ";
        // 输出统计个数
        if (cnt[i] == 0) {
            continue;
        }
        cout << cnt[i] << "  " << endl;

        // 输出百分比
        double temp = (cnt[i] * 100) / (double)total;
        // 限制小数点两位
        cout << fixed << setprecision(2) << temp << "%";

        // 输出条状图
        int each = (cnt[i] * 100) / total ;
        if ((cnt[i] * 100) / total > 0) {
            each += 1;
        }
        for (int i = 0; i < each; i++) {
            cout << "*";
        }
        cout << endl;
    }
}