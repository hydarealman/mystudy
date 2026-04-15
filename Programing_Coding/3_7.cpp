#include <iostream>
#include <vector>
using namespace std;

int main() {
    const int TOTAL_PEOPLE = 50;
    const int SPECIAL_GROUP_SIZE = 7;

    // 假设编号0-6是那7个人
    vector<int> is_special(TOTAL_PEOPLE, 0);
    for (int i = 0; i < SPECIAL_GROUP_SIZE; i++) {
        is_special[i] = 1;
    }

    int handshakes = 0;

    // 遍历所有可能的握手对
    for (int i = 0; i < TOTAL_PEOPLE; i++) {
        for (int j = i + 1; j < TOTAL_PEOPLE; j++) {
            // 如果两个人都属于特殊组，则不握手
            if (is_special[i] && is_special[j]) {
                continue;
            }
            handshakes++;
        }
    }

    cout <<  handshakes << endl;

    return 0;
}