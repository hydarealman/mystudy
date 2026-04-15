// 求n个整数的平均值与中位数
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    int total = 0;
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
        total += nums[i];
    }
    sort(nums.begin(),nums.end());
    int len = nums.size();
    // 求中位数
    int mid_num = 0;
    if (len % 2 == 1) {
        mid_num = nums[len/2];
    }
    else {
        mid_num = nums[len/2] + nums[(len/2)-1];
    }

    double avg = (double)total / (double)n;

    cout << "mean=" << avg << "median=" << mid_num << endl;
}