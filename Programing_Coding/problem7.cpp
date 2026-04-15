// 天才婴儿
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() {
    int n,k;
    cin >> n >> k;
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        int num = i;
        int temp = 0;
        while(num > 0) {
            temp += num%10;
            num /= 10;
        }        
        int k0 = i - temp;
        if (k0 > k) {
            cnt++;
        }
    }
    cout << cnt;
}