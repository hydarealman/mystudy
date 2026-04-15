#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
#include <string>
#include <set>
#include <sstream>
using namespace std;

// (2)	选择问题 给定的n个元素数组a[0: n-1]，要求找出第k小的元素。
int main() {
    // 只能按住ctrk + c等退出
    int n = 0,k = 0;
    while(cin >> n >> k) {
        set<int> s;
        for (int i = 0; i < n; i++) {
            int num;
            cin >> num;
            s.insert(num);
        }
    
        vector<int> nums;
        for (set<int>::iterator it = s.begin(); it != s.end(); it++) {
            nums.push_back(*it);
        }
    
        // sort(nums.begin(),nums.end()); set已经是有序了不需要排序
    
        cout << nums[k -1] << endl;
    }
}