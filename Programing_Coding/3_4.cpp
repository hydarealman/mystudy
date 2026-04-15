#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <string>

using namespace std;

string change(string str) {
    int i = 0;
    string ans;
    while(i < str.size()) {
        int cont = 0;
        while(i + cont < str.size() && str[i + cont] == str[i]) cont++;
        ans += to_string(cont) + str[i];
        i = i + cont;
    }
    return ans;
}

int main() {
    string a;
    int b;
    cin >> a >> b;
    while(b--) a = change(a);
    cout << a;
    return 0;
}//by wqs