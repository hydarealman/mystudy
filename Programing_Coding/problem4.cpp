// 最小公倍数
// 辗转相除法: 
// lcm: 最小公倍数 gcd: 最大公约数
// LCM(a, b) = |a × b| ÷ GCD(a, b)
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

// 求解最大公约数
long long gcd(long long a, long long b) {
    // 反复用余数替换原数相除，直至整除，最后的除数即为最大公约数。
    while(b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// 求解最小公约数
long long lcm(long long a, long long b) {
    // 防止溢出: 先除最大公约数再乘
    return a / gcd(a, b) * b;
}

int main() {
    long long num1,num2;
    cin >> num1 >> num2;
    long long gcd_num = gcd(num1,num2);
    long long lcm_num = lcm(num1,num2);
    cout << lcm_num << endl;
}