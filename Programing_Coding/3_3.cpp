#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MAX_N = 100;

struct Node {
    int x, y, steps;
    char last_sign; // 上一步经过的辐射区类型：'+' 或 '-'
};

int n;
vector<vector<char>> grid;
bool visited[MAX_N][MAX_N][2]; // visited[x][y][0] 表示以'+'结束访问, visited[x][y][1] 表示以'-'结束访问
int startX, startY, endX, endY;

// 四个移动方向：下，上，右，左
int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

int bfs() {
    queue<Node> q;

    // 从起点A开始，可以走任意相邻的辐射区
    for (int d = 0; d < 4; d++) {
        int nx = startX + dir[d][0];
        int ny = startY + dir[d][1];

        if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;

        char cell = grid[nx][ny];
        if (cell == 'B') {
            // A直接相邻B
            return 1;
        }

        if (cell == '+' || cell == '-') {
            int state = (cell == '+') ? 0 : 1;
            if (!visited[nx][ny][state]) {
                visited[nx][ny][state] = true;
                q.push({ nx, ny, 1, cell });
            }
        }
    }

    while (!q.empty()) {
        Node cur = q.front();
        q.pop();

        // 如果当前就是终点
        if (cur.x == endX && cur.y == endY) {
            return cur.steps;
        }

        // 尝试四个方向
        for (int d = 0; d < 4; d++) {
            int nx = cur.x + dir[d][0];
            int ny = cur.y + dir[d][1];

            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;

            char next_cell = grid[nx][ny];

            // 不能走回A
            if (next_cell == 'A') continue;

            // 规则：当前是'+'，下一步必须是'-'或B
            // 当前是'-'，下一步必须是'+'或B
            bool can_move = false;
            if (cur.last_sign == '+') {
                can_move = (next_cell == '-' || next_cell == 'B');
            }
            else if (cur.last_sign == '-') {
                can_move = (next_cell == '+' || next_cell == 'B');
            }

            if (can_move) {
                int state = 0;
                char next_sign = cur.last_sign; // 占位

                if (next_cell == '+') {
                    state = 0;
                    next_sign = '+';
                }
                else if (next_cell == '-') {
                    state = 1;
                    next_sign = '-';
                }
                else if (next_cell == 'B') {
                    // B可以接在任何符号后面，状态可以任意（这里用0）
                    state = 0;
                    next_sign = cur.last_sign;
                }

                if (!visited[nx][ny][state]) {
                    visited[nx][ny][state] = true;
                    q.push({ nx, ny, cur.steps + 1, next_sign });
                }
            }
        }
    }

    return -1;
}

int main() {
    cin >> n;
    grid.resize(n, vector<char>(n));

    // 读取网格
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];

            if (grid[i][j] == 'A') {
                startX = i;
                startY = j;
            }
            else if (grid[i][j] == 'B') {
                endX = i;
                endY = j;
            }
        }
    }

    // 初始化visited数组
    memset(visited, 0, sizeof(visited));

    // 执行BFS
    int result = bfs();

    // 输出结果
    cout << result << endl;

    return 0;
}