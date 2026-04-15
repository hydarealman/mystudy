#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 1e5 + 5;
int a[N];     //储存初始顺序的数组
bool st[N];   //标记数组
int main() {
    int n;
    cin >> n;
    //输入数组
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int cnt = 0; //记录初始环数
    for (int i = 1; i <= n; i++) {
        if (!st[i]) {  //没有被标记，找到一个环的起点
            cnt++;
            for (int j = i; !st[j]; j = a[j]) {    //访问这个环，将这个环中所有结点都进行标记
                st[j] = true;
            }
        }
    }
    cout << n - cnt;
}