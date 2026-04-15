// 编写程序,求n!
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

string calculate(int n) {
    if (n == 0 || n == 1) {
        return "1";
    }

    vector<int> result;
    result.push_back(1);

    for (int i = 2; i <= n; i++) {
        int carry = 0; 

        // 将每个结果乘以i
        for (int j = 0; j < result.size(); j++) {
            int product = result[j] * i + carry;
            result[j] = product % 10;
            carry = product /= 10;
        }

        // 处理剩余进位
        while (carry > 0) {
            result.push_back(carry % 10);
            carry /= 10;
        }
    }

    // 高位填充0
    for (int i = 0 ; i < 64 - result.size(); i++) {
        result.push_back(0);
    }

    // 转换为0
    string res;
    reverse(result.begin(),result.end());
    for (int i = 0; i < result.size(); i++) {
        res += to_string(result[i]);
    }
    return res;
}

int main() {
    int n;
    cin >> n;

    string result = calculate(n);

    cout << result << endl;
}