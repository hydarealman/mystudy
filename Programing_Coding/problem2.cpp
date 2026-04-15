// 找最大数和最小数
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    cin >> nums[0];
    int max_num = nums[0];
    int min_num = nums[0];
    for (int i = 1; i < n; i++) {
        cin >> nums[i];
        max_num = max(max_num,nums[i]);
        min_num = min(min_num,nums[i]);
    }

    cout << "max_num=" << max_num << "min_num=" << min_num;
}