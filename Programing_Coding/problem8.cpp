// 金币支付 -> 用a和b的线性组合不能被表示的最大整数
// 由于a和b互质,
// 任何大于等于(a-1)*(b-1)的整数都可以表示为a和b的非负整数线性组合
// 而a*b - a - b正好等于(a-1)*(b-1) - 1,无法被表示,且是最大的这样的数
// 两个互质数，不能凑出的最大数 = 两数乘积减去两数之和
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() {
    int a,b;
    cin >> a >> b;
       
    cout << a*b - a - b;
}