// 5.3
// 贪心算法
// 多处最优服务次序问题
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() {
    int n,s;            // n个顾客 s处服务地点
    cin >> n >> s;
    vector<int> clinets(n);
    vector<int> services(s);
    vector<int> result(n);
    for (int i = 0; i < n; i++) {
        cin >> clinets[i];
    }

    // 先服务耗时短的(贪心 -> 局部最优堆叠全局最优)
    sort(clinets.begin(),clinets.end());

    // // debug
    // for (int i = 0; i < clinets.size(); i++) {
    //     cout << clinets[i] << endl;
    // }

    // 每个服务点维护一个当前的工作时间,表示该服务点已经工作了多长时间
    // 每当一个顾客被分配了一个服务点,该服务点的工作时间就会增加该顾客的服务时间
    // 为什么服务时间要把自己也算上 -> 如果这样子的话题目表述应该为题目逗留时间
    for (int i = 0; i < clinets.size(); i++) {
        // if (s1 <= s2) {
        //     s1 += clinets[i];
        //     result[i] += s1;
        // }
        // else {
        //     s2 += clinets[i];
        //     result[i] += s2;
        // }

        // 将只能适配两个服务点的代码升级成适配多喝服务点的代码
        // 选择已经服务时间最小的等待点
        int min_services = 0;
        int min_services_index = 0;
        for (int j = 1; j < services.size(); j++) {
            // 更新最小值
            min_services = min(services[min_services_index],services[j]);
            // 更新最小下标
            if (services[min_services_index] >= services[j]) {
                min_services_index = j;
            }
        }
        services[min_services_index] += clinets[i];
        result[i] += services[min_services_index];
    }
    // 计算等待时间
    double avg;
    double total = 0;
    for (int i = 0; i < result.size(); i++) {
        total += result[i];
    }
    avg = total / result.size();
    cout << fixed << setprecision(3) << avg << endl;;
}