#include <iostream>
#include <vector>

using namespace std;

struct Node {
    bool flag;
    int x, y;
};

Node map[20][20];
vector<int> road;
int N, X[20], Y[20], sum;
int dir[4][2] = {{0, 1},
                 {1, 0},
                 {-1, 0},
                 {0, -1}};

bool dfs(int x, int y) {
    if (x == N - 1 && y == N - 1) {
        for (int i = 0; i < N; i++) {
            if (X[i] || Y[i] || sum)
                return false;
            road.push_back(x * N + y);
            return true;
        }
    }

    road.push_back(x * N + y);
    map[x][y].flag = true;
    for (int i = 0; i < 4; i++) {
        int tx = x + dir[i][0];
        int ty = y + dir[i][1];
        if (tx < 0 || tx > (N - 1) || ty < 0 || ty > (N - 1))
            continue;
        if (!map[tx][ty].flag && (X[tx] > 0 && Y[ty] > 0)) {
            X[tx]--;Y[ty]--;sum -= 2;
            if (dfs(tx, ty))
                return true;
            else {
                X[tx]++;
                Y[ty]++;
                sum += 2;
            }
        }
    }
    map[x][y].flag = false;
    road.erase(road.begin() + road.size() - 1);
    return false;
}

int main() {
    cin >> N;
    for (int i = 0; i < N; i++){
        cin >> Y[i];
        sum += Y[i];
    }
    for (int i = 0; i < N; i++) {
        cin >> X[i];
        sum += X[i];
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            map[i][j].flag = false;
            map[i][j].x = i;
            map[i][j].y = j;
        }
    }
    X[0]--;Y[0]--;sum -= 2;
    dfs(0, 0);
    for (int i = 0; i < road.size(); i++)
        cout << road[i] << ' ';
    return 0;
}