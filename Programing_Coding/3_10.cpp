#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// BFS函数，计算从起点(sx,sy)到所有点的最短距离
vector<vector<int>> bfs(int sx, int sy, const vector<string>& grid, int n, int m) {
    vector<vector<int>> dist(n, vector<int>(m, -1));
    if (grid[sx][sy] == '#') return dist;
    queue<pair<int, int>> q;
    dist[sx][sy] = 0;
    q.push({sx, sy});
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    while (!q.empty()) {
        auto [x, y] = q.front(); q.pop();
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == '.' && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
    return dist;
}

int main() {
    ios::sync_with_stdio(false);
    int n, m, D, R;
    cin >> n >> m >> D >> R;
    vector<string> grid(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    // 起点或终点是障碍，直接无法到达
    if (grid[0][0] == '#' || grid[n - 1][m - 1] == '#') {
        cout << -1 << endl;
        return 0;
    }

    // 计算从起点和终点出发的最短距离
    auto dist_from_start = bfs(0, 0, grid, n, m);
    auto dist_from_end = bfs(n - 1, m - 1, grid, n, m);

    // 初始答案为不使用传送门的步数
    int ans = dist_from_start[n - 1][m - 1];

    // 枚举使用传送门的点
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == '.' && dist_from_start[i][j] != -1) {
                int ni = i + D;
                int nj = j + R;
                // 检查传送目标是否合法
                if (ni >= 0 && ni < n && nj >= 0 && nj < m && grid[ni][nj] == '.' && dist_from_end[ni][nj] != -1) {
                    int steps = dist_from_start[i][j] + 1 + dist_from_end[ni][nj];
                    if (ans == -1 || steps < ans) {
                        ans = steps;
                    }
                }
            }
        }
    }

    cout << ans << endl;
    return 0;
}