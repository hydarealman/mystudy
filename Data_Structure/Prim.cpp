#include<iostream>
#include<vector>
#include <climits>

using namespace std;

int main() {
    int v,e;
    int x,y,k;
    cin >> v >> e;
    vector<vector<int>> grid(v+1,vector<int>(v+1,0));
    while(e--) {
        cin >> x >> y >> k;
        grid[x][y] = k;
    }

    vector<int> minDist(v + 1,10001);
    vector<bool> isintree(v + 1,false);

    for (int i = 1; i < v; i++) {
        int cur = -1;
        int minVal = INT_MAX;
        for (int j = 1; j <= v; j++) {
            if (!isintree[v] && minDist[j] < minVal) {
                minVal = minDist[j];
                cur = j;
            }
        }

        isintree[cur] = true;

        for (int j = 1; j <= v; j++) {
            if (!isintree[j] && grid[cur][j] < minDist[j]) {
                minDist[j] = grid[cur][j];
            }
        }

        int result = 0;
        for (int i = 2; i <= v; i++) {
            result += minDist[i];
        }
        cout << result << endl;
    }
}